#include<stdlib.h>
#include<stdio.h>

#include<ensemble.h>
#include<parseur.h>




int main(void){
    
    int mavar1 = 2;
    
    //printf("ma variable vaut : %d\n", mavar1);

    mavar1 = puissance(mavar1);
    //printf("après puissance, ma variable vaut : %d\n", mavar1);
    
    unsigned char rkMax[32] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 4};

    int card = cardinal(1);

    printf("Le cardinal, de AB est : %d\n", card);
    
}