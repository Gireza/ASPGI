#include <stdio.h>
#include "parseur.h"

int main(int argc, char** argv){

  printf("les arguments du programme sont ");
  for (int i = 0; i < argc; i++) {
    printf("%s ", argv[i]);
  }
  printf("\n");

  FILE * file = NULL; // initialisation de file
  file = fopen("problemes/fichier.txt", "r+"); // ouverture du fichier en lecture

  // initialisation des tableaux de rang (tableaux d'ints non signés) 
  unsigned int rkMax[1] = {0}; 
  unsigned int rkMin[1] = {0};
  // initialisation des pointeurs vers les adresses des tableaux 
  unsigned int *pointeur_rkMax = *&rkMax;
  unsigned int *pointeur_rkMin = *&rkMin;

  // initialisation du nombre de point
  unsigned int n_points;
  
  // utilisation de parse
  if (parse(file, &pointeur_rkMax, &pointeur_rkMin, &n_points) == -1) { printf("Erreur de parsage du fichier"); }

  //printf("n_points = %d\n", n_points);

  return 0;

}
