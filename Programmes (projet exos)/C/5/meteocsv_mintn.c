//  affiche le minimum des températures minimales (Tn)
//    de chacun des fichiers météorologiques (format CSV avec tabulations)
//    dont le nom figure sur la ligne de commande

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//--- Autour de la fonction principale -----------------------------------------

//  usage : affiche l'aide et termine le programme
void usage(const char *progname);

//  max_tn : Cherche le maximum des températures minimales
//    du fichier météorologique (format CSV avec tabulations) de nom la chaine
//    pointée par filename. En cas de succès, affecte cette valeur à l'objet
//    pointé par ptr et renvoie zéro. En cas d'échec, ne modifie par la valeur
//    de l'objet pointé par ptr et renvoie une valeur non nulle
int max_tn(const char *filename, float *ptr);

//--- mesure et unité

#define MEASURE_TXT "La température minimale la plus élevée"
#define UNIT_TXT    "oC"

//--- fonction principale

#define ARG__OPT_LONG "--"
#define ARG_HELP      "help"

int main(int argc, char *argv[]) {
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
      usage(argv[0]);
    }
  }
  //  IB : 1 <= k && k <= argc
  //    && les fichiers de nom argv[1] à argv[k - 1] ont été traités
  //  QC : k
  for (int k = 1; k < argc; ++k) {
    const char *a = argv[k];
    float msr;
    int r = max_tn(a, &msr);
    if (r != 0) {
      fprintf(stderr, "Erreur sur '%s'\n", a);
    } else {
      printf("%6.1f " UNIT_TXT "\t%s\n", msr, a);
    }
  }
  return EXIT_SUCCESS;
}

//--- Développements -----------------------------------------------------------

#define FUN_SUCCESS 0
#define FUN_FAILURE -1

//--- usage

#define USG_FILE    "FICHIER"
#define USG__OPEN   "["
#define USG__CLOSE  "]"
#define USG__ETC    "..."

void usage(const char *progname) {
  fputs("Utilisation : ", stdout);
  fputs(progname, stdout);
  fputs(" " USG__OPEN USG_FILE USG__CLOSE USG__ETC "\n", stdout);
  fputs("Affiche " MEASURE_TXT " de " USG_FILE "s.\n", stdout);
  exit(EXIT_SUCCESS);
}

//--- report

//  report : structure pour les relevés météorologiques
typedef struct {
  struct {
    int gyear;
    int month;
    int mday;
  } date;
  float tx; // température maximale
  float tn; // température minimale
  float rr; // précipitations
  float w;  // ensoleillement
} report;

//  freport_scan : lit un relevé dans le flot texte contrôlé par l'objet pointé
//    par f. En cas de succès, affecte le relevé à l'objet pointé par ptr et
//    renvoie zéro. En cas d'échec, renvoie une valeur non nulle
//  AE : le fichier associé au flot est ouvert en lecture
//  AS : conforme à la description
int freport_scan(FILE *f, report *ptr) {
  int rfs = fscanf(f, "%d%d%d%f%f%f%f",
      &(ptr -> date.gyear),
      &(ptr -> date.month),
      &(ptr -> date.mday),
      &(ptr -> tx),
      &(ptr -> tn),
      &(ptr -> rr),

  if(rfs != 6){
    FUN_FAILURE;
  }
  if(fgetchar(f) == "\n" || "\t")
  // condition séparé pour \n et \t
}

//--- min_tn

int max_tn(const char *filename, float *ptr) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    return FUN_FAILURE;
  }
  float n = 0.0;
  report rpt;
  int rfrs = freport_scan(f, &rpt);
  //  IB : rfrs == (dernière valeur renvoyée par freport_scan(f, &rpt))
  //    && rpt == (dernier relevé lu sur f si rfrs == 0)
  //    && n == (Minimum (tn) de température, sans compter le dernier
  //              relevé lu si rfrs == 0)
  //  QC : nombre d'appels freport_scan(f, &rpt)
  while (rfrs == 0) {
    if(rpt.tn < n) {
      n=rpt.tn;
    }

    rfrs = freport_scan(f, &rpt);
  }
  int r = FUN_SUCCESS;
  if (! feof(f)) {
    r = FUN_FAILURE;
  }
  if (fclose(f) != 0) {
    r = FUN_FAILURE;
  }
  if (r == FUN_SUCCESS) {
    *ptr = n;
  }
  return r;
}
