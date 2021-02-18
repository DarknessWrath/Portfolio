#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
int main(void) {
  char s[32 + 1];
  int n=0;
  char *p;

  while (scanf("%32s", s) == 1) {
    ++n;
   long int x = strtol(s,&p, 10);

    if(*p =='\0' && errno ==0) {
      printf("%d\t%s\toperand=%ld\n", n, s, x);
    }
    else if ((strcmp(s, "MUL") == 0) || (strcmp(s, "END") == 0) || strcmp(s, "ADD") == 0){

      printf("%d\t%s\toperator\n", n, s);
    }
    else {
    printf("%d\t%s\t rejected form\n",n, s) ;
    return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
