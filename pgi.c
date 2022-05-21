#include "parseur.h"
#include "saturation.h"
#include "ensemble.h"
#include "affichage.h"
#include "string.h"
#include "time.h"

#include <stdio.h>

int main(int argc, char** argv){
  if (argc < 2) {
    printf("Erreur d'argument : indiquer un fichier en paramètre");
    return -1;
  }

  FILE * file = NULL; // initialisation d'un file pour lecture de l'énoncé
  file = fopen(argv[1], "r"); // ouverture du fichier en lecture

  // initialisation du tableau de noms d'ensembles
  char **tableauNomNoeuds;

  // initialisation des tableaux de rang (tableaux d'ints non signés) 
  unsigned int *rkMax; 
  unsigned int *rkMin;

  // initialisation des variables stockant le résultat 
  unsigned int  indexResult;
  unsigned int  rkMaxResult;
  unsigned int  rkMinResult;

  // initialisation du nombre de point
  unsigned int n_points;
  
  // définition des options d'exécution en fonction des arguments passés à l'application
  int pFich = 0;
  int pTerm = 0;
  int pStat = 0;
  for(int i=2; i < argc; i++){
    if(strcmp(argv[i], "-f")==0) pFich = 1;
    if(strcmp(argv[i], "-t")==0) pTerm = 1;
    if(strcmp(argv[i], "-d")==0) pTerm = 2;
    if(strcmp(argv[i], "-s")==0) pStat = 1;
  }
  
  // utilisation de parse
  if (parse(file, &tableauNomNoeuds, &rkMin, &rkMax, &n_points, &indexResult, &rkMaxResult, &rkMinResult) == -1) { printf("Erreur de parsage du fichier"); }

  // Fermeture du fichier d'énoncé
  fclose(file);

  if(pTerm>0){
    printf("Après hypothèses :\n\n");
    affichageTerminal(tableauNomNoeuds, rkMax, rkMin, n_points);
  }
  
  // DEBUT DE LA SATURATION

  time_t timeDebSat = time( NULL );

  saturer(rkMin, rkMax, n_points, tableauNomNoeuds, pTerm);

  time_t timeFinSat = time( NULL );

  unsigned long dureeSaturation = difftime(timeFinSat, timeDebSat);

  if(pTerm>0){
  printf("Après saturation :\n\n");
  affichageTerminal(tableauNomNoeuds, rkMax, rkMin, n_points);
  }

  // écriture des ensembles saturés dans un autre fichier
  if(pFich==1){
    FILE * resultat = NULL;
    resultat = fopen("resultat.txt", "w");
    ecritureFichier(resultat, tableauNomNoeuds, rkMax, rkMin, n_points);
    fclose(resultat);
  }

  // affihage du résultat
  if(pTerm>0){
  printf("Résultat attendu %s %d/%d\n", tableauNomNoeuds[indexResult], rkMaxResult, rkMinResult);
  printf("Résultat obtenu %s %d/%d\n\n", tableauNomNoeuds[indexResult], rkMax[indexResult], rkMin[indexResult]);
  }

  // affichage durée d'exécution de la saturation
  if(pStat==1){
    printf("Durée de la saturation (sec) : %lu\n", dureeSaturation);
    afficherCompteurReglesAppliquees();
  }
  return 0;
}
