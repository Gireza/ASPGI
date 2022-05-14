#include "saturation.h"
#include "ensemble.h"
#include <stdio.h>
#include <stdbool.h>

// (RS1) si X ⊆ Y et rkMin(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(X)
bool RS1(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin){
  if (estSousEnsemble(x,y) && rkMin[x] > rkMin[y]){
    rkMin[y] = rkMin[x];
    printf("-----RS1----- ");
    return true;
  }
  printf("rs1-false ");
  return false;
}

// (RS2) si Y ⊆ X et rkMin(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(Y)
bool RS2(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin){
  if (estSousEnsemble(y,x) && rkMin[y] > rkMin[x]){
    rkMin[x] = rkMin[y];
    printf("-----RS2----- "); 
    return true;     
  }
  printf("rs2-false ");
  return false;
}

// (RS3) si  X ⊆ Y et rkMax(Y) < rKMax(X) alors rkMax(X) prend la valeur de rkMax(Y)
bool RS3(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMax){
  if (estSousEnsemble(x,y) && rkMax[y] < rkMax[x]) {
    rkMax[x] = rkMax[y];
    printf("-----RS3----- ");
    return true;
  }
  printf("rs3-false ");
  return false;
}

// (RS4) si Y ⊆ X et rkMax(Y) > rkMax(X) alors rkMax(Y) prend la valeur de rkMax(X)
bool RS4(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMax){
  if (estSousEnsemble(y,x) && rkMax[y] > rkMax[x]) {
    rkMax[y] = rkMax[x];
    printf("-----RS4----- ");
    return true;
  }
  printf("rs4-false ");
  return false;
}

// (RS5) si rkMax(X) + rkMax(Y) − rkMin(X ∩ Y) < rkMax(X ∪ Y) alors rkMax(X ∪ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∩ Y)
bool RS5(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin, unsigned int* rkMax){
  if (rkMax[x] + rkMax[y] - rkMin[intersectionEnsembles(x,y)] < rkMax[unionEnsembles(x,y)]){
    printf("-----RS5----- ");
    return true;
  }
  printf("rs5-false ");
  return false;
}

// (RS6) si rkMax(X) + rkMax(Y) − rkMin(X ∪ Y) < rkMax(X ∩ Y) alors rkMax(X ∩ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∪ Y)
bool RS6(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin, unsigned int* rkMax){
  if (rkMax[x] + rkMax[y] - rkMin[unionEnsembles(x,y)] < rkMax[intersectionEnsembles(x,y)]){
    printf("-----RS6----- ");
    return true;
  }
  printf("rs6-false ");
  return false;
}

// (RS7) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y)
bool RS7(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin, unsigned int* rkMax){
  if (rkMin[intersectionEnsembles(x,y)] + rkMin[unionEnsembles(x,y)] - rkMax[y] > rkMin[x]){
    rkMin[x] = rkMin[intersectionEnsembles(x,y)] + rkMin[unionEnsembles(x,y)] - rkMax[y];
    printf("-----RS7----- ");
    return true;
  }
  printf("rs7-false ");
  return false;
}

// (RS8) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X)
bool RS8(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin, unsigned int* rkMax){
  if (rkMin[intersectionEnsembles(x,y)] + rkMin[unionEnsembles(x,y)] - rkMax[x] > rkMin[y]){
    rkMin[y] = rkMin[intersectionEnsembles(x,y)] + rkMin[unionEnsembles(x,y)] - rkMax[x];
    printf("-----RS8----- ");
    return true;
  }
  printf("rs8-false ");
  return false;
}

void saturer(unsigned int * rkMin, unsigned int * rkMax, unsigned int n_points) {

  unsigned int nbNoeuds = puissance2(n_points);
  printf("%d\n", n_points);
  for (unsigned int i = 1; i < puissance2(n_points); i ++){
    printf("rang %d/%d\n", rkMax[i], rkMin[i]);
  }
  printf("\n");

  ENSEMBLE x = 1;

  while (x < nbNoeuds) {
    ENSEMBLE y = 1;
    while (y < nbNoeuds) {
      if (x != y && (RS1(x,y,rkMin) || RS3(x,y,rkMax) || RS2(x,y,rkMin) || RS4(x,y,rkMax) || RS5(x,y,rkMin,rkMax) || RS6(x,y,rkMin,rkMax) || RS7(x,y,rkMin,rkMax) || RS8(x,y,rkMin,rkMax))) {
        x = 1;
        y = 1;
        printf("IF ");
      } else {
        y++;
        printf("y:%d ", y);
      }
    }
    x++;
    printf("---[X]---:%d ", x);
  }

  /* for (unsigned int i = 1; i < puissance2(n_points); i ++){
    printf("rang %d/%d\n", rkMax[i], rkMin[i]);
  } */
}
