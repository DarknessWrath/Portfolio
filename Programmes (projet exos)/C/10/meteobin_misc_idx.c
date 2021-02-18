//  affiche les résultats de divers calculs
//    sur chacun des fichiers météorologiques (format binaire)
//    dont le nom figure sur la ligne de commande

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//--- Autour de la fonction principale -----------------------------------------

//--- aide

bool helpneeded(int argc, char *argv[]);
void usage(const char *progname);

//--- structure date et fonctions diverses

typedef struct {
  int year;
  int month;
  int mday;
} date;

void date_print_year(const date *ptr);
void date_print_mdaymonth(const date *ptr);

//--- structure report et fonctions diverses

typedef struct {
  date d;
  float tx; // température maximale
  float tn; // température minimale
  float rr; // précipitations
  float w;  // ensoleillement
} report;



// cond_count : renvoie le nombre de composants d’un tableau qui satisfont une
// condition. base est l’adresse du premier composant du tableau, nmemb, le
// nombre de composants du tableau, size, la taille des composants, cond, un
// pointeur vers la condition

size_t cond_count(const void *base, size_t nmemb, size_t size,
  bool (*cond)(const void *));
    bool report_frostnight_cond(const report *p);

size_t report_frostnight_count(const report *base, size_t nmemb);

//  report_frost_left_search : recherche la première occurrence d'une journée
//    sans dégel (Tx <= 0 et Tn <= 0) dans un tableau sur le type report. base
//    est l'adresse du premier composant du tableau, nmemb, sa longueur. Renvoie
//    l'adresse du composant trouvé en cas de succès, NULL en cas d'échec
report *report_frost_left_search(const report *base, size_t nmemb);

//  report_mintn_left_search : recherche la première occurrence d'une journée
//    de température minimale (Tn) minimum dans un tableau sur le type report.
//    base est l'adresse du premier composant du tableau, nmemb, sa longueur.
//    Renvoie NULL si nmemb vaut zéro, l'adresse du composant trouvé sinon
report *report_mintn_left_search(const report *base, size_t nmemb);

//--- structure yearreport et fonctions diverses

#define NDAYS_PER_YEAR_MIN  365
#define NDAYS_PER_YEAR_MAX  366

typedef struct {
  size_t length;
  report array[NDAYS_PER_YEAR_MAX];
} yearreport;

//  yearreport_fload : charge le contenu du fichier météorologique binaire de
//    nom la chaine pointée par filename dans le tableau ptr -> array. La
//    longueur du fichier doit être comprise entre NDAYS_PER_YEAR_MIN et
//    NDAYS_PER_YEAR_MAX. En cas de succès, donne à ptr -> length cette longueur
//    et renvoie zéro. En cas d'échec, renvoie une valeur non nulle
int yearreport_fload(const char *filename, yearreport *ptr);

//--- formats

#define TMPR_FORMAT   "%0.1f"
#define LABEL_FORMAT  "%-20s"

//--- fonction principale

int main(int argc, char *argv[]) {
  if (helpneeded(argc, argv)) {
    usage(argv[0]);
    return EXIT_SUCCESS;
  }
  //  IB : 1 <= k && k <= argc
  //    && les fichiers de nom argv[1] à argv[k - 1] ont été traités
  //  QC : k
  for (int k = 1; k < argc; ++k) {
    const char *a = argv[k];
    yearreport yrpt;
    int r = yearreport_fload(a, &yrpt);
    if (r != 0) {
      fprintf(stderr, "Erreur sur '%s'\n", a);
    } else {
      {
        size_t n = cond_count(yrpt.array, yrpt.length, sizeof(report),
        (bool (*) (const void *)) report_frostnight_cond);
        date_print_year(&yrpt.array[0].d);
        printf(" " LABEL_FORMAT, "n. jours Tn <= 0");
        printf("%zu\n", n);
      }
      {
        report *ptr = report_frost_left_search(yrpt.array, yrpt.length);
        date_print_year(&yrpt.array[0].d);
        printf(" " LABEL_FORMAT, "prem. Tx/Tn <= 0");
        if (ptr == NULL) {
          printf("***\n");
        } else {
          date_print_mdaymonth(& ptr -> d);
          printf(" Tx/Tn = " TMPR_FORMAT "/" TMPR_FORMAT "\n", ptr -> tx,
              ptr -> tn);
        }
      }
      {
        report *ptr = report_mintn_left_search(yrpt.array, yrpt.length);
        date_print_year(&yrpt.array[0].d);
        printf(" " LABEL_FORMAT, "prem. min. Tn");
        date_print_mdaymonth(& ptr -> d);
        printf(" Tn = " TMPR_FORMAT "\n", ptr -> tn);
      }
    }
  }
  return EXIT_SUCCESS;
}

