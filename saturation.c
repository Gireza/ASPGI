#include "saturation.h"

#include <stdio.h>

void saturer(unsigned int* rkMin, unsigned int* rkMax, unsigned int n_points) {

    void reinitialise(){
        continueSat = false;
        y = 0;
        x = 0;
    }

    bool RS1(int x, int y, int rkMinx, int rkMiny){
        if (appartienPratique(x,y) && rkMinx > rkMiny){
            return true;
        }
    }
    bool RS2(int x, int y, int rkMiny, int rkMinx){
        if (appartienPratique(y,x) && rkMiny > rkMinx){
            return true;
        }
    }
    bool RS3(int x, int y, int rkMaxy, int rkMaxx){
        if (appartienPratique(x,y) && rkMaxy < rkMaxx) {
            return true;
        }
    }
    bool RS4(int x, int y, int rkMaxy, int rkMaxx){
        if (appartienPratique(y,x) && rkMaxy > rkMaxx){
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
    
    int nbNoeuds = (int)pow(2, (double)n_points) - 1;

    continueSat = true;
    x = 1;

    while (x <= nbNoeuds)
    {
        y = 1;
        while (y <= nbNoeuds)
        {
            // (RS1) si X ⊆ Y et rkMin(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMax rkMin(X)
            if (RS1(x,y,rkMin[x],rkMin[y]) && continueSat)
            {
                rkMin[y] = rkMin[x];
                reinitialise();
            }
            // fin (RS1)

            // (RS3) si  X ⊆ Y et rkMax(Y) < rKMax(X) alors rkMax(X) prend la valeur de rkMax(Y)
            if (RS3(x,y,rkMax[y],rkMax[x]) && continueSat)
            {
                rkMax[x] = rkMax[y];
                reinitialise();
            }
            // fin (RS3)

            // (RS2) si Y ⊆ X et rkMin(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(Y)
            if (RS2(x,y,rkMin[y],rkMin[x]) && continueSat)
            {
                rkMin[x] = rkMin[y];
                reinitialise();

            }
            // fin (RS2)

            // (RS4) si Y ⊆ X et rkMax(Y) > rkMax(X) alors rkMax(Y) prend la valeur de rkMax(X)
            if (RS4(x,y,rkMax[y],rkMax[x]) && continueSat)
            {
                rkMax[y] = rkMax[x];
                reinitialise();
            }
            // fin (RS4)

            // (RS5) si rkMax(X) + rkMax(Y) - rkMin(x & y) < rkMax(x | y) alors rkMax(x | y) prend la valeur de rkMax(X) + rkMax(Y) - rkMin(x & y)
            // (RS5) si rkMax(X) + rkMax(Y) − rkMin(X ∩ Y) < rkMax(X ∪ Y) alors rkMax(X ∪ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∩ Y)
            if (RS5(rkMax[x],rkMax[y],rkMin[unionPratique(x,y)],rkMax[interPratique(x,y)]) && continueSat)
            {
                rkMax[interPratique(x,y)] = rkMax[x] + rkMax[y] - rkMin[unionPratique(x,y)];
                reinitialise();
            }
            // fin (RS5)

            // (RS6) si rkMax(X) + rkMax(Y) - rkMin(x | y) < rkMax(x & y) alors rkMax(x & y) prend la valeur de rkMax(X) + rkMax(Y) - rkMin(x | y)
            // (RS6) si rkMax(X) + rkMax(Y) − rkMin(X ∪ Y) < rkMax(X ∩ Y) alors rkMax(X ∩ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∪ Y)
            if (RS6(rkMax[x],rkMax[y],rkMin[interPratique(x,y)],rkMax[unionPratique(x,y)]) && continueSat)
            {
                rkMax[unionPratique(x,y)] = rkMax[x] + rkMax[y] - rkMin[interPratique(x,y)];
                reinitialise();
            }
            // fin (RS6)

            // (RS7) si rkMin(x & y) + rkMin(x | y) - rkMax(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(x & y) + rkMin(x | y) - rkMax(Y)
            // (RS7) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y)
            if (RS7(rkMin[unionPratique(x,y)],rkMin[interPratique(x,y)],rkMax[y],rkMin[x]) && continueSat)
            {
                rkMin[x] = rkMin[unionPratique(x,y)] + rkMin[interPratique(x,y)] - rkMax[y];
                reinitialise();

            }
            // fin (RS7)

            // (RS8) si rkMin(x & y) + rkMin(x | y) - rkMax(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(x & y) + rkMin(x | y) - rkMax(X)
            // (RS8) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X)
            if (RS8(rkMin[unionPratique(x,y)],rkMin[interPratique(x,y)],rkMax[x],rkMin[y]) && continueSat)
            {
                rkMin[y] = rkMin[unionPratique(x,y)] + rkMin[interPratique(x,y)] - rkMax[x];
                reinitialise();
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
