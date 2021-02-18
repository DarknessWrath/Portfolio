//  fonctions pour les fichiers binaires homogènes de nat

#ifndef FNAT__H
#define FNAT__H

#include "nat.h"
#include <stdio.h>

//  fnat_print : affiche le contenu du fichier homogène de nat associé au flot
//    contrôlé par l'objet pointé par stream. Renvoie zéro en cas de succès, une
//    valeur non nulle en cas d'échec
extern int fnat_print(FILE *stream);

//  fnat_index_to_value : cherche dans le fichier homogène de nat associé au
//    flot contrôlé par l'objet pointé par stream le composant d'indice index.
//    En cas de succès, affecte la valeur du composant à l'objet pointé par
//    valueptr et renvoie zéro. En cas d'échec, renvoie une valeur non nulle
//    sans avoir modifié l'objet pointé par valueptr
extern int fnat_index_to_value(FILE *stream, long int index, nat *valueptr);

//  fnat_value_to_index : cherche dans le fichier homogène de nat associé au
//    flot contrôlé par l'objet pointé par stream un composant de valeur value.
//    En cas de succès, affecte à l'objet pointé par indexptr l'indice de la
//    première occurrence du composant et renvoie zéro. En cas d'échec, renvoie
//    une valeur non nulle sans avoir modifié l'objet pointé par indexptr
extern int fnat_value_to_index(FILE *stream, nat value, long int *indexptr);

//  fnat_open_collatz : ouvre le fichier homogène de nat de nom la chaine
//    pointée par filename en mode "w+b" et lui donne comme contenu le préfixe
//    de longueur length de la suite de Collatz de germe seed. Renvoie un
//    pointeur vers l'objet contrôlant le flot en cas de succès, NULL en cas
//    d'échec
extern FILE *fnat_open_collatz(const char *filename, nat seed, long int length);

#endif
