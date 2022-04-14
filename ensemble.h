#ifndef ENSEMBLE_H
#define ENSEMBLE_H

#include <stdbool.h>

typedef unsigned int ENSEMBLE;

ENSEMBLE unionEnsembles(ENSEMBLE x, ENSEMBLE y);

ENSEMBLE intersectionEnsembles(ENSEMBLE x, ENSEMBLE y);

bool estSousEnsemble(ENSEMBLE x, ENSEMBLE y);

unsigned int cardinalEnsemble(ENSEMBLE x);

#endif
