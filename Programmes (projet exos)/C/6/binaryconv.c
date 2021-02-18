//  conversion d'un fichier météorologique de format .csv en en format binaire.


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//--- Autour de la fonction principale -----------------------------------------

//  usage : affiche l'aide et termine le programme
void usage(const char *progname);

//  sum_rr : calcule la somme des précipitations (Rr)
//    du fichier météorologique (format CSV avec tabulations) de nom la chaine
//    pointée par filename. En cas de succès, affecte cette valeur à l'objet
//    pointé par ptr et renvoie zéro. En cas d'échec, ne modifie par la valeur
//    de l'objet pointé par ptr et renvoie une valeur non nulle
int conv(const char *dest, const char *src);

//--- mesure et unité

#define MEASURE_TXT "la somme des précipitations (Rr)"
#define UNIT_TXT    "mm"

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
    const char *src = argv[k];
    if (strlen(src) > strlen(ARG__OPT_LONG)
        && strlen(src) <= strlen(ARG__OPT_LONG ARG_HELP)
        && strncmp(src, ARG__OPT_LONG ARG_HELP, strlen(src)) == 0) {
      usage(argv[0]);
    }
  }
  //  IB : 1 <= k && k <= argc
  //    && les fichiers de nom argv[1] à argv[k - 1] ont été traités
  //  QC : k
  for (int k = 1; k < argc; ++k) {
    const char *src = argv[k];
    char dest[strlen(src)+1];
    strcpy (dest, src);
    dest[strlen(src)-3] = 'b';
    dest[strlen(src)-2] = 'i';
    dest[strlen(src)-1] = 'n';
    int r = conv(dest, src);
    if (r != 0) {
      fprintf(stderr, "Erreur sur '%s'\n", src);
    } else {
      printf("Le fichier %s à été converti sans soucis\n", src);
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
      &(ptr -> w));
  if (rfs !=7) {
    return FUN_FAILURE;
  }
  return FUN_SUCCESS;
}

//--- conv

int conv (const char *dest, const char *src) {
  FILE *f = fopen(src, "r");
  if (f == NULL) {
    return FUN_FAILURE;
  }
  FILE *d = fopen(dest, "w");
  if (d == NULL) {
    return FUN_FAILURE;
  }

  float s = 0.0;
  report rpt;
  int rfrs = freport_scan(f, &rpt);
  //  IB : rfrs == (dernière valeur renvoyée par freport_scan(f, &rpt))
  //    && rpt == (dernier relevé lu sur f si rfrs == 0)
  //    && conv == (conversion du fichier en format .csv en format .bin,
  //              relevé lu si rfrs == 0)
  //  QC : nombre d'appels freport_scan(f, &rpt)
  while (rfrs == 0 && fwrite(&rpt, sizeof(rpt), 1, d) == 1) {

    rfrs = freport_scan(f, &rpt);
  }
  int r = FUN_SUCCESS;
  if (! feof(f) ) {
    r = FUN_FAILURE;
  }
  if (fclose(f) !=0 || fclose(d) !=0){
    r = FUN_FAILURE;
  }
  if (r == FUN_SUCCESS) {
    s = s;
  }
  return r;
}