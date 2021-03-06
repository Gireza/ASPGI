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

/*
Determine le cardinal de l'ensemble des points 
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


/*
Remplie rkMax avec les valeurs du cardinal de l'ensemble
*/
int remplirRkMax(int cardinalEnsemble, unsigned int **rkMax){
  
  unsigned int tailleTableau = puissance2(cardinalEnsemble);
  
  // allocation de la mémoire
  *rkMax = (unsigned int *)malloc((tailleTableau * sizeof(unsigned int))); 

  // remplissage du tableau max 
  for (unsigned int j = 0; j < tailleTableau; j++){
    (*rkMax)[j] = cardinal(j);
  }

  return 0;
}


/*
Remplie rkMin avec des 1
*/
int remplirRkMin(int cardinalEnsemble, unsigned int **rkMin){
  unsigned int tailleTableau = puissance2(cardinalEnsemble);
  
  // allocation de la mémoire
  *rkMin = (unsigned int *)malloc((tailleTableau * sizeof(unsigned int))); 
  (*rkMin)[0] = 0;
  // remplissage du tableau max 
  for (unsigned int j = 1; j < tailleTableau; j++){
    (*rkMin)[j] = 1;
  }

  return 0;
}

 /*
Remplie le tableau des noms de noeuds
*/
void completionTableauNomNoeuds(char ***tabNoeuds, char  **tableauLignes,char *separateurs, int nombreLignes){
  
  (*tabNoeuds)[0] = malloc(strlen("Ø") + 1);
  strcpy((*tabNoeuds)[0], "Ø");

  char *ligneDesPoints; // string de stockage de la ligne
  char *motClePoints = "Points";

  recupererLigne(motClePoints, tableauLignes, &ligneDesPoints, nombreLignes, 1);

  char *strToken = strtok(ligneDesPoints, separateurs);

  strToken = strtok(NULL, separateurs);
  
  int indiceTabNoeuds = 0;
  int pow2idTabNoeud = 0;
            
  size_t tailleNoeud;

  while (strToken != NULL) {   
      
    indiceTabNoeuds = puissance2(pow2idTabNoeud);
    // on ajoute 1 à la taille mémoire allouée (malloc) à la case du tableau pour le caractère terminal \0
    (*tabNoeuds)[indiceTabNoeuds] = malloc(strlen(strToken) + 1);
    // copie de la valeur parsée dans la case voulue
    strcpy((*tabNoeuds)[indiceTabNoeuds], strToken);
    // pour passer à la case "suivante"
    pow2idTabNoeud++;

    // token suivant
    strToken = strtok(NULL, separateurs);

    // DEFINITON ET ENREGISTREMENT DES SOUS ENSEMBLES
    // (concaténation du nom du nouveau noeud avec le nom de chacun des sous ensembles précédents, inscrits dans les cases suivant le nouveau point du tableau)
    // !!! ON ARRIVE A 2 PUISSANCE (NB DE POINTS) CASES DE TABLEAU => TAILLE DU TABLEAU A ALLOUER !!!

    // à partir du deuxième point (id == 2)
    if (indiceTabNoeuds > 1) {
      // pour chaque noeud précédent, concaténation avec le nom du nouveau point
      for (int j = 1; j < indiceTabNoeuds; j++) {
        // taille du nom du sous ensemble nomNoeud[j] + nomNoeud[idTabNoeud]
        // (nomNoeud[idTabNoeud] = nom du dernier noeud créé avec le dernier point trouvé et incrit dans la case d'id = idTabNoeud)
        tailleNoeud = strlen((*tabNoeuds)[j]) + strlen((*tabNoeuds)[indiceTabNoeuds]) + 1;
        // allocation de la mémoire de la case idTabNoeud + j
        (*tabNoeuds)[indiceTabNoeuds + j] = malloc(tailleNoeud);
        // copie du nom nomNoeud[j] dans la case nomNoeud[idTabNoeud + j]
        strcpy((*tabNoeuds)[indiceTabNoeuds + j], (*tabNoeuds)[j]);
        // concaténation avec nomNoeud[idTabNoeud]
        strcat((*tabNoeuds)[indiceTabNoeuds + j], (*tabNoeuds)[indiceTabNoeuds]);
      }
    }
  }
}

