#ifndef PARSEUR_H
#define PARSEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse(FILE* file, char ***tableauNomNoeuds, unsigned int **rkMin, unsigned int **rkMax, unsigned int * n_points, unsigned int * indexResult, unsigned int * rkMaxResult, unsigned int * rkMinResult);

#endif
