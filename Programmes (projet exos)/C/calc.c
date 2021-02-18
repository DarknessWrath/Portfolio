#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#define HAUTEUR_MAX 4

int main(void) {
  int n=0;
  char s[32+1];
  char *p;
  long int pile[HAUTEUR_MAX];
  int h=0;

  while (scanf("%32s", s) == 1) {
    ++n;
   long int x = strtol(s,&p, 10);

    if(*p =='\0' && errno ==0) {

    if(h==HAUTEUR_MAX) {
    printf("Stack Overflow");
    return EXIT_FAILURE;
    }
   pile[h]=x;
   ++h; }
   else {
   if(strcmp(s, "END") == 0) {
   if (h!=1) {
    printf("Only one integer expected\n");
    return EXIT_FAILURE;
  }
  printf("%ld\n", pile[0]);
  h=0;
}
   else if(strcmp(s, "ADD")){
    if (h<2) {
      printf("Two integers expected\n");
      return EXIT_FAILURE;
    }
  else {
    pile[h-2]=pile[h-2] + pile[h-1];
    --h;
    }
  }

   else if(strcmp(s, "MUL")) {
  if (h<2) {
    printf("Two integers expected\n");
    return EXIT_FAILURE;
   }
   else { pile[h-2]=pile[h-2] * pile[h-1];
  --h;
 } }

   else if(strcmp(s, "SUB")) { // Exercice 3
  if (h<2) {
    printf("Two integers expected\n");
    return EXIT_FAILURE;
   }
   pile[h-2]=pile[h-2] - pile[h-1];
  --h;
}
  else if(strcmp(s, "QUO")) { // Exercice 3
  if (h<2) {
    printf("Two integers expected\n");
    return EXIT_FAILURE;
   }
   pile[h-2]=pile[h-2] / pile[h-1];
  --h; }
}

}
   return EXIT_SUCCESS;}