//--- Développements -----------------------------------------------------------

#define FUN_SUCCESS 0
#define FUN_FAILURE -1

//--- aide

#define ARG__OPT_LONG "--"
#define ARG_HELP      "help"

bool helpneeded(int argc, char *argv[]) {
  //  IB : 1 <= k && k <= argc
  //    && aucune des chaines argv[1] à argv[k - 1] n'est préfixe de
  //        ARG__OPT_LONG . ARG_HELP ou n'admet ARG__OPT_LONG . ARG_HELP[0]
  //        comme préfixe
  //  QC : k
  for (int k = 1; k < argc; ++k) {
    const char *a = argv[k];
    if (strlen(a) > strlen(ARG__OPT_LONG)
        && strlen(a) <= strlen(ARG__OPT_LONG ARG_HELP)
        && strncmp(a, ARG__OPT_LONG ARG_HELP, strlen(a)) == 0) {
      return true;
    }
  }
  return false;
}

#define USG_FILE    "FICHIER"
#define USG__OPEN   "["
#define USG__CLOSE  "]"
#define USG__ETC    "..."

void usage(const char *progname) {
  fputs("Utilisation : ", stdout);
  fputs(progname, stdout);
  fputs(" " USG__OPEN USG_FILE USG__CLOSE USG__ETC "\n", stdout);
  fputs("Affiche les résultats de divers calculs sur " USG_FILE "s.\n", stdout);
}

//--- date

void date_print_year(const date *ptr) {
  printf("%.4d", ptr -> year);
}

void date_print_mdaymonth(const date *ptr) {
  printf("%.2d-%.2d", ptr -> mday, ptr -> month);
}

//--- yearreport

int yearreport_fload(const char *filename, yearreport *ptr) {
  FILE *f = fopen(filename, "rb");
  if (f == NULL) {
    return FUN_FAILURE;
  }
  int r = FUN_SUCCESS;
  size_t n = fread(ptr -> array, sizeof(report), NDAYS_PER_YEAR_MAX, f);
  if (n < NDAYS_PER_YEAR_MIN || (n == NDAYS_PER_YEAR_MAX && fgetc(f) != EOF)) {
    r = FUN_FAILURE;
  }
  if (fclose(f) != 0) {
    r = FUN_FAILURE;
  }
  ptr -> length = (r == FUN_FAILURE ? 0 : n);
  return r;
}

//--- report

/*size_t report_frostnight_count(const report *base, size_t nmemb) {
  size_t n = 0;
  //  IB : 0 <= k && k <= nmemb
  //    && n == somme([base[j].tn <= 0] ; j == 0 ... k - 1)
  //  QC : k
  for (const report *p = base; p < base + nmemb; ++p) {
    n += (p -> tn <=0);
  }
  return n;
}*/

size_t report_frostnight_count(const report *base, size_t nmemb) {
  return cond_count(base, nmemb, sizeof(report),
    (bool (*)(const void *)) report_frostnight_cond);
}

bool report_frostnight_cond(const report *p){
  return p -> tn <=0;
}


size_t cond_count(const void *base, size_t nmemb, size_t size,
bool (*cond)(const void *)){

  size_t n = 0;
  //IB: 0 <= p <= nmemb +1
  // && n n == somme(([p -> tn <=0]): p == base....base + nmemb)
  // QC: p
  for (const char *p = base;  p < (const char *) base + nmemb * size; ++p){
    if (cond(p)){
      ++n;
    }
  }
  return n;
}




report *report_frost_left_search(const report *base, size_t nmemb) {
  size_t k = 0;
  //  IB : 0 <= k && k <= nmemb
  //    && et(! (base[j].tx <= 0.0 && base[j].tn <= 0.0)) ; j == 0 ... k - 1)
  //  QC : k
  while (k < nmemb) {
    if (base[k].tx <= 0.0 && base[k].tn <= 0.0) {
      return (report *) & base[k];
    }
    ++k;
  }
  return NULL;
}

report *report_mintn_left_search(const report *base, size_t nmemb) {
  if (nmemb == 0) {
    return NULL;
  }
  size_t j = 0;
  //  IB : 1 <= k && k <= nmemb
  //    && j == premmin(base[0 ... k - 1].tn)
  //  QC : k
  for (size_t k = 1; k < nmemb; ++k) {
    if (base[k].tn < base[j].tn) {
      j = k;
    }
  }
  return (report *) & base[j];
}
