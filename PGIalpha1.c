#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// POUR RAPPEL
// Données : E = {A, B, C}
// Hypothèse : AB 2/2
// Résultat attendu : ABC 3/2

int main()
{
    // tableau minimal de noms de noeuds (on pourra aller jusqu'à 31 lettres différentes, là il y en a 5...)
    char *nomNoeud[] = {"Ø", "A", "B", "AB", "C", "AC", "BC", "ABC", "D", "AD", "BD", "ABD", "CD", "ACD", "BCD", "ABCD", "E", "AE", "BE", "ABE", "CE", "ACE", "BCE", "ABCE", "DE", "ADE", "BDE", "ABDE", "CDE", "ACDE", "BCDE", "ABCDE"};

    // tableaux rkMin[] et rkMax[] par défaut générés avec rankTabGen.c
    unsigned char rkMin[32] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    unsigned char rkMax[32] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 4};

    // E = {A, B, C}
    int cardinalE = 3;
    int nbNoeuds = (int)pow(2, (double)cardinalE) - 1;

    // pour (RS0) on se contente pour l'instant de...
    int idAB = 3;
    int rkAB = 2;
    rkMax[idAB] = rkAB;
    rkMin[idAB] = rkAB;

    int numTest = 0;

    // application de RS1
    int x = 1;
    while (x <= nbNoeuds)
    {   
        
        int y = 1;
        while (y <= nbNoeuds)
        {
            // (RS1) si X ⊆ Y et rkMin(X) > rkMin(Y ) alors rkMin(Y ) ← rkMin(X)
            numTest++;
            if ((x & y) == x && rkMin[x] > rkMin[y])
            {
                rkMin[y] = rkMin[x];
                printf("Test %d : RS1 de %s sur %s  →  rkMin(%s) = %d  →  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[y], rkMin[y], nomNoeud[y], rkMax[y], rkMin[y]);
            }
            // fin (RS1)
            y++;
        }
        x++;
    }
    printf("Nombre total de tests effectués : %d\n", numTest);
}
