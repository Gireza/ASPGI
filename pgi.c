#include "parseur.h"
#include "saturation.h"
#include "ensemble.h"
#include "affichage.h"
#include "string.h"

#include <stdio.h>

int main(int argc, char** argv){
  if (argc < 2) {
    printf("erreur dans les arguments");
    return -1;
  }

  FILE * file = NULL; // initialisation de file
  file = fopen(argv[1], "r+"); // ouverture du fichier en lecture

  // fichier pour l'écriture du résultat
  /* FILE * result = NULL;
  result = fopen("result.txt", "a");
  fprintf(result, "Bonjour !");
  fclose(result); */

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
 
  int pFich = 0;
  int pTerm = 0;
  for(int i=2; i < argc; i++){
    if(strcmp(argv[i], "-f")==0) pFich = 1;
    if(strcmp(argv[i], "-t")==0) pTerm = 1;
    if(strcmp(argv[i], "-d")==0) pTerm = 2;
  }
  
  // utilisation de parse
  if (parse(file, &tableauNomNoeuds, &rkMin, &rkMax, &n_points, &indexResult, &rkMaxResult, &rkMinResult) == -1) { printf("Erreur de parsage du fichier"); }

  // Fermeture du fichier
  fclose(file);

  if(pTerm>0){
    printf("Après hypothèses :\n\n");
    affichageTerminal(tableauNomNoeuds, rkMax, rkMin, n_points);
  }
  
  // DEBUT DE LA SATURATION

  saturer(rkMin, rkMax, n_points);

  if(pTerm>0){
  printf("Après saturation :\n\n");
  affichageTerminal(tableauNomNoeuds, rkMax, rkMin, n_points);
  }

  /* // écriture des ensembles saturés dans le fichier
  fprintf(file, "\n");
  for (unsigned int i = 1; i < puissance2(n_points); i ++){
    fprintf(file, "%s %d/%d\n", tableauNomNoeuds[i], rkMax[i], rkMin[i]);
  } */
  if(pFich==1){
    FILE * resultat = NULL;
    resultat = fopen("resultat.txt", "w");
    ecritureFichier(resultat, tableauNomNoeuds, rkMax, rkMin, n_points);
    fclose(resultat);
  }
  // Fermeture du fichier de resultat
  

  // affihage du résultat
  printf("Résultat attendu %s %d/%d\n\n", tableauNomNoeuds[indexResult], rkMaxResult, rkMinResult);


  return 0;

}
