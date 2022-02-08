#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Générateur de tableaux rkMin[] et rkMax[] par défaut
// (pour l'exemple on se contente de 31 noeuds + l'ensemble vide, donc de 2 tableaux de 32 valeurs suffisant pour un ensemble E de 5 points maximum)

int main()
{
    unsigned char rkMin[32] = {0};
    unsigned char rkMax[32] = {0};
    // remarque : rkMin[0] et rkMax[0] resterons initialisés à 0

    int i = 1;
    int j = 1;

    // initialisation du tableau rkMin à {0, 1, 1... 1}
    printf("{%d", rkMin[0]);
    while (i<32)
    {
        rkMin[i]=1;
        printf(", %d", rkMin[i]);
        i++;
    }
    printf("}\n");

    // initialisation du tableau rkMax à {0, 1, 1, 2, 1, 2, 2, 3... 4}
    printf("{%d", rkMax[0]);
    // parcour des 31 noeuds
    while (j < 32)
    {
        // calcul du nombre de bits (la "largeur") nécéssaire à l'écriture binaire de chaque noeud (ayant pour valeur décimale j).
        int nbBits = (int)log2((double)j) + 1;
        // on cherche ensuite à savoir le nombre de bits de valeur "1" présents dans le mot binaire : cela correspond au nombre d'éléments du noeud (sous-ensemble de points) considéré et permet de calculer son rkMax
        int nbUns = 0;
        // variable nb correspondant à la valeur décimale du noeud
        int nb = j;
        // parcour des bits de nbBits
        for (int bit = 1; bit <= nbBits; bit++) {
            // si le premier bit est égale à 1, on incrémente nbUns
            if (nb%2 == 1) nbUns += 1;
            // on change le bit considéré par décalage à droite bit à bit (opérateur bitwise)
            nb = nb >> 1;
        }
        // on applique la règle rkMax[j] = min{nbUns, 4}
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
