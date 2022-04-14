#include<stdlib.h>
#include<stdio.h>

#include<ensemble.h>
#include<saturation.h>
#include<parseur.h>

int main(void){
   
      FILE *fichier = NULL;
    fichier = fopen("fichier.txt", "r+"); // r+ pour lire et écrire !

    if (fichier == NULL) // On ne trouve pas le fichier...
    {
        printf("Impossible de trouver le fichier \"fichier.txt\"\n");
        return 0;
        // TODO : gestion des erreurs...
    }
    unsigned int rkMax[0] = {};
    unsigned int rkMin[0] = {};
    int n_points = 0;
   
   parse(fichier,rkMin,rkMax,n_points);
   saturation(rkMin,rkMax,n_points);

}
