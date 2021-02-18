#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct day day;

//  get_day : si le temps courant n'est pas disponible, ne modifie pas l'objet
//    *dptr et renvoie une valeur non nulle. Sinon, affecte à l'objet *dptr les
//    données temporelles année, mois, quantième et jour de la semaine du temps
//    courant et renvoie zéro
int get_day(day *dptr);

//  put_day : écrit sur la sortie standard les données temporelles année A,
//    mois M, quantième Q et jour de la semaine J mémorisées dans l'objet *dptr
//    selon la norme en typographie française "litt(J) Q litt(M) A" où litt(x)
//    signifie le nom associé à x puis provoque un passage à la ligne suivante
void put_day(const day *dptr);

struct day {
  int gyear;  // année grégorienne
  int mon;    // mois depuis janvier, [0, 11]
  int mday;   // quantième, [1, 31]
  int wday;   // jours depuis dimanche, [0, 6]
};

int main(void) {
  day d;
  if (get_day(&d) != 0) {
    fprintf(stderr, "Erreur : temps indisponible\n");
    return EXIT_FAILURE;
  }
  put_day(&d);
  return EXIT_SUCCESS;
}
