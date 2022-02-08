#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// NOTA BENE : FORMATAGE ATTENDU POUR LE FICHIER.TXT DE L'ENONCE
/* 
(* Exemple de lemme à 4 points p. 114 *)    // ligne descriptive
A, B, C, D                                  // éléments de l'ensemble considéré
ABD 3/3                                     // hypothèses au format X rkMax/rkMin
ACD 2/2
AC 2/2
CD 2/2
*ABC 3/3                                    // résultat attendu précédé d'une astérique
*/

#define TAILLE_MAX 100
//#define xstr(s) str(s) // https://xrenault.developpez.com/tutoriels/c/scanf/#Lno-5-3
//#define str(s) #s

int main()
{
    FILE *fichier = NULL;
    fichier = fopen("fichier.txt", "r+"); // r+ pour lire et écrire !

    // idée : passer plutôt le fichier en paramètre de l'app... est-ce possible ???

    char *ligneFichier[32] = {"Ø"}; // tableau pour stocker chaque ligne de l'énoncé écrite sur le fichier (taille arbitraire de 32 lignes, parce que pourquoi pas ?)

    // tableau minimal de 32 noms de noeuds (formés avec seulement 5 éléments différents, on pourra aller jusqu'à 32 ?...)
    char *nomNoeud[] = {"Ø", "A", "B", "AB", "C", "AC", "BC", "ABC", "D", "AD", "BD", "ABD", "CD", "ACD", "BCD", "ABCD", "E", "AE", "BE", "ABE", "CE", "ACE", "BCE", "ABCE", "DE", "ADE", "BDE", "ABDE", "CDE", "ACDE", "BCDE", "ABCDE"};
    // {"Ø", "P", "Q", "PQ", "R", "PR", "QR", "PQR", "S", "PS", "QS", "PQS", "RS", "PRS", "QRS", "PQRS", "T", "PT", "QT", "PQT", "RT", "PRT", "QRT", "PQRT", "ST", "PST", "QST", "PQST", "RST", "PRST", "QRST", "PQRST"};

    // tableaux rkMin[] et rkMax[] par défaut générés avec rankTabGen.c
    unsigned char rkMin[32] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    unsigned char rkMax[32] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 4};

    if (fichier != NULL) // On peut lire et écrire dans le fichier
    {
        // DEBUT PARTIE PARSEUR

        // PARSAGE DU FICHIER PAR LIGNES -> *ligneFichier[]

        char buffer[TAILLE_MAX + 1] = "0";
        int idLigne = 0;

        while (fgets(buffer, TAILLE_MAX, fichier) != NULL)
        {
            printf("%s", buffer);
            ligneFichier[idLigne] = malloc(strlen(buffer) + 1);
            strcpy(ligneFichier[idLigne], buffer);
            idLigne++;
        }
        printf("\n");

        // PARSAGE DE LA DEUXIEME LIGNE DU FICHIER AVEC strtok (on rempli nomNoeud[] à partir de ligneFichier[1])
        // (par convention, la première ligne ligneFichier[0] contient une courte description du cas étudié)

        // Définitions de séparateurs possibles.
        const char *separators = " ,.-!\n";

        char *strToken = strtok(ligneFichier[1], separators);

        // chaque point de E est à enregistrer à un index == à une puissande de 2;
        int pow2idNoeud = 0;
        // index où sera inscrit le nom du noeud dans le tableau
        int idTabNoeud = 0;
        // cardinal de l'ensemble de points de l'énoncé
        int cardinalE = 0;

        // pour calculer la taille mémoire nécessaire à chaque nom de sous-ensemble
        size_t noeudSize;

        while (strToken != NULL)
        {
            // REMPLISSAGE *nomNoeud[] avec chaque point de E définit dans l'énoncé (deuxième ligne du fichier.txt)

            // chaque point de E est à enregistrer à un index == à une puissande de 2;
            idTabNoeud = (int)pow(2, (double)pow2idNoeud);
            // on ajoute 1 à la taille mémoire allouée (malloc) à la case du tableau pour le caractère terminal \0
            nomNoeud[idTabNoeud] = malloc(strlen(strToken) + 1);
            // copie de la valeur parsée dans la case voulue
            strcpy(nomNoeud[idTabNoeud], strToken);
            // incrémentation du cardinal pour chaque élément (point) trouvé
            cardinalE++;
            // pour passer à la case "suivante"
            pow2idNoeud++;
            // token suivant
            strToken = strtok(NULL, separators);

            // dans la foulée... DEFINITON ET ENREGISTREMENT DES SOUS ENSEMBLES

            // à partir du deuxième point (id == 2)
            if (idTabNoeud > 1)
            {
                for (int i = 1; i < idTabNoeud; i++)
                {
                    noeudSize = strlen(nomNoeud[i]) + strlen(nomNoeud[idTabNoeud]) + 1;
                    nomNoeud[idTabNoeud + i] = malloc(noeudSize);
                    strcpy(nomNoeud[idTabNoeud + i], nomNoeud[i]);
                    strcat(nomNoeud[idTabNoeud + i], nomNoeud[idTabNoeud]);
                }
            }
        }
        // affichage des sous ensembles (+ écriture éventuelle dans le fichier)
        // on s'assure d'être à la fin de l'énoncé dans le fichier
        // fseek(fichier, 0, SEEK_END);

        printf("Cardinal de E : %d\n", cardinalE);
        printf("\n");
        int nbNoeuds = (int)pow(2, (double)cardinalE) - 1;
        for (int i = 0; i <= nbNoeuds; i++)
        {
            printf("%s\n", nomNoeud[i]);
            //fprintf(fichier, "\n%s", nomNoeud[i]);
        }

        printf("\n");

        // LIGNEES SUIVANTES : CONTRAINTES SUR LES SOUS-ENSEMBLES
        int rkM = 0;
        int rkm = 0;
        char noeud[32] = {0}; // l'espace doit être assez grand pour recevoir la chaine retournée !!!

        for (int i = 2; i < idLigne; i++)
        {
            (void)sscanf(ligneFichier[i], "%s %d/%d", noeud, &rkM, &rkm);
            //printf("%s %d/%d\n", noeud, rkM, rkm);
            // printf("\n");
            for (int j = 0; j < 32; j++)
            {
                // à faire plutôt : parcour partiel avec while !!!...
                if (strcmp(nomNoeud[j], noeud) == 0)
                {
                    rkMax[j] = rkM;
                    rkMin[j] = rkm;
                    printf("Modif noeud %d : %s %d/%d\n", j, nomNoeud[j], rkMax[j], rkMin[j]);
                }
            }
            printf("\n");
        }

        // affichage des rangs mis à jour...
        for (int i = 0; i < 32; i++)
        {
            printf("%d, ", rkMax[i]);
        }
        printf("\n");
        for (int i = 0; i < 32; i++)
        {
            printf("%d, ", rkMin[i]);
        }
        printf("\n");

        // FIN PARTIE PARSEUR
        // DEBUT PARTIE SATURATION

        int numTest = 0;

        // on s'assure d'être à la fin de l'énoncé dans le fichier.txt
        fseek(fichier, 0, SEEK_END);
        fprintf(fichier, "\nListe des règles RS1 à RS8 appliquées avec succès :\n\n");
        printf("\nListe des règles RS1 à RS8 appliquées avec succès :\n\n");

        // APPLICATION DES REGLES RS1 à RS8
        int x = 1;
        while (x <= nbNoeuds)
        {

            int y = 1;
            while (y <= nbNoeuds)
            {
                // (RS1) si X ⊆ Y et rkMin(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMax rkMin(X)
                numTest++;
                if ((x & y) == x && rkMin[x] > rkMin[y])
                {
                    rkMin[y] = rkMin[x];
                    printf("Test %d : RS1 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[y], rkMin[y], nomNoeud[y], rkMax[y], rkMin[y]);
                    fprintf(fichier, "Test %d : RS1 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[y], rkMin[y], nomNoeud[y], rkMax[y], rkMin[y]);
                }
                // fin (RS1)

                // (RS3) si  X ⊆ Y et rkMax(Y) < rKMax(X) alors rkMax(X) prend la valeur de rkMax(Y)
                numTest++;
                if ((x & y) == x && rkMax[y] < rkMax[x])
                {
                    rkMax[x] = rkMax[y];
                    printf("Test %d : RS3 de %s sur %s  ->  rkMax(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x], rkMax[x], nomNoeud[x], rkMax[x], rkMin[x]);
                    fprintf(fichier, "Test %d : RS3 de %s sur %s  ->  rkMax(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x], rkMax[x], nomNoeud[x], rkMax[x], rkMin[x]);
                }
                // fin (RS3)

                // (RS2) si Y ⊆ X et rkMin(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(Y)
                numTest++;
                if ((x & y) == y && rkMin[y] > rkMin[x])
                {
                    rkMin[x] = rkMin[y];
                    printf("Test %d : RS2 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x], rkMin[x], nomNoeud[x], rkMax[x], rkMin[x]);
                    fprintf(fichier, "Test %d : RS2 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x], rkMin[x], nomNoeud[x], rkMax[x], rkMin[x]);
                }
                // fin (RS2)

                // (RS4) si Y ⊆ X et rkMax(Y) > rkMax(X) alors rkMax(Y) prend la valeur de rkMax(X)
                numTest++;
                if ((x & y) == y && rkMax[y] > rkMax[x])
                {
                    rkMax[y] = rkMax[x];
                    printf("Test %d : RS4 de %s sur %s  ->  rkMax(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[y], rkMax[y], nomNoeud[y], rkMax[y], rkMin[y]);
                    fprintf(fichier, "Test %d : RS4 de %s sur %s  ->  rkMax(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[y], rkMax[y], nomNoeud[y], rkMax[y], rkMin[y]);
                }
                // fin (RS4)

                // (RS5) si rkMax(X) + rkMax(Y) - rkMin(X & Y) < rkMax(X | Y) alors rkMax(X | Y) prend la valeur de rkMax(X) + rkMax(Y) - rkMin(X & Y)
                // (RS5) si rkMax(X) + rkMax(Y) − rkMin(X ∩ Y) < rkMax(X ∪ Y) alors rkMax(X ∪ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∩ Y)
                numTest++;
                if (rkMax[x] + rkMax[y] - rkMin[x & y] < rkMax[x | y])
                {
                    rkMax[x | y] = rkMax[x] + rkMax[y] - rkMin[x & y];
                    printf("Test %d : RS5 de %s sur %s  ->  rkMax(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x | y], rkMax[x | y], nomNoeud[x | y], rkMax[x | y], rkMin[x | y]);
                    fprintf(fichier, "Test %d : RS5 de %s sur %s  ->  rkMax(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x | y], rkMax[x | y], nomNoeud[x | y], rkMax[x | y], rkMin[x | y]);
                }
                // fin (RS5)

                // (RS6) si rkMax(X) + rkMax(Y) - rkMin(X | Y) < rkMax(X & Y) alors rkMax(X & Y) prend la valeur de rkMax(X) + rkMax(Y) - rkMin(X | Y)
                // (RS6) si rkMax(X) + rkMax(Y) − rkMin(X ∪ Y) < rkMax(X ∩ Y) alors rkMax(X ∩ Y) prend la valeur de rkMax(X) + rkMax(Y) − rkMin(X ∪ Y)
                numTest++;
                if (rkMax[x] + rkMax[y] - rkMin[x | y] < rkMax[x & y])
                {
                    rkMax[x & y] = rkMax[x] + rkMax[y] - rkMin[x | y];
                    printf("Test %d : RS6 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x & y], rkMax[x & y], nomNoeud[x & y], rkMax[x & y], rkMin[x & y]);
                    fprintf(fichier, "Test %d : RS6 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x & y], rkMax[x & y], nomNoeud[x & y], rkMax[x & y], rkMin[x & y]);
                }
                // fin (RS6)

                // (RS7) si rkMin(X & Y) + rkMin(X | Y) - rkMax(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(X & Y) + rkMin(X | Y) - rkMax(Y)
                // (RS7) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y) > rkMin(X) alors rkMin(X) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(Y)
                numTest++;
                if (rkMin[x & y] + rkMin[x | y] - rkMax[y] > rkMin[x])
                {
                    rkMin[x] = rkMin[x & y] + rkMin[x | y] - rkMax[y] > rkMin[x];
                    printf("Test %d : RS7 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x], rkMin[x], nomNoeud[x], rkMax[x], rkMin[x]);
                    fprintf(fichier, "Test %d : RS7 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[x], rkMin[x], nomNoeud[x], rkMax[x], rkMin[x]);
                }
                // fin (RS7)

                // (RS8) si rkMin(X & Y) + rkMin(X | Y) - rkMax(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(X & Y) + rkMin(X | Y) - rkMax(X)
                // (RS8) si rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X) > rkMin(Y) alors rkMin(Y) prend la valeur de rkMin(X ∩ Y) + rkMin(X ∪ Y) − rkMax(X)
                numTest++;
                if (rkMin[x & y] + rkMin[x | y] - rkMax[x] > rkMin[y])
                {
                    rkMin[y] = rkMin[x & y] + rkMin[x | y] - rkMax[x];
                    printf("Test %d : RS8 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[y], rkMin[y], nomNoeud[y], rkMax[y], rkMin[y]);
                    fprintf(fichier, "Test %d : RS8 de %s sur %s  ->  rkMin(%s) = %d  ->  %s %d/%d\n", numTest, nomNoeud[x], nomNoeud[y], nomNoeud[y], rkMin[y], nomNoeud[y], rkMax[y], rkMin[y]);
                }
                // fin (RS8)
                y++;
            }
            x++;
        }
        printf("\nNombre total de tests effectués : %d\n", numTest);
        fprintf(fichier, "\nNombre total de tests effectués : %d\n", numTest);

        fclose(fichier);
    }
    else
        printf("Impossible d'ouvrir le fichier fichier.txt");

    return 0;
}
