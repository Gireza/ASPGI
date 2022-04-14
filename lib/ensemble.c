#include <ensemble.h>

int unionPratique(int x,int y){
    return(x & y);
}

int interPratique(int x,int y){
    return (x | y);
}

int puissance(int puiss){
    return 1 << puiss;
}

int logarithme(int x){
    int n = 0;
    while (puissance(n)<x){
        n++;
    }
    return n;
}

int appartienPratique(int tenir, int appartient){
    return unionPratique(tenir,appartient)==tenir;
}

// prend l'indice de l'ensemble dans le tableau dont on veux connaitre le cardinal
// et renvoie ce cardinal
int cardinal(int indiceEnsemble){
    int nombre = indiceEnsemble;
    int nbBits = logarithme(nombre) + 1;
    int nombreDeUn = 0;
    // parcour des bits de nbBits
    for (int bit = 1 ; bit <= nbBits ; bit++) {

        // si le premier bit est égale à 1, on incrémente nbUns
        if (nombre%2 == 1) {
            nombreDeUn++;
        }

        // on change le bit considéré par décalage à droite bit à bit (opérateur bitwise)
        nombre = nombre >> 1;
    }

    return nombreDeUn;
}
