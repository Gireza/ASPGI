#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Générateur de tableaux rkMin[] et rkMax[] par défaut

int main()
{
    unsigned char rkMin[32] = {0}; // phase de toutes les initialisations
    unsigned char rkMax[32] = {0};

    int i = 1; 
    int j = 1;

    printf("{%d", rkMin[0]);
    while (i<32)
    {
        rkMin[i]=1;
        printf(", %d", rkMin[i]);
        i++;
    }

    printf("}\n");

    printf("{%d", rkMax[0]);
    while (j < 32)
    {
        int nbBits = (int)log2((double)j) + 1;
        int nbUns = 0;
        int nb = j;
        for (int bit = 1; bit <= nbBits; bit++) {
            if (nb%2 == 1) nbUns += 1;
            nb = nb >> 1;
        }
        if (nbUns <= 4) rkMax[j] = nbUns;
        else {
            rkMax[j] = 4;
        }    
        printf(", %d", rkMax[j]);
        j++;
    }
    printf("}\n");

    // tableaux rkMin[] et rkMax[] générés
    /* unsigned char rkMin[32] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    unsigned char rkMax[32] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 4}; */
}
