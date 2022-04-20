#include "parseur.h"


/* 
determine le nombre de lignes du fichier 
 */
int calculeNombreLignes(FILE * file, char *buffer){

  int nbLignes = 0;

  // parcours du fichier jusqu'à la dernière ligne
  while (fgets(buffer, 500, file) != NULL) {
    nbLignes++;
  }

  return nbLignes;
}

/*
Récupère les lignes du fichier dans un tableau de string
*/
int recupererTableauLignes(FILE * file, char **tableauLigne, char *buffer){
  
  int indiceLigne = 0;

  fseek(file, 0, SEEK_SET); // retour au début du fichier

  // parcours du fichier jusqu'à la dernière ligne
  while (fgets(buffer, 500, file) != NULL){

    tableauLigne[indiceLigne] = (char *)malloc(strlen(buffer) + 1); // casting des lignes du tableau en char, allouer l'espace pour copier buffer
    strcpy(tableauLigne[indiceLigne], buffer); // copie des lignes dans le tableau

    indiceLigne++;
  }

  return 0;
}


/*
void recupererLigne(char * motCle, char ** tableauLignes, char *ligneRecupere, int nombreLignes){

  for (int i = 0; i < nombreLignes; i++){
    int resultatTestLigne = strncmp(tableauLignes[i], motCle, strlen(motCle));
    if (resultatTestLigne == 0){
      *ligneRecupere = (char *)malloc(strlen(tableauLignes[i]) + 1);
      strcpy(ligneRecupere, )
    }
  }
  
}


char* clonerLigne(char * ligne){

}
*/


/***
  *Determine le cardinal de l'ensemble des points 
  */
unsigned int determinerCardinal(char **tableauLignes, char *separateurs, int nombreLignes){
  
  unsigned int cardinaleEnsemble = 0; 

  char *ligneDesPoints; // variable nécessaire à la restauration des points 

  const char *motClePoints = "Points";

  for (int i = 0; i < nombreLignes; i++) {
    // Recherche de la ligne des points
    int resutatTestPoints = strncmp(tableauLignes[i], motClePoints, strlen(motClePoints));
    if (resutatTestPoints == 0)
    {
      // SAUVEGARDE DE LA LIGNE DES POINTS
      ligneDesPoints = (char *)malloc(strlen(tableauLignes[i]) +1);
      strcpy(ligneDesPoints, tableauLignes[i]);
      
      // PARSAGE DE LA LIGNE DES POINTS AVEC strtok

      char *strToken = strtok(ligneDesPoints, separateurs);

      // !!! ON PASSE TOUT DE SUITE AU DEUXIEME token POUR IGNORER LE MOT CLE !!!
      strToken = strtok(NULL, separateurs);

      while (strToken != NULL){
        // affichage strToken courant
        //printf("%s\n", strToken);

        // incrémentation du cardinal pour chaque élément (point) trouvé
        cardinaleEnsemble++;
        // token suivant
        strToken = strtok(NULL, separateurs);
      }
    }
  }

  return cardinaleEnsemble;
}

int parse(FILE * file, unsigned int** rkMin, unsigned int** rkMax, unsigned int* n_points){

  if (file == NULL) { return -1; }
  
  // TODO
  *rkMin = NULL;
  *rkMax = NULL;
  *n_points = 0;
  

  // création d'un buffer
  char buffer[501] = "0";

  // récupération du nombre de lignes
  int nbLignes = calculeNombreLignes(file, buffer);

  //printf("nombre de lignes du fichier : %d\n", nbLignes);

  // intitialisation du tableau pour stocker les lignes de l'énoncé
  char **tableauLignes = malloc(nbLignes * sizeof(char*));
  
  // récupération du contenue du tableau
  recupererTableauLignes(file, tableauLignes, buffer); 

  // récupération du nombre de points = cardinal de l'ensemble

  unsigned int cardinalEnsemble = 0; // initlialisation 

  char *separateurs = " \n";

  cardinalEnsemble = determinerCardinal(tableauLignes, separateurs, nbLignes);

  printf("cardinal de l'ensemble : %d", cardinalEnsemble);


  return 0;
}
