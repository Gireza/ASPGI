#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "utile.c"
int y;
int x;
bool continueSat;

// POUR RAPPEL
// (* Exemple de lemme à 4 points p. 114 *)
// Données : E = {A, B, C, D}
// Hypothèses :
// ABD 3/3
// ACD 2/2
// AC 2/2
// CD 2/2
// Résultat attendu : ABC 3/3

void reinitialise(){
    continueSat = false;
    y = 0;
    x = 0;
}


int main(int argc, char * argv[])
{

    FILE *fichier = NULL;
    FILE *resultFile = NULL;
    // argv[1] prend la valeur du premier paramètrer
    fichier = fopen(argv[1], "r+"); // r+ pour lire et écrire !
    resultFile = fopen("resultats.txt","r+");
    resultFile = fopen("resultats.txt","wb");

    // tableau minimal de noms de noeuds (on pourra aller jusqu'à 31 lettres différentes, là il y en a 5...)
    char *nomNoeud[] = {"Ø", "A", "B", "AB", "C", "AC", "BC", "ABC", "D", "AD", "BD", "ABD", "CD", "ACD", "BCD", "ABCD", "E", "AE", "BE", "ABE", "CE", "ACE", "BCE", "ABCE", "DE", "ADE", "BDE", "ABDE", "CDE", "ACDE", "BCDE", "ABCDE"};

    // tableaux rkMin[] et rkMax[] par défaut générés avec rankTabGen.c
    /* unsigned char rkMin[32] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
       unsigned char rkMax[32] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 4}; */

    // E = {A, B, C, D}
    int cardinalE = 4;
    int nbNoeuds = (int)pow(2, (double)cardinalE) - 1;

    // pour (RS0), en attendant le parseur, on se contente pour l'instant de...
    unsigned char rkMin[32] = {0, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 3, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    unsigned char rkMax[32] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 2, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 4};


    int numTest = 0;

    // on s'assure d'être à la fin de l'énoncé dans le fichier.txt
    fseek(fichier, 0, SEEK_END);
    fprintf(resultFile, "\nListe des règles RS1 à RS8 appliquées avec succès :\n\n");
    printf("\nListe des règles RS1 à RS8 appliquées avec succès :\n\n");

    // APPLICATION DES REGLES RS1 à RS8
    continueSat = true;
    x = 1;
    

    while (x <= nbNoeuds)
    {
        y = 1;
        while (y <= nbNoeuds)
        {
            // (RS1) si X ⊆ Y et rkMin(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMax rkMin(X)
            numTest++;
            if (unionPratique(x,y) == x && rkMin[x] > rkMin[y] && continueSat )
            {
                rkMin[y] = rkMin[x];
                printf("Test %d : RS1 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[y], rkMin[y], nomNoeud[y], rkMax[y], rkMin[y]);
                fprintf(resultFile, "Test %d : RS1 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[y], rkMin[y], nomNoeud[y], rkMax[y], rkMin[y]);
                reinitialise();
            }
            // fin (RS1)

            // (RS3) si  X ⊆ Y et rkMax(Y) < rKMax(X) alors rkMax(X) prend la valeur de rkMax(Y)
            numTest++;
            if ((unionPratique(x,y)) == x && rkMax[y] < rkMax[x] && continueSat)
            {
                rkMax[x] = rkMax[y];
                printf("Test %d : RS3 de %s sur %s  ->  rkMax(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x], rkMax[x], nomNoeud[x], rkMax[x], rkMin[x]);
                fprintf(resultFile, "Test %d : RS3 de %s sur %s  ->  rkMax(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x], rkMax[x], nomNoeud[x], rkMax[x], rkMin[x]);
                reinitialise();
            }
            // fin (RS3)

            // (RS2) si Y ⊆ X et rkMin(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(Y)
            numTest++;
            if ((unionPratique(x,y)) == y && rkMin[y] > rkMin[x] && continueSat)
            {
                rkMin[x] = rkMin[y];
                printf("Test %d : RS2 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x], rkMin[x], nomNoeud[x], rkMax[x], rkMin[x]);
                fprintf(resultFile, "Test %d : RS2 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x], rkMin[x], nomNoeud[x], rkMax[x], rkMin[x]);
                reinitialise();

            }
            // fin (RS2)

            // (RS4) si Y ⊆ X et rkMax(Y) > rkMax(X) alors rkMax(Y) prend la valeur de rkMax(X)
            numTest++;
            if ((unionPratique(x,y)) == y && rkMax[y] > rkMax[x] && continueSat)
            {
                rkMax[y] = rkMax[x];
                printf("Test %d : RS4 de %s sur %s  ->  rkMax(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[y], rkMax[y], nomNoeud[y], rkMax[y], rkMin[y]);
                fprintf(resultFile, "Test %d : RS4 de %s sur %s  ->  rkMax(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[y], rkMax[y], nomNoeud[y], rkMax[y], rkMin[y]);
                reinitialise();
            }
            // fin (RS4)

            // (RS5) si rkMax(X) + rkMax(Y) - rkMin(x & y) < rkMax(x | y) alors rkMax(x | y) prend la valeur de rkMax(X) + rkMax(Y) - rkMin(x & y)
            // (RS5) si rkMax(X) + rkMax(Y) − rkMin(X ∩ Y) < rkMax(X ∪ Y) alors rkMax(X ∪ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∩ Y)
            numTest++;
            if (rkMax[x] + rkMax[y] - rkMin[unionPratique(x,y)] < rkMax[interPratique(x,y)] && continueSat)
            {
                rkMax[interPratique(x,y)] = rkMax[x] + rkMax[y] - rkMin[unionPratique(x,y)];
                printf("Test %d : RS5 de %s sur %s  ->  rkMax(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[interPratique(x,y)], rkMax[interPratique(x,y)], nomNoeud[interPratique(x,y)], rkMax[x |y], rkMin[interPratique(x,y)]);
                fprintf(resultFile, "Test %d : RS5 de %s sur %s  ->  rkMax(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[interPratique(x,y)], rkMax[interPratique(x,y)], nomNoeud[interPratique(x,y)], rkMax[x |y], rkMin[interPratique(x,y)]);
                reinitialise();
            }
            // fin (RS5)

            // (RS6) si rkMax(X) + rkMax(Y) - rkMin(x | y) < rkMax(x & y) alors rkMax(x & y) prend la valeur de rkMax(X) + rkMax(Y) - rkMin(x | y)
            // (RS6) si rkMax(X) + rkMax(Y) − rkMin(X ∪ Y) < rkMax(X ∩ Y) alors rkMax(X ∩ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∪ Y)
            numTest++;
            if (rkMax[x] + rkMax[y] - rkMin[interPratique(x,y)] < rkMax[unionPratique(x,y)] && continueSat)
            {
                rkMax[unionPratique(x,y)] = rkMax[x] + rkMax[y] - rkMin[interPratique(x,y)];
                printf("Test %d : RS6 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[unionPratique(x,y)], rkMax[unionPratique(x,y)], nomNoeud[unionPratique(x,y)], rkMax[unionPratique(x,y)], rkMin[unionPratique(x,y)]);
                fprintf(resultFile, "Test %d : RS6 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[unionPratique(x,y)], rkMax[unionPratique(x,y)], nomNoeud[unionPratique(x,y)], rkMax[unionPratique(x,y)], rkMin[unionPratique(x,y)]);
                reinitialise();
            }
            // fin (RS6)

            // (RS7) si rkMin(x & y) + rkMin(x | y) - rkMax(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(x & y) + rkMin(x | y) - rkMax(Y)
            // (RS7) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y)
            numTest++;
            if (rkMin[unionPratique(x,y)] + rkMin[interPratique(x,y)] - rkMax[y] > rkMin[x] && continueSat)
            {
                rkMin[x] = rkMin[unionPratique(x,y)] + rkMin[interPratique(x,y)] - rkMax[y];
                printf("Test %d : RS7 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x], rkMin[x], nomNoeud[x], rkMax[x], rkMin[x]);
                fprintf(resultFile, "Test %d : RS7 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x], rkMin[x], nomNoeud[x], rkMax[x], rkMin[x]);
                reinitialise();

            }
            // fin (RS7)

            // (RS8) si rkMin(x & y) + rkMin(x | y) - rkMax(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(x & y) + rkMin(x | y) - rkMax(X)
            // (RS8) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X)
            numTest++;
            if (rkMin[unionPratique(x,y)] + rkMin[interPratique(x,y)] - rkMax[x] > rkMin[y] && continueSat)
            {
                rkMin[y] = rkMin[unionPratique(x,y)] + rkMin[interPratique(x,y)] - rkMax[x];
                          printf("Test %d : RS8 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[y], rkMin[y], nomNoeud[y], rkMax[y], rkMin[y]);
                fprintf(resultFile, "Test %d : RS8 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[y], rkMin[y], nomNoeud[y], rkMax[y], rkMin[y]);
                reinitialise();
            }
            printf("%d - ",x);
            printf("%d\n",y);
            
            // fin (RS8)
            /*printf("y =%d",y);
            printf("x=%d",x);*/
            y++;
        }
        continueSat = true;
        x++;
    }
    printf("\nNombre total de tests effectués : %d\n", numTest);
    fprintf(resultFile, "\nNombre total de tests effectués : %d\n", numTest);
}





// mettre dans une variable le printf et le mettre dans le fichier 
