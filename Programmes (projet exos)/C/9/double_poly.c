#include "double_base.h"
#include "double_poly.h"
#include <stdio.h>

#define FUN_SUCCESS 0
#define FUN_FAILURE 1

void poly_null(poly *ptr) {
  ptr -> degree = POLY_DEGREE_INF;
}

void poly_copy(poly *destptr, const poly *srcptr) {
  if (destptr != srcptr) {
    //  IB : -1 <= k && k <= srcptr -> degree
    //    && srcptr -> coeff[k + 1 ... srcptr -> degree]
    //        == destptr -> coeff[k + 1 ... srcptr -> degree]
    //  QC : k
    for (int k = srcptr -> degree; k >= 0; --k) {
      destptr -> coeff[k] = srcptr -> coeff[k];
    }
    destptr -> degree = srcptr -> degree;
  }
}

int poly_scan(poly *ptr) {
  ptr -> degree = POLY_DEGREE_INF;
  int k = -1;
  double v;
  int rs = double_scan(&v);
  //  IB : -1 <= k && k <= POLY_DEGREE_MAX
  //    && les composants d'indices 0 à k du tableau ptr -> coeff ont été
  //        initialisés par lecture de valeurs sur l'entrée
  //    && rs == (dernière valeur renvoyée par double_scan(&v))
  //    && v == (dernière valeur lue si rs == 1)
  //  QC : nombre d'appels à scanf
  while (rs == 1 && k < POLY_DEGREE_MAX) {
    ++k;
    ptr -> coeff[k] = v;
    rs = double_scan(&v);
  }
  if (rs != 0) {
    return FUN_FAILURE;
  }
  //  AVEC : K valeur initiale de k
  //  IB : -1 <= k && k <= K
  //    && les composants d'indices 0 à K du tableau ptr -> coeff ont été
  //        initialisés par lecture de valeurs sur l'entrée
  //    && les composants d'indices k + 1 à K de ptr -> coeff sont nuls
  //  QC : k
  while (k >= 0 && ptr -> coeff[k] == 0.0) {
    --k;
  }
  ptr -> degree = k;
  return FUN_SUCCESS;
}

void poly_print(const poly *ptr) {
  if (ptr -> degree == POLY_DEGREE_INF) {
    printf("0");
  } else {
    bool first = true;
    //  IB : -1 <= k && k <= ptr -> degree
    //    && les monômes non nuls des degrés k + 1 à ptr -> degree du polynôme
    //        associé à ptr ont été affichés, en décroissant selon leurs degrés
    //    && first == aucun monôme n'a encore été affiché
    for (int k = ptr -> degree; k >= 0; --k) {
      double a = ptr -> coeff[k];
      if (a != 0.0) {
        if (! first) {
          printf(" ");
        }
        double_mo_print(a, k, first);
        first = false;
      }
    }
  }
}

void poly_opposite(poly *ptr) {
  //IB : 0 <= k && k <= ptr -> degree ?
  int k = ptr -> degree;
  double coeff[POLY_DEGREE_MAX + 1];
    while (k>0) {
     coeff[k] *= -1;
     --k;
    }
}

void poly_derivative(poly *ptr) {
  if (ptr -> degree > POLY_DEGREE_INF) {
    int k = 0;
     while(k < ptr -> degree) {
       ptr -> coeff[k] = ptr -> coeff[k+1] * (k+1);
        k += 1;
      }
    ptr -> degree -= 1;
  }
}

void poly_add(poly *destptr, const poly *srcptr) {
  if (destptr != srcptr) {
    int k = 0;
        while (destptr != srcptr) {
          srcptr -> destptr;
        }
   }

}

int poly_multiply(poly *destptr, const poly *srcptr) {
  return FUN_FAILURE;
}
/*
double poly_evaluate(const poly *ptr, double x) {
  int k = ptr -> degree;
  double s = 0;

  // IB: 0<=k <= p et la somme est égale à p[k...|p|-1](x)
  // QC: k
    while(k>0) {
    --k;
    s = (s * x + ptr -> coeff[k]);
    }

  return s;
}
*/
double poly_evaluate(const poly *ptr, double x) {
  const double *p = ptr -> coeff  + ptr -> degree + 1;
  double s = 0;

  // IB: 0<=k <= p et la somme est égale à p[k...|p|-1](x)
  // QC: kq
    while(p > ptr -> coeff) {
      --p;
    s = (s * x + *p);
    }
  return s;
}
