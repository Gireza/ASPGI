#include "parseur.h"

/* determine le nombre de lignes du fichier 
 */
int calculeNbLignes(FILE * file){

  char buffer[500 + 1] = "0"; // création d'un buffer
  int nbLignes = 0;

  // parcours du fichier jusqu'à la dernière ligne
  while (fgets(buffer, 500, file) != NULL) {
    nbLignes++;
  }

  return nbLignes;
}

int parse(FILE * file, unsigned int** rkMin, unsigned int** rkMax, unsigned int* n_points){

  if (file == NULL) { return -1; }
  
  // TODO
  *rkMin = NULL;
  *rkMax = NULL;
  *n_points = 0;
  
  int nbLignes = calculeNbLignes(file);

  printf("nombre de lignes du fichier : %d\n", nbLignes);

  return 0;
}
