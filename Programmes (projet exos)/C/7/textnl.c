//  Syntaxe : textnl [FILE]...
//
//  Affiche sur la sortie standard le contenu des fichiers texte spécifiés.
//    Chaque ligne est précédée de son numéro. La numérotation des lignes
//    commence à 1. Le numéro de la ligne et son contenu sont séparés par une
//    tabulation. Si le dernier caractère du fichier n'est pas la fin de ligne,
//    affiche une fin de ligne après ce dernier caractère. L'affichage du
//    contenu est précédé d'une tabulation, du nom du fichier et d'une fin de
//    ligne

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define FUN_SUCCESS 1
#define FUN_FAILURE 0


//  textnl : affiche sur la sortie standard le contenu du fichier texte de nom
//    la chaine pointée par filename. Chaque ligne est précédée de son numéro.
//    La numérotation des lignes commence à 1. Le numéro de la ligne et son
//    contenu sont séparés par une tabulation. Si le dernier caractère du
//    fichier n'est pas la fin de ligne, affiche une fin de ligne après ce
//    dernier caractère. L'affichage du contenu est précédé d'une tabulation,
//    du nom du fichier et d'une fin de ligne. Renvoie zéro en cas de succès,
//    une valeur non nulle en cas d'échec
int textnl(const char *filename);

int main(int argc, char *argv[]) {
  //  IB : 1 <= k && k <= argc
  //    && les fichiers de nom argv[1] à argv[k - 1] ont été traités
  //  QC : k
  for (int k = 1; k < argc; ++k) {
    const char *filename = argv[k];
    if (textnl(filename) != 0) {
      fprintf(stderr, "*** Error on file '%s'\n", filename);
    }
  }
}
//------Développement
int textnl(const char *filename){
  printf("\t%s\n", filename);
  FILE *f=fopen(filename, "r");
  long int n=0;
    if(f == NULL) {
     return FUN_FAILURE;
    }
  while(! feof(f)) {
    int c=fgetc(f);
    ++n;
    printf("%ld\t", n);
    while(c !='\n' && c != EOF){
     printf("%c", c);
     c=fgetc(f);
    }
     printf("\n");
  }



      int r = FUN_SUCCESS;
   if(! feof(f)){
    r= FUN_FAILURE;
    }
    if(fclose(f) !=1) {
    r = FUN_FAILURE;
    }
    return r;
}
