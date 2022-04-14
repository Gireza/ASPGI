#include "ensemble.h"

unsigned int puissance2(unsigned int n){
  return 1 << n;
}

unsigned int logarithme2(unsigned int n){
  unsigned int l = 0;
  while (puissance2(l) < n){
    l++;
  }
  return l;
}

ENSEMBLE unionEnsembles(ENSEMBLE x, ENSEMBLE y) {
  return(x & y);
}

ENSEMBLE intersectionEnsembles(ENSEMBLE x, ENSEMBLE y) {
  return (x | y);
}

bool estSousEnsemble(ENSEMBLE x, ENSEMBLE y) {
  return unionEnsembles(x, y) == x;
}

/* prend l'indice de l'ensemble dans le tableau dont on veux connaitre
   le cardinal et renvoie ce cardinal */
unsigned int cardinal(ENSEMBLE x) {
  unsigned int nbBits = logarithme2(x) + 1;
  unsigned int nombreDeUn = 0;
  // parcour des bits de nbBits
  for (unsigned int bit = 1 ; bit <= nbBits ; bit++) {

    // si le premier bit est égale à 1, on incrémente nbUns
    if (x % 2 == 1) {
      nombreDeUn++;
    }

    // on change le bit considéré par décalage à droite bit à bit (opérateur bitwise)
    x = x >> 1;
  }

  return nombreDeUn;
}
