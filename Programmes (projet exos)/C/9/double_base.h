//  partie en-tête d'un module sur le type double :
//  - déclaration des fonctions
//      double_scan,
//      double_print,
//      double_mo_print

#ifndef DOUBLE_BASE__H
#define DOUBLE_BASE__H

#include <stdbool.h>

//  double_scan : tente de lire une valeur flottante de type double sur l'entrée
//    standard. En cas de succès, affecte la valeur lue à l'objet pointé par ptr
//    et renvoie une valeur strictement positive. En cas d'échec, renvoie zéro
//    si une fin de ligne a été détectée à la position courante ; sinon, renvoie
//    EOF
extern int double_scan(double *ptr);

//  double_print : affiche la valeur x sur la sortie standard sans partie
//    décimale si cette valeur est entière
extern void double_print(double x);

//  double_mo_print : affiche le monôme de coefficient coeff et de degré degree
//    sur la sortie standard. Si first vaut true et si coeff est strictement
//    négatif, le signe (-) de coeff est collé à l'affichage de sa valeur
//    absolue. Si first vaut false, le signe (+ ou -) et l'affichage de la
//    valeur absolue de coeff sont séparés par une espace
extern void double_mo_print(double coeff, int degree, bool first);

#endif
