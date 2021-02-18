#include <stdlib.h>
#include <stdio.h>

typedef struct timeofday timeofday;





//  get_timeofday : attend sur l'entrée standard trois données temporelles
//    heures, minutes et secondes, dans cet ordre. Si l'une de ces trois données
//    n'a pu être lue ou si elle n'appartient pas aux intervalles définis par le
//    BIPM, l'objet *tptr n'est pas modifié et la fonction renvoie une valeur
//    non nulle. Sinon, les données temporelles sont affectées à l'objet *tptr
//    et la fonction renvoie zéro
int get_timeofday(timeofday *tptr);

//  put_timeofday : écrit sur la sortie standard les données temporelles heures
//    H, minutes M et secondes S mémorisées dans l'objet *tptr selon la norme en
//    typographie française "H h M min S s" puis provoque un passage à la ligne
//    suivante
void put_timeofday(const timeofday *tptr);



struct timeofday {


  int hour; // heures depuis minuit, [0, 23]
  int min;  // minutes après l'heure, [0, 59]
  int sec;  // secondes après la minute, [0, 60], avec 60 pour la seconde
            //    intercalaire qui peut être rajoutée (ou retranchée) à la fin
            //    des mois de juin ou de décembre
};

int main(void) {
  timeofday t;
  if (get_timeofday(&t) != 0) {
    fprintf(stderr, "Erreur : donnée heures, minutes ou secondes illégale\n");
    return EXIT_FAILURE;
  }
  put_timeofday(&t);
  return EXIT_SUCCESS;
}
#define   HOUR 23
#define   MIN 60
#define   SEC 59

int get_timeofday(timeofday *tptr){
  int h=0;
  int m=0;
  int s=0;

  if (scanf("%d%d%d", &h, &m, &s) == 3){
    if(h >= 0 && h <= HOUR &&  m >= 0 && m <= MIN && s >= 0 && s <= SEC){
      tptr -> hour = h;
      printf("bruh");
    }
  }
  return 0;
}




























