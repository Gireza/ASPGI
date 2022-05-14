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

  // initialisation du tableau de noms d'ensembles
  char **tableauNomNoeuds;

  // initialisation des tableaux de rang (tableaux d'ints non signés) 
  unsigned int *rkMax; 
  unsigned int *rkMin;

  // initialisation des variables stockant le résultat 
  unsigned int  indexResult;
  unsigned int  rkMaxResult;
  unsigned int  rkMinResult;

  // initialisation du nombre de point
  unsigned int n_points;
  
  // utilisation de parse
  if (parse(file, &tableauNomNoeuds, &rkMin, &rkMax, &n_points, &indexResult, &rkMaxResult, &rkMinResult) == -1) { printf("Erreur de parsage du fichier"); }

  // Fermeture du fichier
  fclose(file);

  //printf("nombre de points de l'ensemble : %d\n", n_points);
  for (unsigned int i = 1; i < puissance2(n_points); i ++){
    printf("%s %d/%d\n", tableauNomNoeuds[i], rkMax[i], rkMin[i]);
  }

  
  // DEBUT DE LA SATURATION

  saturer(rkMin, rkMax, n_points);

  printf("Après saturation :\n");
  for (unsigned int i = 1; i < puissance2(n_points); i++) {
    printf("%s %d/%d\n", tableauNomNoeuds[i], rkMax[i], rkMin[i]);
  }  


  return 0;

}
