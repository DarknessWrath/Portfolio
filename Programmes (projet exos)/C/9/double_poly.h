//  partie en-tête d'un module sur les polynômes à coefficients sur le type
//    double :
//  - définition de la macroconstante fixant le degré maximal,
//      POLY_DEGREE_MAX
//  - définition de la macroconstante fixant le degré du polynôme nul,
//      POLY_DEGREE_INF
//  - définition du type des polynômes, poly
//  - déclaration des fonctions
//      poly_null, poly_copy, poly_scan, poly_print
//      poly_opposite, poly_derivative,
//      poly_add, poly_multiply,
//      poly_evaluate

#ifndef DOUBLE_POLY__H
#define DOUBLE_POLY__H

//  convention pour le (nom de) type poly :
//  1) POLYNÔMES NON NULS DE DEGRÉ INFÉRIEUR OU ÉGAL À POLY_DEGREE_MAX. Toute
//    variable p du type poly pour laquelle
//    (p.degree == n)
//    &&  (p.coeff[k] == a_k pour tout entier k compris entre 0 et n)
//    est une implantation du polynôme (a_0, a_1, ..., a_n, 0, ...) de degré n
//    dès lors n <= POLY_DEGREE_MAX && a_n != 0.0
//  2) POLYNÔME NUL. Toute variable p de type poly pour laquelle
//    p.degree == POLY_DEGREE_INF
//    est une implantation du polynôme nul
//  3) EXCLUSION. Toute variable p du type poly qui ne satisfait pas
//    (p.degre >= 0 && p.degre <= POLY_DEGREE_MAX)
//    || (p.degre == POLY_DEGREE_INF)
//    n'est pas l'implantation d'un polynôme

#define POLY_DEGREE_MAX 10
#define POLY_DEGREE_INF -1

typedef struct {
  int degree;
  double coeff[POLY_DEGREE_MAX + 1];
} poly;

//  poly_null : initialise l'objet pointé par ptr au polynôme nul
extern void poly_null(poly *ptr);

//  poly_copy : initialise l'objet pointé par destptr par copie du polynôme
//    pointé par srcptr
extern void poly_copy(poly *destptr, const poly *srcptr);

//  poly_scan : initialise l'objet pointé par ptr par lecture d'une liste de
//    flottants sur l'entrée. Les flottants lus sont affectés séquentiellement
//    aux coefficients du polynôme. La fin de la liste est signifiée par la
//    marque de fin de ligne '\n'. Renvoie zéro si la liste a été correctement
//    lue et affectée. Sinon, l'objet est initialisé au polynôme nul et une
//    valeur non nulle est renvoyée
extern int poly_scan(poly *ptr);

//  poly_print : affiche le polynôme pointé par ptr dans l'ordre décroissant des
//    degrés des monômes, sans faire figurer les monômes de coefficient nul, en
//    faisant figurer l'indéterminée "X" suivie de la mention du degré du monôme
extern void poly_print(const poly *ptr);

//  poly_opposite : remplace le polynôme pointé par ptr par le polynôme opposé
extern void poly_opposite(poly *ptr);

//  poly_derivative : remplace le polynôme pointé par ptr par le polynôme dérivé
extern void poly_derivative(poly *ptr);

//  poly_advance : ajoute au polynôme pointé par destptr celui pointé par srcptr
extern void poly_add(poly *destptr, const poly *srcptr);

//  poly_multiply : multiplie le polynôme pointé par destptr par celui pointé
//    par srcptr si le degré du polynôme résultant n'excède pas POLY_DEGREE_MAX.
//    Renvoie zéro à cette condition et une valeur non nulle sinon
extern int poly_multiply(poly *destptr, const poly *srcptr);

//  poly_evaluate : renvoie l'évaluation du polynôme pointé par ptr en x en
//    appliquant la méthode de Horner
extern double poly_evaluate(const poly *ptr, double x);

#endif
