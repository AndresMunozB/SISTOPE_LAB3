#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

#define THREADS 2
#define N 10
#define M 10
#define T 10
#define NP 4
#define MP 4

Thread_t** threads = NULL;
int* threads_id = NULL;
Wave* wave = NULL;




int main(){
    
    
    
    wave = wave_create(N,M,T,THREADS);
    wave->data[0][NP][MP] = 100.0;
    int i;

    threads = threads_init(N,M,THREADS);
    threads_show(threads);
    
    
    

    return 1;
}