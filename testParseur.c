#include<stdlib.h>
#include<stdio.h>

#include<ensemble.h>
#include<parseur.h>

int main(void){
    
    int mavar1 = 2;
    
    printf("ma variable vaut : %d\n", mavar1);

    mavar1 = puissance(mavar1);
    printf("après puissance, ma variable vaut : %d\n", mavar1);
    
    int mavar2;

    mavar2 = modifier(mavar1);

    printf("le logarithme de mavar est : %d\n", mavar2);
    
}