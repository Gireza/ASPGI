#include "parseur.h"
#include "saturation.h"
#include "ensemble.h"


#include <stdio.h>

int main(int argc, char** argv){
  if (argc != 2) {
    printf("erreur dans les arguments");
    return -1;
  }
 

  FILE * file = NULL; // initialisation de file
  file = fopen(argv[1], "r+"); // ouverture du fichier en lecture

  // initialisation des tableaux de rang (tableaux d'ints non signés) 
  unsigned int *rkMax; 
  unsigned int *rkMin;

  // initialisation du nombre de point
  unsigned int n_points;
  
  // utilisation de parse
  if (parse(file, &rkMin, &rkMax, &n_points) == -1) { printf("Erreur de parsage du fichier"); }

  // Fermeture du fichier
  fclose(file);

  //printf("nombre de points de l'ensemble : %d\n", n_points);
  for (unsigned int i = 0; i < puissance2(n_points); i ++){
    printf("point %d, rang %d/%d\n", i, rkMin[i], rkMax[i]);
  }

  
  // DEBUT DE LA SATURATION

  saturer(rkMin, rkMax, n_points);

  printf("après la saturation\n");
  for (unsigned int i = 0; i < puissance2(n_points); i++) {
    printf("point %d, rang %d/%d\n", i, rkMin[i], rkMax[i]);
  }  


  return 0;

}
