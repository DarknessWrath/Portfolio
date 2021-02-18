//  Syntaxe : textwc [FILE]...
//
//  Affiche sur la sortie standard le nombre de mots apparaissant dans les
//    fichiers texte spécifiés. Un mot est une suite de longueur maximale de
//    caractères qui ne sont pas de la catégorie isspace. Pour chaque fichier
//    pour lequel le décompte peut être mené à son terme, l'affichage est de la
//    forme le nombre de mots, une tabulation, le nom du fichier, une fin de
//    ligne

#include <stdlib.h>
#include <stdio.h>
#define FUN_SUCCESS 0
#define FUN_FAILURE -1

//  textwc : renvoie le nombre de mots apparaissant dans le fichier texte de nom
//    pointé par filename
long int textwc(const char *filename);

int main(int argc, char *argv[]) {
  //  IB : 1 <= k && k <= argc
  //    && les fichiers de nom argv[1] à argv[k - 1] ont été traités
  //  QC : k
  for (int k = 1; k < argc; ++k) {
    const char *filename = argv[k];
    long int n = textwc(filename);
    if (n == -1) {
      fprintf(stderr, "*** Error on file '%s'\n", filename);
    } else {
      printf("%ld\t%s\n", n, filename);
    }
  }
}

long int textwc(const char *filename) {
  FILE *f=fopen(filename, "r");
  long int n=0;
    if(f == NULL) {
     return FUN_FAILURE;
    }
    while(fscanf(f,"%*s") == 0) {
     ++n;
     }
   if(! feof(f)){
    n= FUN_FAILURE;
    }
    if(fclose(f) !=0) {
    n = FUN_FAILURE;
    }
    return n;
}

