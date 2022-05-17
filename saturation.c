#include "saturation.h"
#include "ensemble.h"
#include "affichage.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int verbose = 0;
char **tableauNom;

// (RS1) si X ⊆ Y et rkMin(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(X)
bool RS1(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin){
  if (estSousEnsemble(x,y) && rkMin[x] > rkMin[y]){
    appliqueRegle(verbose, "RS1", "rkMin", tableauNom[y], rkMin[y], rkMin[x]);
    rkMin[y] = rkMin[x];
    return true;
  }
  if (verbose > 0 ) printf("rs1 ");
  return false;
}

// (RS2) si Y ⊆ X et rkMin(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(Y)
bool RS2(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin){
  if (estSousEnsemble(y,x) && rkMin[y] > rkMin[x]){
    appliqueRegle(verbose, "RS2", "rkMin", tableauNom[x], rkMin[x], rkMin[y]);
    rkMin[x] = rkMin[y]; 
    return true;     
  }
  if (verbose > 0 ) printf("rs2 ");
  return false;
}

// (RS3) si  X ⊆ Y et rkMax(Y) < rKMax(X) alors rkMax(X) prend la valeur de rkMax(Y)
bool RS3(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMax){
  if (estSousEnsemble(x,y) && rkMax[y] < rkMax[x]) {
    appliqueRegle(verbose, "RS3", "rkMax", tableauNom[x], rkMax[x], rkMax[y]);
    rkMax[x] = rkMax[y];
    return true;
  }
  if (verbose > 0 ) printf("rs3 ");
  return false;
}

// (RS4) si Y ⊆ X et rkMax(Y) > rkMax(X) alors rkMax(Y) prend la valeur de rkMax(X)
bool RS4(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMax){
  if (estSousEnsemble(y,x) && rkMax[y] > rkMax[x]) {
    appliqueRegle(verbose, "RS4", "rkMax", tableauNom[y], rkMax[y], rkMax[x]);
    rkMax[y] = rkMax[x];
    return true;
  }
  if (verbose > 0 ) printf("rs4 ");
  return false;
}

// (RS5) si rkMax(X) + rkMax(Y) − rkMin(X ∩ Y) < rkMax(X ∪ Y) alors rkMax(X ∪ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∩ Y)
bool RS5(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin, unsigned int* rkMax){
  if (rkMax[x] + rkMax[y] - rkMin[intersectionEnsembles(x,y)] > 0) {
    if (rkMax[x] + rkMax[y] - rkMin[intersectionEnsembles(x,y)] < rkMax[unionEnsembles(x,y)]){
    appliqueRegle(verbose, "RS5", "rkMax", tableauNom[unionEnsembles(x,y)], rkMax[unionEnsembles(x,y)], rkMax[x] + rkMax[y] - rkMin[intersectionEnsembles(x,y)]);
    rkMax[unionEnsembles(x,y)] = rkMax[x] + rkMax[y] - rkMin[intersectionEnsembles(x,y)];
    return true;
    }
  }
  
  if (verbose > 0 ) printf("rs5 ");
  return false;
}

// (RS6) si rkMax(X) + rkMax(Y) − rkMin(X ∪ Y) < rkMax(X ∩ Y) alors rkMax(X ∩ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∪ Y)
bool RS6(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin, unsigned int* rkMax){
  if (rkMax[x] + rkMax[y] - rkMin[unionEnsembles(x,y)] > 0) {
    if (rkMax[x] + rkMax[y] - rkMin[unionEnsembles(x,y)] < rkMax[intersectionEnsembles(x,y)]){
      appliqueRegle(verbose, "RS6", "rkMax", tableauNom[intersectionEnsembles(x,y)], rkMax[intersectionEnsembles(x,y)], rkMax[x] + rkMax[y] - rkMin[unionEnsembles(x,y)]);
      rkMax[intersectionEnsembles(x,y)] = rkMax[x] + rkMax[y] - rkMin[unionEnsembles(x,y)];
      return true;
    }
  }
  if (verbose > 0 ) printf("rs6 ");
  return false;
}

// (RS7) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y)
bool RS7(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin, unsigned int* rkMax){
  if (rkMin[intersectionEnsembles(x,y)] + rkMin[unionEnsembles(x,y)] - rkMax[y] <= 4) {
    if (rkMin[intersectionEnsembles(x,y)] + rkMin[unionEnsembles(x,y)] - rkMax[y] > rkMin[x]){
      appliqueRegle(verbose, "RS7", "rkMin", tableauNom[x], rkMin[x], rkMin[intersectionEnsembles(x,y)] + rkMin[unionEnsembles(x,y)] - rkMax[y]);
      rkMin[x] = rkMin[intersectionEnsembles(x,y)] + rkMin[unionEnsembles(x,y)] - rkMax[y];
      return true;
    }
  }
  if (verbose > 0 ) printf("rs7 ");
  return false;
}

// (RS8) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X)
bool RS8(ENSEMBLE x, ENSEMBLE y, unsigned int* rkMin, unsigned int* rkMax){
  if (rkMin[intersectionEnsembles(x,y)] + rkMin[unionEnsembles(x,y)] - rkMax[x] <= 4) {
    if (rkMin[intersectionEnsembles(x,y)] + rkMin[unionEnsembles(x,y)] - rkMax[x] > rkMin[y]){
      appliqueRegle(verbose, "RS8", "rkMin", tableauNom[y], rkMin[y], rkMin[intersectionEnsembles(x,y)] + rkMin[unionEnsembles(x,y)] - rkMax[x]);
      rkMin[y] = rkMin[intersectionEnsembles(x,y)] + rkMin[unionEnsembles(x,y)] - rkMax[x];
      return true;
    }
  }
  if (verbose > 0 ) printf("rs8 ");
  return false;
}

void saturer(unsigned int * rkMin, unsigned int * rkMax, unsigned int n_points, char **tableauNomNoeuds, int pTerm) {

  unsigned int nbNoeuds = puissance2(n_points);

  tableauNom = tableauNomNoeuds;

  verbose = pTerm;

  ENSEMBLE x = 1;
  if (verbose > 0 ) printf("---|x:%d|--- ", x);

  while (x < nbNoeuds) {
    ENSEMBLE y = 1;
    if (verbose > 0 ) printf("|y:%d| ", y);
    while (y < nbNoeuds) {
      if (x != y && (RS1(x,y,rkMin) || RS3(x,y,rkMax) || RS2(x,y,rkMin) || RS4(x,y,rkMax) || RS5(x,y,rkMin,rkMax) || RS6(x,y,rkMin,rkMax) || RS7(x,y,rkMin,rkMax) || RS8(x,y,rkMin,rkMax))) {
        x = 1;
        if (verbose > 0 ) printf("(x:%d ", x);
        y = 1;
        if (verbose > 0 ) printf("y:%d) ", y);
      } else {
        y++;
        if (verbose > 0 ) printf("|y:%d| ", y);
      }
    }
    x++;
    if (verbose > 0 ) printf("\n---|x:%d|--- ", x);
  }

  if (verbose > 0 ) printf("\n\n");
}
