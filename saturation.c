#include "saturation.h"
#include "ensemble.h"
#include <stdio.h>
#include <stdbool.h>

// (RS1) si X ⊆ Y et rkMin(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMax rkMin(X)
bool RS1(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin){
  if (estSousEnsemble(x,y) && rkMin[x] > rkMin[y]){
    rkMin[y] = rkMin[x];
    return true;
        
  }
  return false;
}

// (RS2) si Y ⊆ X et rkMin(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(Y)
bool RS2(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin){
  if (estSousEnsemble(y,x) && rkMin[y] > rkMin[x]){
    rkMin[x] = rkMin[y];
    return true;
            
  }
  return false;
}

// (RS3) si  X ⊆ Y et rkMax(Y) < rKMax(X) alors rkMax(X) prend la valeur de rkMax(Y)
bool RS3(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMax){
  if (estSousEnsemble(x,y) && rkMax[y] < rkMax[x]) {
    rkMax[x] = rkMax[y];
    return true;
  }
  return false;
}

// (RS4) si Y ⊆ X et rkMax(Y) > rkMax(X) alors rkMax(Y) prend la valeur de rkMax(X)
bool RS4(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMax){
  if (estSousEnsemble(y,x) && rkMax[y] > rkMax[x]) {
    rkMax[y] = rkMax[x];
    return true;
  }
  return false;
}

// (RS5) si rkMax(X) + rkMax(Y) - rkMin(x & y) < rkMax(x | y) alors rkMax(x | y) prend la valeur de rkMax(X) + rkMax(Y) - rkMin(x & y)
// (RS5) si rkMax(X) + rkMax(Y) − rkMin(X ∩ Y) < rkMax(X ∪ Y) alors rkMax(X ∪ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∩ Y)
bool RS5(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin, unsigned int* rkMax){
  if (rkMax[x] + rkMax[y] - rkMin[unionEnsembles(x,y)] < rkMax[intersectionEnsembles(x,y)]){
    rkMax[intersectionEnsembles(x,y)] = rkMax[x] + rkMax[y] - rkMin[unionEnsembles(x,y)];
    return true;
  }
  return false;
}

// (RS6) si rkMax(X) + rkMax(Y) - rkMin(x | y) < rkMax(x & y) alors rkMax(x & y) prend la valeur de rkMax(X) + rkMax(Y) - rkMin(x | y)
// (RS6) si rkMax(X) + rkMax(Y) − rkMin(X ∪ Y) < rkMax(X ∩ Y) alors rkMax(X ∩ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∪ Y)
bool RS6(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin, unsigned int* rkMax){
  if (rkMax[x] + rkMax[y] - rkMin[unionEnsembles(x,y)] < rkMax[unionEnsembles(x,y)]){
    rkMax[unionEnsembles(x,y)] = rkMax[x] + rkMax[y] - rkMin[intersectionEnsembles(x,y)];
    return true;
  }
  return false;
}

// (RS7) si rkMin(x & y) + rkMin(x | y) - rkMax(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(x & y) + rkMin(x | y) - rkMax(Y)
// (RS7) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y)
bool RS7(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin, unsigned int* rkMax){
  if (rkMin[unionEnsembles(x,y)] + rkMin[intersectionEnsembles(x,y)] - rkMax[y] > rkMin[x]){
    rkMin[x] = rkMin[unionEnsembles(x,y)] + rkMin[intersectionEnsembles(x,y)] - rkMax[y];
    return true;
  }
  return false;
}

// (RS8) si rkMin(x & y) + rkMin(x | y) - rkMax(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(x & y) + rkMin(x | y) - rkMax(X)
// (RS8) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X)
bool RS8(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin, unsigned int* rkMax){
  if (rkMin[unionEnsembles(x,y)] + rkMin[intersectionEnsembles(x,y)] - rkMax[x] > rkMin[y]){
    rkMin[y] = rkMin[unionEnsembles(x,y)] + rkMin[intersectionEnsembles(x,y)] - rkMax[x];
    return true;
  }
  return false;
}

void saturer(unsigned int* rkMin, unsigned int* rkMax, unsigned int n_points) {

  unsigned int nbNoeuds = puissance2(n_points) - 1;

  ENSEMBLE x = 1;

  while (x <= nbNoeuds) {
    ENSEMBLE y = 1;
    while (y <= nbNoeuds) {
      if (RS1(x,y,rkMin) || RS3(x,y,rkMax) || RS2(x,y,rkMin) || RS4(x,y,rkMax) || RS5(x,y,rkMin,rkMax) || RS6(x,y,rkMin,rkMax) || RS7(x,y,rkMin,rkMax) || RS8(x,y,rkMin,rkMax)) {
          x = 1;
          y = 1;
        } else {
          y++;
        }
        x++;
    }
    
    for (unsigned int i = 0; i < n_points; i++) {
      // TODO
      printf("point %d, rang %d/%d", i, rkMin[i], rkMax[i]);
    }
  
  }
}
