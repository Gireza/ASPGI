#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

bool continueSat = false;
int y = 0;
int x = 0;

static inline int unionPratique(int x,int y){
    return(x & y);
}
static inline int interPratique(int x,int y){
    return (x | y);
}
static inline int puissance(int puiss){
    return 1 << puiss;
}
/*static inline int log2(int a){
    return a >> 1;
}*/
static inline void reinitialise(){
continueSat = false;
y = 0;
x = 0;
}