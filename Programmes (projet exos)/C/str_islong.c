#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
int main(void) {
  char s[32 + 1];
  int n = 0;
  char *p;

  while (scanf("%32s", s) == 1) {
    ++n;
    errno = 0;

    long int x = strtol(s, &p, 10);
    if (*p == '\0' && errno == 0) {
      printf("%d\t%s\tlong=%ld\n", n, s, x);
    } else {
      printf("%d\t%s\tnot long\n", n, s);
    }
  }
  return EXIT_SUCCESS;
}
