#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

#define THREADS 2
void* thread_function(void* args){
	Wave* wave = (Wave*)args;
	int i,j,k;
	for(i=0;i<wave->steps;i++){
		printf("id:%li,step:%d\n",pthread_self(),i);
		pthread_barrier_wait(&wave->barriers[i]);

	}
}
pthread_t threads[THREADS];
int main(){
    Wave* wave = NULL;
    
    
    wave = wave_create(10,10,10,THREADS);
    wave->data[0][2][2] = 100.0;
    //next(wave);
    printf("hola\n");
    int i;
    for(i=0;i<THREADS;i++){
    	pthread_create(&threads[i],NULL,thread_function,(void*)wave);
    }
    for(i=0;i<THREADS;i++){
    	pthread_join(threads[i],NULL);
    }
    //wave_show(wave);
    //printf("chao\n");
    wave_destroy(wave);
    //printf("hola\n");
    
    
    

    return 1;
}