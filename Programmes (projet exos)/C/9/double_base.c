#include "double_base.h"
#include <stdio.h>
#include <math.h>

int double_scan(double *ptr) {
  int c = fgetc(stdin);
  return
      ungetc(c, stdin) == EOF ? EOF :
      c == '\n' ? 0 :
      fscanf(stdin, "%lf", ptr) == 1 ? 1 : EOF;
}

void double_print(double x) {
  printf(floor(x) == x ? "%.0lf" : "%lf", x);
}

void double_mo_print(double coeff, int degree, bool first) {
  if (coeff >= 0.0) {
    if (! first) {
      printf("+ ");
    }
  } else {
    printf("-");
    if (! first) {
      printf(" ");
    }
  }
  if (fabs(coeff) != 1.0 || degree == 0) {
    double_print(fabs(coeff));
    if (fabs(coeff) != 1.0) {
      printf(" ");
    }
  }
  if (degree >= 1) {
    printf("X");
    if (degree >= 2) {
      printf("^%d", degree);
    }
  }
}
