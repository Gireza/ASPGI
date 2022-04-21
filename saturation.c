#include "saturation.h"
#include "ensemble.h"
#include <stdio.h>
#include <stdbool.h>



/*
void reinitialise(){
        continueSat = false;
        y = 0;
        x = 0;
    }*/

    bool RS1(ENSEMBLE x, ENSEMBLE y, int* rkMin){
        if (estSousEnsemble(x,y) && rkMin[x] > rkMin[y]){
            rkMin[y] = rkMin[x];
            return true;
        
        }
        return false;
    }
    bool RS2(ENSEMBLE x, ENSEMBLE y, int* rkMin){
        if (estSousEnsemble(y,x) && rkMin[y] > rkMin[x]){
            rkMin[x] = rkMin[y];
            return true;
            
        }
        return false;
    }
    bool RS3(ENSEMBLE x, ENSEMBLE y, int* rkMax){
        if (estSousEnsemble(x,y) && rkMax[y] < rkMax[x]) {
            rkMax[x] = rkMax[y];
            return true;
        }
        return false;
    }
    bool RS4(ENSEMBLE x, ENSEMBLE y, int* rkMax){
        if (estSousEnsemble(y,x) && rkMax[y] > rkMax[x]){
            rkMax[y] = rkMax[x];
            return true;
        }
        return false;
    }
    bool RS5(ENSEMBLE x, ENSEMBLE y, int* rkMin, int* rkMax){
        if (rkMax[x] + rkMax[y] - rkMin[unionEnsembles(x,y)] < rkMax[intersectionEnsembles(x,y)]){
            rkMax[intersectionEnsembles(x,y)] = rkMax[x] + rkMax[y] - rkMin[unionEnsembles(x,y)];
            return true;
        }
        return false;
    }
    bool RS6(ENSEMBLE x, ENSEMBLE y, int* rkMin, int* rkMax){
        if (rkMax[x] + rkMax[y] - rkMin[unionEnsembles(x,y)] < rkMax[unionEnsembles(x,y)]){
            rkMax[unionEnsembles(x,y)] = rkMax[x] + rkMax[y] - rkMin[intersectionEnsembles(x,y)];
            return true;
        }
        return false;
    }
    bool RS7(ENSEMBLE x, ENSEMBLE y, int* rkMin, int* rkMax){
        if (rkMin[unionEnsembles(x,y)] + rkMin[intersectionEnsembles(x,y)] - rkMax[y] > rkMin[x]){
            rkMin[x] = rkMin[unionEnsembles(x,y)] + rkMin[intersectionEnsembles(x,y)] - rkMax[y];
            return true;
        }
        return false;
    }
    bool RS8(ENSEMBLE x, ENSEMBLE y, int* rkMin, int* rkMax){
        if (rkMin[unionEnsembles(x,y)] + rkMin[intersectionEnsembles(x,y)] - rkMax[x] > rkMin[y]){
            rkMin[y] = rkMin[unionEnsembles(x,y)] + rkMin[intersectionEnsembles(x,y)] - rkMax[x];
            return true;
        }
        return false;
    }

void saturer(unsigned int* rkMin, unsigned int* rkMax, unsigned int n_points) {

    unsigned int nbNoeuds = puissance2(n_points) - 1;

    bool continueSat = true;
    ENSEMBLE x = 1;

    while (x <= nbNoeuds)
    {
        ENSEMBLE y = 1;
        while (y <= nbNoeuds)
        {
            // (RS1) si X ⊆ Y et rkMin(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMax rkMin(X)
            if (RS1(x,y,rkMin) && continueSat)
            {
                rkMin[y] = rkMin[x];
                
            }
            // fin (RS1)

            // (RS3) si  X ⊆ Y et rkMax(Y) < rKMax(X) alors rkMax(X) prend la valeur de rkMax(Y)
            else if (RS3(x,y,rkMax) && continueSat)
            {
                rkMax[x] = rkMax[y];
                
            }
            // fin (RS3)

            // (RS2) si Y ⊆ X et rkMin(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(Y)
            else if (RS2(x,y,rkMin) && continueSat)
            {
                rkMin[x] = rkMin[y];
            

            }
            // fin (RS2)

            // (RS4) si Y ⊆ X et rkMax(Y) > rkMax(X) alors rkMax(Y) prend la valeur de rkMax(X)
            else if (RS4(x,y,rkMax) && continueSat)
            {
                rkMax[y] = rkMax[x];
                
            }
            // fin (RS4)

            // (RS5) si rkMax(X) + rkMax(Y) - rkMin(x & y) < rkMax(x | y) alors rkMax(x | y) prend la valeur de rkMax(X) + rkMax(Y) - rkMin(x & y)
            // (RS5) si rkMax(X) + rkMax(Y) − rkMin(X ∩ Y) < rkMax(X ∪ Y) alors rkMax(X ∪ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∩ Y)
            else if (RS5(x,y,rkMin,rkMax) && continueSat)
            {
                rkMax[intersectionEnsembles(x,y)] = rkMax[x] + rkMax[y] - rkMin[unionEnsembles(x,y)];
                
            }
            // fin (RS5)

            // (RS6) si rkMax(X) + rkMax(Y) - rkMin(x | y) < rkMax(x & y) alors rkMax(x & y) prend la valeur de rkMax(X) + rkMax(Y) - rkMin(x | y)
            // (RS6) si rkMax(X) + rkMax(Y) − rkMin(X ∪ Y) < rkMax(X ∩ Y) alors rkMax(X ∩ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∪ Y)
            else if (RS6(x,y,rkMin,rkMax) && continueSat)
            {
                rkMax[unionEnsembles(x,y)] = rkMax[x] + rkMax[y] - rkMin[intersectionEnsembles(x,y)];
                
            }
            // fin (RS6)

            // (RS7) si rkMin(x & y) + rkMin(x | y) - rkMax(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(x & y) + rkMin(x | y) - rkMax(Y)
            // (RS7) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y)
            else if (RS7(x,y,rkMin,rkMax) && continueSat)
            {
                rkMin[x] = rkMin[unionEnsembles(x,y)] + rkMin[intersectionEnsembles(x,y)] - rkMax[y];
                

            }
            // fin (RS7)

            // (RS8) si rkMin(x & y) + rkMin(x | y) - rkMax(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(x & y) + rkMin(x | y) - rkMax(X)
            // (RS8) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X)
            else if (RS8(x,y,rkMin,rkMax) && continueSat)
            {
                rkMin[y] = rkMin[unionEnsembles(x,y)] + rkMin[intersectionEnsembles(x,y)] - rkMax[x];
                
            }
            // fin (RS8)
            y++;
        }
        continueSat = true;
        x++;
    }
    
  for (unsigned int i = 0; i < n_points; i++) {
    // TODO
    printf("point %d, rang %d/%d", i, rkMin[i], rkMax[i]);
  }
  
}