int completionTableauxRangs(char **tableauNomNoeuds, char **tableauLignes, unsigned int **rkMin, unsigned int **rkMax, int nombreLignes){
  
  unsigned int rkM = 0;
  unsigned int rkm = 0;
  char noeud[30] = {'s','t','o','c','k','a','g','e'}; // initialisation du string du noeud

  char *motCleHypothese = "Hypo";

  int occurence = occurenceMotCle(motCleHypothese, tableauLignes, nombreLignes);

  for (int i = 1 ; i <= occurence ; i++){

    char *ligneHypothese;

    if (recupererLigne(motCleHypothese, tableauLignes, &ligneHypothese, nombreLignes, i) == -1) return -1;
    
    (void)sscanf(ligneHypothese, "%*s %s %d/%d", noeud, &rkM, &rkm); // echappement du mot clé avec %* 

    int j = 1;

    while (strcmp((tableauNomNoeuds)[j], noeud) != 0) {
      j++;
    }

    // mise a jour des rangs min et max 
    (*rkMax)[j] = rkM;
    (*rkMin)[j] = rkm;

  }
  printf("\n");
  return 0;

}

int extractionResultat(char **tableauNomNoeuds, char **tableauLignes, int nombreLignes, unsigned int* indexResult, unsigned int * rkMaxResult, unsigned int * rkMinResult){
  
  unsigned int rkMin = 0;
  unsigned int rkMax = 0;
  unsigned int index = 0;

  char noeud[30] = {'s','t','o','c','k','a','g','e'};

  char *motCleResultat = "Result";

  char *ligneResultat;

  if (recupererLigne(motCleResultat, tableauLignes, &ligneResultat, nombreLignes, 1) == -1) return -1;
  
  (void)sscanf(ligneResultat, "%*s %s %d/%d", noeud, &rkMin, &rkMax); // echappement du mot clé avec %* 
  
  while (strcmp(tableauNomNoeuds[index], noeud) != 0){ // TODO : gestion noeud n'existe pas 
    index++;
  }

  *rkMinResult = rkMin;
  *rkMaxResult = rkMax;
  *indexResult = index;
  

  return 0;
}

int parse(FILE * file, char ***tableauNomNoeuds, unsigned int **rkMin, unsigned int **rkMax, unsigned int* n_points, unsigned int * indexResult, unsigned int * rkMaxResult, unsigned int * rkMinResult){

  if (file == NULL) { return -1; }
  
  // création d'un buffer
  char buffer[501] = "0";

  // récupération du nombre de lignes
  int nbLignesFichier = calculeNombreLignes(file, buffer);

  // intitialisation du tableau pour stocker les lignes de l'énoncé
  char **tableauLignes = malloc(nbLignesFichier * sizeof(char*));
  
  // récupération du contenue du tableau
  recupererTableauLignes(file, tableauLignes, buffer); 

  // récupération du nombre de points = cardinal de l'ensemble
  unsigned int cardinalEnsemble;

  char *separateurs = " \n";

  cardinalEnsemble = determinerCardinal(tableauLignes, separateurs, nbLignesFichier);
  
  // complétion des tableau de rang
  remplirRkMin(cardinalEnsemble, rkMin);
  remplirRkMax(cardinalEnsemble, rkMax);

  // retour des résultats :
  *n_points = cardinalEnsemble;

  
  // Allocation mémoire de tableauNomNoeuds pour la prise en compte des hypothèses
  *tableauNomNoeuds = malloc(puissance2(cardinalEnsemble) * sizeof(char*));
  
  // Remplie le tableau des noms des noeuds
  completionTableauNomNoeuds(tableauNomNoeuds, tableauLignes, separateurs, nbLignesFichier);

  // Complétion des rangs min et max
  if (completionTableauxRangs(*tableauNomNoeuds, tableauLignes, rkMin, rkMax, nbLignesFichier) == -1) return -1;

  // Extraction des résultats
  if (extractionResultat(*tableauNomNoeuds, tableauLignes, nbLignesFichier, indexResult, rkMaxResult, rkMinResult) == -1) return -1;


  return 0;
}
