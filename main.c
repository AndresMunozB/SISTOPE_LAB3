#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"


int main(){
    Wave* wave = NULL;
    
    

    wave = wave_create(10,10,200);
    wave->data[0][2][2] = 100.0;
    first(wave);
    next(wave);
    wave_show(wave);
    printf("chao\n");
    wave_destroy(wave);
    printf("hola\n");
    
    
    

    return 1;
}