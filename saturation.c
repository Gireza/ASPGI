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

    bool RS1(int x, int y, int rkMinx, int rkMiny){
        if (estSousEnsemble(x,y) && rkMinx > rkMiny){
            return true;
        }
    }
    bool RS2(int x, int y, int rkMiny, int rkMinx){
        if (estSousEnsemble(y,x) && rkMiny > rkMinx){
            return true;
        }
    }
    bool RS3(int x, int y, int rkMaxy, int rkMaxx){
        if (estSousEnsemble(x,y) && rkMaxy < rkMaxx) {
            return true;
        }
    }
    bool RS4(int x, int y, int rkMaxy, int rkMaxx){
        if (estSousEnsemble(y,x) && rkMaxy > rkMaxx){
            return true;
        }
    }
    bool RS5(int rkMaxx, int rkMaxy,int rkMinunion, int rkMaxinter){
        if (rkMaxx + rkMaxy - rkMinunion < rkMaxinter){
            return true;
        }
    }
    bool RS6(int rkMaxx, int rkMaxy,int rkMininter, int rkMaxunion){
        if (rkMaxx + rkMaxy - rkMininter < rkMaxunion){
            return true;
        }
    }
    bool RS7(int rkMinunion, int rkMininter,int rkMaxy, int rkMinx){
        if (rkMinunion + rkMininter - rkMaxy > rkMinx){
            return true;
        }
    }
    bool RS8(int rkMinunion, int rkMininter,int rkMaxx, int rkMiny){
        if (rkMinunion + rkMininter - rkMaxx > rkMiny){
            return true;
        }
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
            if (RS1(x,y,rkMin[x],rkMin[y]) && continueSat)
            {
                rkMin[y] = rkMin[x];
                
            }
            // fin (RS1)

            // (RS3) si  X ⊆ Y et rkMax(Y) < rKMax(X) alors rkMax(X) prend la valeur de rkMax(Y)
            else if (RS3(x,y,rkMax[y],rkMax[x]) && continueSat)
            {
                rkMax[x] = rkMax[y];
                
            }
            // fin (RS3)

            // (RS2) si Y ⊆ X et rkMin(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(Y)
            else if (RS2(x,y,rkMin[y],rkMin[x]) && continueSat)
            {
                rkMin[x] = rkMin[y];
            

            }
            // fin (RS2)

            // (RS4) si Y ⊆ X et rkMax(Y) > rkMax(X) alors rkMax(Y) prend la valeur de rkMax(X)
            else if (RS4(x,y,rkMax[y],rkMax[x]) && continueSat)
            {
                rkMax[y] = rkMax[x];
                
            }
            // fin (RS4)

            // (RS5) si rkMax(X) + rkMax(Y) - rkMin(x & y) < rkMax(x | y) alors rkMax(x | y) prend la valeur de rkMax(X) + rkMax(Y) - rkMin(x & y)
            // (RS5) si rkMax(X) + rkMax(Y) − rkMin(X ∩ Y) < rkMax(X ∪ Y) alors rkMax(X ∪ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∩ Y)
            else if (RS5(rkMax[x],rkMax[y],rkMin[unionEnsembles(x,y)],rkMax[intersectionEnsembles(x,y)]) && continueSat)
            {
                rkMax[intersectionEnsembles(x,y)] = rkMax[x] + rkMax[y] - rkMin[unionEnsembles(x,y)];
                
            }
            // fin (RS5)

            // (RS6) si rkMax(X) + rkMax(Y) - rkMin(x | y) < rkMax(x & y) alors rkMax(x & y) prend la valeur de rkMax(X) + rkMax(Y) - rkMin(x | y)
            // (RS6) si rkMax(X) + rkMax(Y) − rkMin(X ∪ Y) < rkMax(X ∩ Y) alors rkMax(X ∩ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∪ Y)
            else if (RS6(rkMax[x],rkMax[y],rkMin[intersectionEnsembles(x,y)],rkMax[unionEnsembles(x,y)]) && continueSat)
            {
                rkMax[unionEnsembles(x,y)] = rkMax[x] + rkMax[y] - rkMin[intersectionEnsembles(x,y)];
                
            }
            // fin (RS6)

            // (RS7) si rkMin(x & y) + rkMin(x | y) - rkMax(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(x & y) + rkMin(x | y) - rkMax(Y)
            // (RS7) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y)
            else if (RS7(rkMin[unionEnsembles(x,y)],rkMin[intersectionEnsembles(x,y)],rkMax[y],rkMin[x]) && continueSat)
            {
                rkMin[x] = rkMin[unionEnsembles(x,y)] + rkMin[intersectionEnsembles(x,y)] - rkMax[y];
                

            }
            // fin (RS7)

            // (RS8) si rkMin(x & y) + rkMin(x | y) - rkMax(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(x & y) + rkMin(x | y) - rkMax(X)
            // (RS8) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X)
            else if (RS8(rkMin[unionEnsembles(x,y)],rkMin[intersectionEnsembles(x,y)],rkMax[x],rkMin[y]) && continueSat)
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
