//  affiche le contenu
//    de chacun des fichiers météorologiques (format binaire)
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

//--- structure report et fonctions diverses

typedef struct {
  date d;
  float tx; // température maximale
  float tn; // température minimale
  float rr; // précipitations
  float w;  // ensoleillement
} report;

//  report_print : affiche sur la sortie standard le contenu d'un tableau sur
//    le type report dont l'adresse du premier composant est base et dont la
//    longueur est nmemb
void report_print(const report *base, size_t nmemb);
int comp_Tx (const report *ptr1, const report *ptr2);
void *min_search(const void *base, size_t nmemb ,size_t size, int (*compar)
 (const void *, const void *));
 void mem_swap (void *s1, void *s2, size_t size);
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
       qsort (yrpt.array, yrpt.length, sizeof(report), (int (*)(const void * ,
       const void *)) comp_Tx);
      printf("--- %s\n", a);
      report_print(yrpt.array, yrpt.length);
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
  fputs("Affiche le contenu de " USG_FILE "s.\n", stdout);
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

void report_print(const report *base, size_t nmemb) {
  //  IB : 0 <= k && k <= nmemb
  //    && les composants d'indices 0 à k - 1 du tableau base ont été affichés
  //  QC : k
  for (size_t k = 0; k < nmemb; ++k) {
    printf("%02d-%02d-%04d\t%5.1f °C\t%5.1f °C\t%5.1f mm\t%5.1f h\n",
        base[k].d.mday, base[k].d.month, base[k].d.year,
        base[k].tx, base[k].tn, base[k].rr, base[k].w);
  }
}
//-----Comparaisons
int comp_Tx (const report *ptr1 , const report *ptr2) {
  //IB:
  //QC:
  int d = (ptr1 -> tx > ptr2 -> tx) - (ptr1 -> tx < ptr2 -> tx);
  if (d == 0) {
    d = (ptr1 -> tn > ptr2 -> tn) - (ptr1 -> tn < ptr2 -> tn);
  }
  return d;
  }
void *min_search(const void *base, size_t nmemb ,size_t size, int (*compar)
  (const void *, const void *)) {
  //IB: q <= p && p <= e
  //QC:
  const char *q= base;
  const char *p = (const char *) base + size;
  const char *e= (const char *) base + nmemb * size;
    while (p < e) {
      if (compar(p,q) < 0) {
        q = p;
      }
      p+=size;
    }
  return (void *) q;
}
void mem_swap (void *s1, void *s2, size_t size) {
  char *p1 = s1;
  char *p2 = s2;
  size_t k = 0;
  while (k < size) {
    char c = *p1;
    *p1 = *p2;
    *p2 = c;
    ++p1;
    ++p2;
    ++k;
  }
}
  void select_sort(void * base, size_t nmemb, size_t size, int (*compar)
  (const void *, const void *)) {
  char *p= base;
  //  IB:base <= k && k <=  nmemb
  //  && le tableau base est une reconstruction de sa valeur initiale
  //  && le préfixe de longueur nmemb*size est crlkssa t aj se s de compar
  //  && tout composant du préfixe est inférieur ou égal à tout composant
  // du suffixe complémentaire au sens de compar
  //&& p == adresse du premier composant du suffixe
  //  QC: k
  for (size_t k = nmemb;k>0; --k) {
    char *q = min_search(p, k ,size, compar);
    if (p < q) {
      mem_swap(p, q, size);
    }
  p +=size;
  }
}
