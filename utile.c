#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "PGI.c"
#include "utile.h"



int unionPratique(int x,int y){
    return(x & y);
}
int interPratique(int x,int y){
    return (x | y);
}
int puissance(int puiss){
    return 1 << puiss;
}
int appartienPratique(int tenir, int appartient){
    return unionPratique(x,y)==x;
}
int RS1Pratique(int x, int y, int rkMinx, int rkMiny, bool continueSat){
    return appartienPratique(x,y) && rkMinx > rkMiny && continueSat;
}
int RS2Pratique(int x, int y, int rkMiny, int rkMinx, bool continueSat){
    return appartienPratique(y,x) && rkMiny > rkMinx && continueSat;
}
int RS3Pratique(int x, int y, int rkMaxy, int rkMaxx, bool continueSat){
    return appartienPratique(x,y) && rkMaxy < rkMaxx && continueSat;
}
int RS4Pratique(int x, int y, int rkMaxy, int rkMaxx, bool continueSat){
    return appartienPratique(y,x) && rkMaxy > rkMaxx && continueSat;
}
int RS5Pratique(int rkMaxx, int rkMaxy,int rkMinunion, int rkMaxinter, bool continueSat){
    return rkMaxx + rkMaxy - rkMinunion < rkMaxinter && continueSat;
}
int RS6Pratique(int rkMaxx, int rkMaxy,int rkMininter, int rkMaxunion, bool continueSat){
    return rkMaxx + rkMaxy - rkMininter < rkMaxunion && continueSat;
}
int RS7Pratique(int rkMinunion, int rkMininter,int rkMaxy, int rkMinx, bool continueSat){
    return rkMinunion + rkMininter - rkMaxy > rkMinx && continueSat;
}
int RS8Pratique(int rkMinunion, int rkMininter,int rkMaxx, int rkMiny, bool continueSat){
    return rkMinunion + rkMininter - rkMaxx > rkMiny && continueSat;
}
/*static inline int log2(int a){
    return a >> 1;
}*/
/*static inline void reinitialise(){
continueSat = false;
y = 0;
x = 0;
}*/