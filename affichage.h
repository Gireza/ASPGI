#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <stdio.h>

void affichageTerminal(char ** tableauNomNoeuds, unsigned int *rkMax, unsigned int *rkMin, unsigned int n_points);

void ecritureFichier(FILE * file, char ** tableauNomNoeuds, unsigned int *rkMax, unsigned int *rkMin, unsigned int n_points);

void appliqueRegle(int verbose, char* nomRegle, char* ensembleApplique, char* rangModifie, unsigned int ancienneValeur, unsigned int nouvelleValeur);

void afficherCompteurReglesAppliquees();

#endif