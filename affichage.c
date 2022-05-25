#include <stdlib.h>
#include <string.h>
#include "ensemble.h"
#include "affichage.h"

unsigned int compteurReglesAppliquees = 0;

/*
Affiche les ensembles et leurs rangs dans la console
*/
void affichageTerminal(char ** tableauNomNoeuds, unsigned int *rkMax, unsigned int *rkMin, unsigned int n_points){
    for (unsigned int i = 1; i < puissance2(n_points); i ++){
    printf("%s %d/%d\n", tableauNomNoeuds[i], rkMax[i], rkMin[i]);
  }
  printf("\n");
}

/*
Ecrit les ensembles et leurs rangs dans un fichier
*/
void ecritureFichier(FILE * file, char ** tableauNomNoeuds, unsigned int *rkMax, unsigned int *rkMin, unsigned int n_points){
    //fprintf(file, "\n\n");
    for (unsigned int i = 1; i < puissance2(n_points); i ++){
        fprintf(file, "%s %d/%d\n", tableauNomNoeuds[i], rkMax[i], rkMin[i]);
    }
}


void appliqueRegle(int verbose, char* nomRegle, char* ensembleApplique, char* rangModifie, unsigned int ancienneValeur, unsigned int nouvelleValeur){

    // affichage des info
    /* if (verbose == 1 ){
        printf("-----%s----- ", nomRegle);
        return;
    } */

    // affichage du debug 
    if (verbose == 2){
        printf("------la règle %s est appliquée : %s %s %d -> %d ", nomRegle, ensembleApplique, rangModifie, ancienneValeur, nouvelleValeur);
    }

    compteurReglesAppliquees++;

}

void afficherCompteurReglesAppliquees(){
    printf("Nombre de règles appliquées : %d\n\n", compteurReglesAppliquees);
};
