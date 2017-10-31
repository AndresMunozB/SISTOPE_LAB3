#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

#define THREADS 2
#define N 5
#define M 5
#define T 10
#define NP 2
#define MP 2


//VARIABLES GLOBALES
Thread_t** threads = NULL;
int* threads_id = NULL;
Wave_t* wave = NULL;
float pd;
pthread_mutex_t mutex;
//FIN VARIABLES GLOBALES


void* function(void* id_ptr){
    int thread_id = *(int*)id_ptr;
    int i,j;
    int row,col;
    for(i=1;i<wave->steps;i++){
        for(j=0;j<threads[thread_id]->int_pos;j++){
            row = threads[thread_id]->positions[j].row;
            col = threads[thread_id]->positions[j].col;
            calculate(wave,pd,i,row,col);
        }
      	pthread_barrier_wait(&wave->barriers[i]);
    }
    pthread_exit (NULL);
}

int main(){
    
    //VALIDAR ENTRADA

    //FIN VALIDAR ENTRADA


    //PEDIR MEMORIA
    wave = wave_create(N,M,T,THREADS);
    threads = threads_init(N,M,THREADS);
    threads_id = (int*) malloc(sizeof(int)*THREADS);
    //FIN PEDIR MEMORIA


    //PROCESAR INFORMACION
    threads_show(threads);
    wave->data[0][NP][MP] = 100.0;
    int i;
    float c,dt,dd;
    c = 1.0;
    dt = 0.1;
    dd = 2.0;
    pd = ((c*c))*((dt/dd)*(dt/dd));

    //INCIAR THREADS
    for(i=0;i<THREADS;i++){
        threads_id[i]=i;
        pthread_create(&threads[i]->thread,NULL,function,(void*)&threads_id[i]);
    }
    //FIN INICIAR THREADS

    //ESPERAR THREADS
    for(i=0;i<THREADS;i++){
        pthread_join(threads[i]->thread,NULL);
    }
    wave_show(wave);
    //FIN ESPERAR THREADS
    //FIN PROCESAR INFORMACION
    wave_save(wave,"salida.txt");

    //LIBERAR MEMORIA
    wave_destroy(wave);
    threads_destroy(threads);
    free(threads_id);
    //FIN LIBERAR MEMORIA



    //SECUENCIAL
    /*wave = wave_create(N,M,T,THREADS);
    wave->data[0][NP][MP] = 100.0;
    next(wave);
    wave_show(wave);
    wave_destroy(wave);*/
    //FIN SECUENCIAL
    
    

    return 1;
}