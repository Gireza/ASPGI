#ifndef ENSEMBLE_H
#define ENSEMBLE_H

#include <stdbool.h>

typedef unsigned int ENSEMBLE;

unsigned int puissance2(unsigned int n);

ENSEMBLE unionEnsembles(ENSEMBLE x, ENSEMBLE y);

ENSEMBLE intersectionEnsembles(ENSEMBLE x, ENSEMBLE y);

bool estSousEnsemble(ENSEMBLE x, ENSEMBLE y);

unsigned int cardinal(ENSEMBLE x);

#endif
