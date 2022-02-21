#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "utile.c"

#define TAILLE_MAX 100
//#define xstr(s) str(s) // https://xrenault.developpez.com/tutoriels/c/scanf/#Lno-5-3
//#define str(s) #s

int main()
{
    FILE *fichier = NULL;
    fichier = fopen("fichier.txt", "r+"); // r+ pour lire et écrire !

    // idée : passer plutôt le fichier en paramètre de l'app... est-ce possible ???

    char *ligneFichier[32] = {"Ø"}; // tableau pour stocker chaque ligne de l'énoncé écrite sur le fichier (taille arbitraire de 32 lignes, parce que pourquoi pas ?)

    // tableau minimal de 32 noms de noeuds (formés avec seulement 5 éléments différents, on pourra aller jusqu'à 32...)
    char *nomNoeud[] = {"Ø", "A", "B", "AB", "C", "AC", "BC", "ABC", "D", "AD", "BD", "ABD", "CD", "ACD", "BCD", "ABCD", "E", "AE", "BE", "ABE", "CE", "ACE", "BCE", "ABCE", "DE", "ADE", "BDE", "ABDE", "CDE", "ACDE", "BCDE", "ABCDE"};
    // {"Ø", "P", "Q", "PQ", "R", "PR", "QR", "PQR", "S", "PS", "QS", "PQS", "RS", "PRS", "QRS", "PQRS", "T", "PT", "QT", "PQT", "RT", "PRT", "QRT", "PQRT", "ST", "PST", "QST", "PQST", "RST", "PRST", "QRST", "PQRST"};

    // tableaux rkMin[] et rkMax[] par défaut générés avec rankTabGen.c
    unsigned char rkMin[32] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    unsigned char rkMax[32] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 4};

    if (fichier != NULL) // On peut lire et écrire dans le fichier
    {
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
            idTabNoeud = puissance(pow2idNoeud);
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
        for (int i = 0; i < 32; i++)
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
            printf("%s %d/%d\n", noeud, rkM, rkm);
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

        fclose(fichier);
    }
    else
        printf("Impossible d'ouvrir le fichier fichier.txt");

    return 0;
}

// fscanf fgets fgetc
// fscanf(fichier, "%64[^\n]", buffer);
// fprintf fputs fputc
/* fseek(fichier, 0, SEEK_END);
int fin = ftell(fichier);
fseek(fichier, 0, SEEK_SET);*/
// printf("%ld\n", ftell(fichier));
