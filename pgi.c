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
  unsigned int *rkMax; 
  unsigned int *rkMin;

  // initialisation du nombre de point
  unsigned int n_points;
  
  // utilisation de parse
  if (parse(file, &rkMin, &rkMax, &n_points) == -1) { printf("Erreur de parsage du fichier"); }

  // Fermeture du fichier
  fclose(file);

  //printf("nombre de points de l'ensemble : %d\n", n_points);
  for (unsigned int i = 0; i < 16; i ++){
    printf("élément %d de rkMax : %d\n", i, rkMax[i]);
  }

  for (unsigned int i = 0; i < 16; i ++){
    printf("élément %d de rkMin : %d\n", i, rkMin[i]);
  }


  // DEBUT DE LA SATURATION


  return 0;

}
