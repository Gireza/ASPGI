#include <stdlib.h>
#include <stdio.h>
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
