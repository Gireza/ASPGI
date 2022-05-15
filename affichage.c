#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ensemble.h"
#include "affichage.h"

void affichageTerminal(char ** tableauNomNoeuds, unsigned int *rkMax, unsigned int *rkMin, unsigned int n_points){
    for (unsigned int i = 1; i < puissance2(n_points); i ++){
    printf("%s %d/%d\n", tableauNomNoeuds[i], rkMax[i], rkMin[i]);
  }
  printf("\n");
}

void ecritureFichier(FILE * file, char ** tableauNomNoeuds, unsigned int *rkMax, unsigned int *rkMin, unsigned int n_points){
    fprintf(file, "\n\n");
    for (unsigned int i = 1; i < puissance2(n_points); i ++){
        fprintf(file, "%s %d/%d\n", tableauNomNoeuds[i], rkMax[i], rkMin[i]);
    }
}
