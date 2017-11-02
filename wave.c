#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

#define THREADS 2
#define N 5
#define M 5
#define T 10
#define NP 5
#define MP 5


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

int main(int argc, char** argv){
    
    //VALIDAR ENTRADA
     /*     -N tamano_grilla
        -T número_de_pasos 
        -H número_de_hebras
        -f archivo_de_salida 
        -t iteracion_de_salida
*/
    int Nvalue, Tvalue, Hvalue, svalue;
    char fvalue[300];
    if(!opt_get( argc, argv, &Nvalue,&Tvalue,&Hvalue,fvalue,&svalue))
        return 0;  
   
    if(verifyArguments(Nvalue,Tvalue,Hvalue,fvalue,svalue) == 0) 
        return 0;
    //FIN VALIDAR ENTRADA


    //PEDIR MEMORIA
    wave = wave_create(Nvalue,Nvalue,Tvalue,Hvalue);
    threads = threads_init(Nvalue,Nvalue,Hvalue);
    threads_id = (int*) malloc(sizeof(int)*Hvalue);
    //FIN PEDIR MEMORIA

    //PROCESAR INFORMACION
    //threads_show(threads);
    wave->data[0][NP][MP] = 100.0;
    
    
    int i;
    float c,dt,dd;
    c = 1.0;
    dt = 0.1;
    dd = 2.0;
    pd = ((c*c))*((dt/dd)*(dt/dd));

    //INCIAR THREADS
    for(i=0;i<Hvalue;i++){
        threads_id[i]=i;
        pthread_create(&threads[i]->thread,NULL,function,(void*)&threads_id[i]);
    }
    //FIN INICIAR THREADS

    //ESPERAR THREADS
    for(i=0;i<Hvalue;i++){
        pthread_join(threads[i]->thread,NULL);
    }
    wave_show(wave);
    //FIN ESPERAR THREADS
    //FIN PROCESAR INFORMACION

    wave_save(wave,"salida.txt",svalue);

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