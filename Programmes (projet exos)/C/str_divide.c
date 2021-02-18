#include <stdlib.h>
#include <stdio.h>

int main(void) {
  char s[11 + 1];
  int n = 0;
  while (scanf("%11s", s) == 1) {
    ++n;
    printf("%d\t%s\n", n, s);
  }
  return EXIT_SUCCESS;
}
