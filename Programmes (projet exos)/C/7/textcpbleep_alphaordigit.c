//  Syntaxe : textcpbleep_alphaordigit BLEEP CLASS SRC DEST
//
//  Crée le fichier texte DEST en lui donnant comme contenu celui du fichier
//    texte SRC en substituant le caractère BLEEP aux caractères de la catégorie
//    CLASS. Les valeurs possibles pour CLASS sont alpha ou digit

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define FUN_FAILURE -1
#define FUN_SUCCESS 0

//  textcpbleep : crée le fichier texte de nom la chaine pointée par dest en lui
//    donnant comme contenu celui du fichier texte de nom la chaine pointée par
//    src en substituant le caractère bleep aux caractères satisfaisant la
//    condition charcond. Renvoie zéro en cas de succès, une valeur non nulle en
//    cas d'échec
int textcpbleep(const char *dest, const char *src, int bleep,
    int (*charcond)(int c));

enum {
  PROGN_IDX,
  BLEEP_IDX,
  CLASS_IDX,
  SRC_IDX,
  DEST_IDX,
  EXPECTED_ARGC
};

int main(int argc, char *argv[]) {
  if (argc != EXPECTED_ARGC) {
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
  if (textcpbleep(argv[DEST_IDX], argv[SRC_IDX], *argv[BLEEP_IDX],
      charcond) != 0) {
    fprintf(stderr, "*** An error occurred\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int textcpbleep(const char *dest, const char *src, int bleep,
    int (*charcond)(int c)){
  FILE *f =fopen(src, "r");
  if (f == NULL) {
    return FUN_FAILURE;
  }
  FILE *d = fopen(dest, "w");
  if (d == NULL) {
    if (fclose(f) !=0) {
      return FUN_FAILURE;
    }
    while(! feof(f)) {
      int c = fgetc(f);
      fputc(
  return FUN_SUCCESS;
  }
}
