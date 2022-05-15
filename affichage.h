#ifndef AFFICHAGE_H
#define AFFICHAGE_H

void affichageTerminal(char ** tableauNomNoeuds, unsigned int *rkMax, unsigned int *rkMin, unsigned int n_points);

void ecritureFichier(FILE * file, char ** tableauNomNoeuds, unsigned int *rkMax, unsigned int *rkMin, unsigned int n_points);

#endif