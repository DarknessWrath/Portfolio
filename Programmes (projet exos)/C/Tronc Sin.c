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
  int k=0;
  double t=x;
  double s=x;

  while(k<=n) {
    ++k;
    t*=(-x*x)/((2*k)*(2*k+1));
    s+=t;
  }
  return s;
}

// E: envoie la troncature à l’ordre n du développement en série au voisinage de
// 0 de la fonction x->sin(x)
// AE:n=>1
//AS: s
//IB: 0<=k && k<=n && t= && somme de 0 à n
//QC:k
