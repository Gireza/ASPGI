#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <ensemble.h>
#include <saturation.h>

int enlever(int x, int y){
    return x - y;
}

int devaluer(int base){
    return logarithme(base) - 3;
}