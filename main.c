#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

#define THREADS 2
#define N 5
#define M 5
#define T 10
#define NP 2
#define MP 2

Thread_t** threads = NULL;
int* threads_id = NULL;
Wave* wave = NULL;
float pd;
pthread_mutex_t mutex;

void* function(void* id_ptr){
    
    int thread_id = *(int*)id_ptr;
    int i,j;
    int row,col;
    for(i=1;i<wave->steps;i++){
        //pthread_mutex_lock(&mutex);
        //printf("thread:%d,step:%d,pd:%09.4f \n",thread_id,i,pd);

        for(j=0;j<threads[thread_id]->int_pos;j++){
            row = threads[thread_id]->positions[j].row;
            col = threads[thread_id]->positions[j].col;
            //printf("pos: %d,%d\n",row,col );
            calculate(wave,pd,i,row,col);
        }
        //pthread_mutex_unlock(&mutex);
      	pthread_barrier_wait(&wave->barriers[i]);
    }

}

int main(){
    
    
    //pthread_mutex_init(&mutex,NULL);
    
    wave = wave_create(N,M,T,THREADS);
    wave->data[0][NP][MP] = 100.0;
    threads_id = (int*) malloc(sizeof(int)*THREADS);
    threads = threads_init(N,M,THREADS);
    threads_show(threads);
    float c,dt,dd;
    c = 1.0;
    dt = 0.1;
    dd = 2.0;
    pd = ((c*c))*((dt/dd)*(dt/dd));
    //printf("pd:%09.4f \n",pd);

    int i;
    for(i=0;i<THREADS;i++){
        threads_id[i]=i;
        pthread_create(&threads[i]->thread,NULL,function,(void*)&threads_id[i]);
    }
    for(i=0;i<THREADS;i++){
        pthread_join(threads[i]->thread,NULL);
    }
    threads_destroy(threads,THREADS);
    wave_show(wave);
    wave_destroy(wave);
    free(threads_id);

    //secuencial 
    /*wave = wave_create(N,M,T,THREADS);
    wave->data[0][NP][MP] = 100.0;
    next(wave);
    wave_show(wave);
    wave_destroy(wave);*/

    
    

    return 1;
}