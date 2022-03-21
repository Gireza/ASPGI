
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include <ensemble.h>

#define TAILLE_MAX 500
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

    // tableaux rkMax[] et rkMin[] par défaut générés avec rankTabGen.c
    unsigned char rkMax[32] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 4};
    unsigned char rkMin[32] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    // variables nécessaires à la mise à jour des rangs dans le tableau en fonction des contraintes (hypothèses) de l'énoncé
    int rkM = 0;
    int rkm = 0;
    char noeud[32] = {0}; // l'espace doit être assez grand pour recevoir la chaine retournée !!!


    // PARSAGE DU FICHIER PAR LIGNES -> détermination du nombre de lignes

    char buffer[TAILLE_MAX + 1] = "0";
    int nbLignes = 0;

    while (fgets(buffer, TAILLE_MAX, fichier) != NULL)
    {
        nbLignes++;
    }
    // initialisation d'un tableau pour stocker chaque ligne de l'énoncé écrite sur le fichier
    char **ligneFichier = malloc(nbLignes * sizeof(char*));


    // PARSAGE DU FICHIER PAR LIGNES -> *ligneFichier[]

    fseek(fichier, 0, SEEK_SET); // retour au début du fichier !

    int idLigne = 0;

    printf("\nRappel de l'énoncé :\n\n");

    while (fgets(buffer, TAILLE_MAX, fichier) != NULL)
    {
        ligneFichier[idLigne] = (char *)malloc(strlen(buffer) + 1); // -----------------------CASTAGE EN (CHAR *) !!!!
        strcpy(ligneFichier[idLigne], buffer);

        printf("%s", ligneFichier[idLigne]); // affichage de la ligne d'énoncé parsée
        idLigne++;
    }
    printf("\n");

    // Nombre de lignes dans le tableau *ligneFichier[]
    printf("\nNombre de lignes : %d\n", nbLignes);
    // printf("\n");


    // PARSAGE DES LIGNES PAR MOTS CLES

    // Définition des mots clés
    const char *motClePoints = "Points";
    const char *motCleHypotheses = "Hypo";
    const char *motCleResultat = "Résultat";

    // cardinal de l'ensemble de points de l'énoncé
    int cardinalE = 0;
    // taille du tableau nomNoeud
    // int tailleNomNoeud = 1;

    // Définitions de séparateurs possibles pour le parsage avec strtok
    const char *separators = " \n"; // " ,.:-!\n"

    // Déclaration d'une variable pour la SAUVEGARDE DE LA LIGNE DES "POINTS" du fichier
    char *ligneDesPoints;

    // 1er PARCOUR DU TABLEAU *ligneFichier[] : determination du cardinal de l'ensemble pour initialisation des tableaux de noeuds, rkMin, rkMax
    for (int i = 0; i < nbLignes; i++)
    {
        // Recherche de la ligne des points
        int resutatTestPoints = strncmp(ligneFichier[i], motClePoints, strlen(motClePoints));
        if (resutatTestPoints == 0)
        {
            // SAUVEGARDE DE LA LIGNE DES POINTS
            ligneDesPoints = (char *)malloc(strlen(ligneFichier[i]) +1);
            strcpy(ligneDesPoints, ligneFichier[i]);
            
            // PARSAGE DE LA LIGNE DES POINTS AVEC strtok

            char *strToken = strtok(ligneFichier[i], separators);

            // !!! ON PASSE TOUT DE SUITE AU DEUXIEME token POUR IGNORER LE MOT CLE !!!
            strToken = strtok(NULL, separators);

            while (strToken != NULL)
            {
                // affichage strToken courant
                //printf("%s\n", strToken);

                // incrémentation du cardinal pour chaque élément (point) trouvé
                cardinalE++;
                // token suivant
                strToken = strtok(NULL, separators);
            }
        }
    }


    // affichage du cardinal de l'ensemble de points considéré
    printf("Cardinal de l'ensemble : %d\n", cardinalE);
    printf("\n");

    // cardinal du l'ensemble de noeuds
    int cardinalEnsembleNoeuds = puissance(cardinalE);
    // initialisation d'un tableau pour stocker chaque ligne de l'énoncé écrite sur le fichier
    char **nomNoeud = malloc(cardinalEnsembleNoeuds * sizeof(char*));

    // initialisation du premier élément du tableau de noms à "Ø"
    nomNoeud[0] = malloc(strlen("Ø") + 1);
    strcpy(nomNoeud[0], "Ø");


    // 2nd PARCOUR DU TABLEAU *ligneFichier[] : remplissage du tableau de noms de noeuds
    for (int i = 0; i < nbLignes; i++)
    {
        // Recherche de la ligne des points
        int resutatTestPoints = strncmp(ligneFichier[i], motClePoints, strlen(motClePoints));
        if (resutatTestPoints == 0)
        {
            // RESTAURATION DE LA LIGNE DES POINTS
            //ligneFichier[i] = ligneDesPoints;
            ligneFichier[i] = (char *)malloc(strlen(ligneDesPoints) + 1); // -----------------------CASTAGE EN (CHAR *) !!!!
            strcpy(ligneFichier[i], ligneDesPoints);

            // PARSAGE DE LA LIGNE DES POINTS AVEC strtok (on rempli nomNoeud[])

            char *strToken = strtok(ligneFichier[i], separators);

            // !!! ON PASSE TOUT DE SUITE AU DEUXIEME token POUR IGNORER LE MOT CLE !!!
            strToken = strtok(NULL, separators);

            // chaque point de E est à enregistrer à un index == à une puissande de 2;
            int pow2idTabNoeud = 0;
            // index où sera inscrit le nom du noeud dans le tableau
            int idTabNoeud = 0;

            // pour calculer la taille mémoire nécessaire à chaque nom de sous-ensemble
            size_t noeudSize;

            while (strToken != NULL)
            {   
                // REMPLISSAGE *nomNoeud[] avec chaque point de E définit dans l'énoncé

                // chaque point de E est à enregistrer à un index == à une puissande de 2; ------------------------(POW A SUPPRIMER !!!)
                
                idTabNoeud = puissance(pow2idTabNoeud);
                // on ajoute 1 à la taille mémoire allouée (malloc) à la case du tableau pour le caractère terminal \0
                nomNoeud[idTabNoeud] = malloc(strlen(strToken) + 1);
                // copie de la valeur parsée dans la case voulue
                strcpy(nomNoeud[idTabNoeud], strToken);
                // pour passer à la case "suivante"
                pow2idTabNoeud++;

                // token suivant
                strToken = strtok(NULL, separators);

                // DEFINITON ET ENREGISTREMENT DES SOUS ENSEMBLES
                // (concaténation du nom du nouveau noeud avec le nom de chacun des sous ensembles précédents, inscrits dans les cases suivant le nouveau point du tableau)
                // !!! ON ARRIVE A 2 PUISSANCE (NB DE POINTS) CASES DE TABLEAU => TAILLE DU TABLEAU A ALLOUER !!!

                // à partir du deuxième point (id == 2)
                if (idTabNoeud > 1)
                {
                    // pour chaque noeud précédent, concaténation avec le nom du nouveau point
                    for (int j = 1; j < idTabNoeud; j++)
                    {
                        // taille du nom du sous ensemble nomNoeud[j] + nomNoeud[idTabNoeud]
                        // (nomNoeud[idTabNoeud] = nom du dernier noeud créé avec le dernier point trouvé et incrit dans la case d'id = idTabNoeud)
                        noeudSize = strlen(nomNoeud[j]) + strlen(nomNoeud[idTabNoeud]) + 1;
                        // allocation de la mémoire de la case idTabNoeud + j
                        nomNoeud[idTabNoeud + j] = malloc(noeudSize);
                        // copie du nom nomNoeud[j] dans la case nomNoeud[idTabNoeud + j]
                        strcpy(nomNoeud[idTabNoeud + j], nomNoeud[j]);
                        // concaténation avec nomNoeud[idTabNoeud]
                        strcat(nomNoeud[idTabNoeud + j], nomNoeud[idTabNoeud]);
                    }
                }
            }

            // affichage des sous ensembles (+ écriture éventuelle dans le fichier)

            // Si on veut écrire le nom des sous ensembles dans le fichier, on s'assure d'être à la fin de l'énoncé
            // fseek(fichier, 0, SEEK_END);

            // printf("\n");
            //     int nbNoeuds = (int)pow(2, (double)cardinalE) - 1;
            //     for (int i = 0; i <= nbNoeuds; i++)
            //     {
            //         printf("%s\n", nomNoeud[i]);
            //         // fprintf(fichier, "\n%s", nomNoeud[i]);
            //     }
            // printf("\n");
        }

        // CONTRAINTES SUR LES SOUS-ENSEMBLES : recherche d'une ligne d'hypothèse
        int resultatTestHypotheses = strncmp(ligneFichier[i], motCleHypotheses, strlen(motCleHypotheses));
        if (resultatTestHypotheses == 0)
        {
            (void)sscanf(ligneFichier[i], "%*s %s %d/%d", noeud, &rkM, &rkm); // ECHAPPEMENT DU MOT CLE !!!
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

    // affichage nomNoeud
    for (int i = 0; i < cardinalEnsembleNoeuds; i++){
        printf("%s, ", nomNoeud[i]);
    }
    printf("\n");

    // affichage des rangs mis à jour...
    for (int i = 0; i < cardinalEnsembleNoeuds; i++)
    {
        printf("%d, ", rkMax[i]);
    }
    printf("\n");
    for (int i = 0; i < cardinalEnsembleNoeuds; i++)
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