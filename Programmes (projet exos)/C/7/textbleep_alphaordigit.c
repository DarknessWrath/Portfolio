//  Syntaxe : textbleep_alphaordigit BLEEP CLASS [FILE]...
//
//  Modifie les fichiers texte FILEs en substituant le caractère BLEEP aux
//    caractères de la catégorie CLASS. Les valeurs possibles pour CLASS sont
//    alpha ou digit

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//  textbleep : modifie le fichier texte de nom la chaine pointée par filename
//    en substituant le caractère bleep aux caractères satisfaisant la condition
//    charcond. Renvoie zéro en cas de succès, une valeur non nulle en cas
//    d'échec
int textbleep(const char *filename, int bleep, int (*charcond)(int c));

enum {
  PROGN_IDX,
  BLEEP_IDX,
  CLASS_IDX,
  EXPECTED_ARGC_MIN
};

int main(int argc, char *argv[]) {
  if (argc < EXPECTED_ARGC_MIN) {
    fprintf(stderr, "*** Bad number of parameters\n");
    return EXIT_FAILURE;
  }
  if (strlen(argv[BLEEP_IDX]) != 1) {
    fprintf(stderr, "*** Illegal BLEEP argument\n");
    return EXIT_FAILURE;
  }
  int (*charcond)(int) = NULL;
  if (strcmp(argv[CLASS_IDX], "alpha") == 0) {
    charcond = isalpha;
  } else if (strcmp(argv[CLASS_IDX], "digit") == 0) {
    charcond = isdigit;
  }
  if (charcond == NULL) {
    fprintf(stderr, "*** Illegal CLASS argument\n");
    return EXIT_FAILURE;
  }
  //  IB : EXPECTED_ARGC_MIN <= k && k <= argc
  //    && les fichiers de nom argv[EXPECTED_ARGC_MIN] à argv[k - 1] ont été
  //        traités
  //  QC : k
  for (int k = EXPECTED_ARGC_MIN; k < argc; ++k) {
    const char *filename = argv[k];
    if (textbleep(filename, *argv[BLEEP_IDX], charcond) != 0) {
      fprintf(stderr, "*** Error on file '%s'\n", filename);
    } else {
      printf("Done\t%s\n", filename);
    }
  }
  return EXIT_SUCCESS;
}
