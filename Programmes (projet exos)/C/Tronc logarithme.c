#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <math.h>
double fonc(double x, int n);


int main(void) {

  double x;
  int n;
  while(scanf("%lf%d", &x, &n)==2){
    printf("%lf", fonc(x,n));
   }
  return EXIT_SUCCESS;
}

double fonc(double x, int n){
  int k=1;
  double t=x;
  double s=x;

  while(k<=n) {
    ++k;
    t*=-(x) * (k-1)/k;
    s+=t;
  }
  return s;
}

// E: envoie la troncature à l’ordre n du développement en série au voisinage de
// 0 de la fonction x->ln(1+x)
// AE:n=>1
//AS: s = somme de 1 à n, (-1)^j+1 x^j/j
//IB: 1<=k && k<=n && t=(-1)^k+1 x^k/k && somme de 1 à n
//QC:k
