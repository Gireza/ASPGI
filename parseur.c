#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define TAILLE_MAX 100
//#define xstr(s) str(s) // https://xrenault.developpez.com/tutoriels/c/scanf/#Lno-5-3
//#define str(s) #s

int main()
{
    FILE *fichier = NULL;
    fichier = fopen("fichier.txt", "r+"); // r+ pour lire et écrire !

    if (fichier == NULL) // On ne trouve pas le fichier...
    {
        printf("Impossible de trouver le fichier \"fichier.txt\"\n");
        return 0;
        // TODO : gestion des erreurs...
    }

    // IDEE : passer plutôt le fichier en paramètre de l'app... est-ce possible ???

    // tableau pour stocker chaque ligne de l'énoncé écrite sur le fichier (taille arbitraire de 32 lignes, parce que pourquoi pas ?)
    char *ligneFichier[32] = {"Ø"};

    // tableau minimal de 32 noms de noeuds (formés avec seulement 5 éléments différents, on prévoit d'aller jusqu'à 32...)
    char *nomNoeud[] = {"Ø", "A", "B", "AB", "C", "AC", "BC", "ABC", "D", "AD", "BD", "ABD", "CD", "ACD", "BCD", "ABCD", "E", "AE", "BE", "ABE", "CE", "ACE", "BCE", "ABCE", "DE", "ADE", "BDE", "ABDE", "CDE", "ACDE", "BCDE", "ABCDE"};
    // {"Ø", "P", "Q", "PQ", "R", "PR", "QR", "PQR", "S", "PS", "QS", "PQS", "RS", "PRS", "QRS", "PQRS", "T", "PT", "QT", "PQT", "RT", "PRT", "QRT", "PQRT", "ST", "PST", "QST", "PQST", "RST", "PRST", "QRST", "PQRST"};

    // tableaux rkMax[] et rkMin[] par défaut générés avec rankTabGen.c
    unsigned char rkMax[32] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 4};
    unsigned char rkMin[32] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    // variables nécessaires à la mise à jour des rangs dans le tableau en fonction des contraintes (hypothèses) de l'énoncé
    int rkM = 0;
    int rkm = 0;
    char noeud[32] = {0}; // l'espace doit être assez grand pour recevoir la chaine retournée !!!

    // PARSAGE DU FICHIER PAR LIGNES -> *ligneFichier[]

    char buffer[TAILLE_MAX + 1] = "0";
    int idLigne = 0;

    printf("\nRappel de l'énoncé :\n\n");

    while (fgets(buffer, TAILLE_MAX, fichier) != NULL)
    {
        printf("%s", buffer); // affichage de la ligne d'énoncé parsée
        ligneFichier[idLigne] = malloc(strlen(buffer) + 1);
        strcpy(ligneFichier[idLigne], buffer);
        idLigne++;
    }
    printf("\n");

    // Nombre de lignes dans le tableau *ligneFichier[]
    int nbLignes = idLigne;
    printf("\nNombre de lignes : %d\n", nbLignes);
    // printf("\n");

    // PARSAGE DES LIGNES PAR MOTS CLES

    // Définition des mots clés
    const char *motClePoints = "Points :";
    const char *motCleHypotheses = "H :";
    const char *motCleResultat = "Résultat :";

    // Parcour du tableau *ligneFichier[]
    for (int i = 0; i < nbLignes; i++)
    {
        // Recherche de la ligne des points
        int resPoints = strncmp(ligneFichier[i], motClePoints, strlen(motClePoints));
        if (resPoints == 0)
        {
            //printf("\"%s\" trouvé à la ligne %d\n", motClePoints, i + 1);

            // PARSAGE DE LA LIGNE DES POINTS AVEC strtok (on rempli nomNoeud[])

            // Définitions de séparateurs possibles.
            const char *separators = " ,.:-!\n";

            char *strToken = strtok(ligneFichier[i], separators);

            // !!! ON PASSE TOUT DE SUITE AU DEUXIEME token POUR IGNORER LE MOT CLE !!!
            strToken = strtok(NULL, separators);

            // chaque point de E est à enregistrer à un index == à une puissande de 2;
            int pow2idTabNoeud = 0;
            // index où sera inscrit le nom du noeud dans le tableau
            int idTabNoeud = 0;
            // cardinal de l'ensemble de points de l'énoncé
            int cardinalE = 0;

            // pour calculer la taille mémoire nécessaire à chaque nom de sous-ensemble
            size_t noeudSize;

            while (strToken != NULL)
            {
                // REMPLISSAGE *nomNoeud[] avec chaque point de E définit dans l'énoncé

                // chaque point de E est à enregistrer à un index == à une puissande de 2; ------------------------(POW A SUPPRIMER !!!)
                idTabNoeud = (int)pow(2, (double)pow2idTabNoeud);
                // on ajoute 1 à la taille mémoire allouée (malloc) à la case du tableau pour le caractère terminal \0
                nomNoeud[idTabNoeud] = malloc(strlen(strToken) + 1);
                // copie de la valeur parsée dans la case voulue
                strcpy(nomNoeud[idTabNoeud], strToken);
                // incrémentation du cardinal pour chaque élément (point) trouvé
                cardinalE++;
                // pour passer à la case "suivante"
                pow2idTabNoeud++;
                // token suivant
                strToken = strtok(NULL, separators);

                // dans la foulée... DEFINITON ET ENREGISTREMENT DES SOUS ENSEMBLES

                // à partir du deuxième point (id == 2)
                if (idTabNoeud > 1)
                {
                    for (int j = 1; j < idTabNoeud; j++)
                    {
                        noeudSize = strlen(nomNoeud[j]) + strlen(nomNoeud[idTabNoeud]) + 1;
                        nomNoeud[idTabNoeud + j] = malloc(noeudSize);
                        strcpy(nomNoeud[idTabNoeud + j], nomNoeud[j]);
                        strcat(nomNoeud[idTabNoeud + j], nomNoeud[idTabNoeud]);
                    }
                }
            }
            // affichage du cardinal de l'ensemble de points considéré
            printf("\nCardinal de l'ensemble : %d\n", cardinalE);

            // affichage des sous ensembles (+ écriture éventuelle dans le fichier)
            // Si on veut écrire le nom des sous ensembles dans le fichier, on s'assure d'être à la fin de l'énoncé
            // fseek(fichier, 0, SEEK_END);
            /* printf("\n");
            int nbNoeuds = (int)pow(2, (double)cardinalE) - 1;
            for (int i = 0; i <= nbNoeuds; i++)
            {
                printf("%s\n", nomNoeud[i]);
                // fprintf(fichier, "\n%s", nomNoeud[i]);
            } */

            printf("\n");
        }

        // CONTRAINTES SUR LES SOUS-ENSEMBLES : recherche d'une ligne d'hypothèse
        int resHypotheses = strncmp(ligneFichier[i], motCleHypotheses, strlen(motCleHypotheses));
        if (resHypotheses == 0)
        {
            //printf("\"%s\" trouvé à la ligne %d\n", motCleHypotheses, i + 1);

            //(void)sscanf(ligneFichier[i], "H : %s %d/%d", noeud, &rkM, &rkm);
            (void)sscanf(ligneFichier[i], "%*s%*s %s %d/%d", noeud, &rkM, &rkm); // ---------------------------------A FAIRE : ECHAPPEMENT DU MOT CLE !!!
            // printf("%s %d/%d\n", noeud, rkM, rkm);

            int j = 1;
            while (strcmp(nomNoeud[j], noeud) != 0)
            {
                j++;
            }
            rkMax[j] = rkM;
            rkMin[j] = rkm;
            printf("Modif. noeud %d : %s %d/%d\n", j, nomNoeud[j], rkMax[j], rkMin[j]);
        }

        // Recherche d'une ligne de résultat
        int resResultat = strncmp(ligneFichier[i], motCleResultat, strlen(motCleResultat));
        if (resResultat == 0)
        {
            //printf("\n\"%s\" trouvé à la ligne %d de l'énoncé.\n", motCleResultat, i + 1);
        }
    }
    printf("\n");

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

    return 0;
}

/* fseek(fichier, 0, SEEK_END);
int fin = ftell(fichier);
fseek(fichier, 0, SEEK_SET);*/
// printf("%ld\n", ftell(fichier));