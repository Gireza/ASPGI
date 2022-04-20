#include "parseur.h"
#include "ensemble.h"

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
int recupererTableauLignes(FILE * file, char **tableauLignes, char *buffer){
  
  int indiceLigne = 0;

  fseek(file, 0, SEEK_SET); // retour au début du fichier

  // parcours du fichier jusqu'à la dernière ligne
  while (fgets(buffer, 500, file) != NULL){

    tableauLignes[indiceLigne] = (char *)malloc(strlen(buffer) + 1); // casting des lignes du tableau en char, allouer l'espace pour copier buffer
    strcpy(tableauLignes[indiceLigne], buffer); // copie des lignes dans le tableau

    indiceLigne++;
  }

  return 0;
}

/*
Récupère la ligne dans le tableau de lignes grace au mot clé et à son occurence (commence à 0)
*/
int occurenceMotCle(char * motCle, char ** tableauLignes, int nombreLignes){
  
  int nombreOccurence = 0; // initialisation d'occurence

  // parcours du tableau des nombres de lignes
  for (int i = 0; i < nombreLignes; i++){ 

    int resultatTestLigne = strncmp(tableauLignes[i], motCle, strlen(motCle)); // 

    if (resultatTestLigne == 0){ // si la comparaison ne trouve aucune différence

      // incrémentation du nombre d'occurence
      nombreOccurence++;
    }
  }

  return nombreOccurence;
}


/*
Récupère la ligne dans le tableau de lignes grace au mot clé et à son occurence (commence à 0)
*/
int recupererLigne(char * motCle, char ** tableauLignes, char **ligneARecupere, int nombreLignes, int occurence){
  
  int nombreOccurence = 1; // nombre d'occurence actuelle

  // parcours du tableau des nombres de lignes
  for (int i = 0; i < nombreLignes; i++){ 

    int resultatTestLigne = strncmp(tableauLignes[i], motCle, strlen(motCle)); // 

    if (resultatTestLigne == 0){ // si la comparaison ne trouve aucune différence
      
      // si c'est l'occurence que l'on veut 
      if (nombreOccurence == occurence){ 
        
        *ligneARecupere = (char *)malloc(strlen(tableauLignes[i]) + 1);
        strcpy(*ligneARecupere, tableauLignes[i]);

        return 0;
      }

      nombreOccurence++;
    }
  }

  return -1;
  
}

/***
  *Determine le cardinal de l'ensemble des points 
  */
unsigned int determinerCardinal(char **tableauLignes, char *separateurs, int nombreLignes){
  
  unsigned int cardinalEnsemble = 0; 

  char *ligneDesPoints; // variable nécessaire à la restauration des points 
  char *motClePoints = "Points";
  
  if (recupererLigne(motClePoints, tableauLignes, &ligneDesPoints, nombreLignes, 1) == -1) return 0;

  char *strToken = strtok(ligneDesPoints, separateurs);

  // !!! ON PASSE TOUT DE SUITE AU DEUXIEME token POUR IGNORER LE MOT CLE !!!
  strToken = strtok(NULL, separateurs);

  while (strToken != NULL){

    // incrémentation du cardinal pour chaque élément (point) trouvé
    cardinalEnsemble++;
    // token suivant
    strToken = strtok(NULL, separateurs);
  }

  return cardinalEnsemble;
}

void genererTabRgMax(int cardinalEnsemble){
  unsigned int tailleTableau = puissance2(cardinalEnsemble);
  
  unsigned int tabRgMax[tailleTableau];

  tabRgMax[0] = 0;

  for (unsigned int j = 1; j < tailleTableau; j++){
    tabRgMax[j] = cardinal(j);
  }

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

  unsigned int cardinalEnsemble; // initlialisation 

  char *separateurs = " \n";

  cardinalEnsemble = determinerCardinal(tableauLignes, separateurs, nbLignes);

  //printf("cardinal de l'ensemble : %d\n", cardinalEnsemble);
  
  // generation de tabRgMax
  //unsigned int *tabRgMax = genererTabRgMax(cardinalEnsemble);

  // retour des résultats :
  *n_points = cardinalEnsemble;

  return 0;
}
