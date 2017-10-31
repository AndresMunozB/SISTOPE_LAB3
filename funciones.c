#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

//ENTRADA: Enteros n y m, que representan las filas y columnas respectivamente
//SALIDA: Puntero a la estructura Matriz
//Esta función se encarga de crear una nueva matriz e inicializar cada posicion con caracter espacio.
Wave* wave_create(int n,int m,int t, int h){
    Wave* wave = (Wave*) malloc(sizeof(Wave));
    wave->row = n;
    wave->col = m;
    wave->steps = t;
    wave->data = (float***) malloc (sizeof(float**)*t);
    wave->barriers = (pthread_barrier_t*) malloc(sizeof(pthread_barrier_t)*t);
    int i,j,k;
    for(i=0;i<t;i++){
        wave->data[i] = (float**) malloc (sizeof(float*)*n);
        pthread_barrier_init(&wave->barriers[i], NULL, h );

        for(j=0;j<n;j++){
            wave->data[i][j] = (float*) malloc(sizeof(float)*m);
            for(k=0;k<m;k++){
                wave->data[i][j][k] = 0.0;
            }
        }
    }
    return wave;
}

//ENTRADA: Puntero a la estructura Matriz
//SALIDA: Void (Nada)
//Función se encarga de liberar la memoria utilizada por la matriz.
void wave_destroy(Wave* wave){
    int i,j;  
    for(i=0;i<wave->steps;i++){
        pthread_barrier_destroy(&wave->barriers[i]);

        for ( j = 0; j < wave->row; j++)
        {
            free(wave->data[i][j]);
        }
        free(wave->data[i]);
    }
    free(wave->data);

    free(wave->barriers);
    free(wave);
}

//ENTRADA: Puntero a la estructura Matriz
//SALIDA: Void (Nada)
//Función al cual le corresponde mostrar los datos de la matriz por consola
void wave_show(Wave *wave){
    int i,j,k;
    for (i=0;i<wave->steps;i++){
        printf("Step:%d\n",i );
        for(j=0;j<wave->row;j++){
            for(k=0;k<wave->col;k++){
                printf("%09.4f   ",wave->data[i][j][k]);

            }
            printf("\n");
        }
        printf("\n");
        
    }
}

void next(Wave* wave){
    int i,j,k;
    float up,down,right,left,before,before2,c,dt,dd,pd;
    c = 1.0;
    dt = 0.1;
    dd = 2.0;
    pd = ((c*c))*((dt/dd)*(dt/dd));

    for ( i = 1; i < wave->steps; i++){
        for ( j = 1; j < wave->row-1; j++){
            for( k = 1; k < wave->col-1;k++){
                calculate(wave,pd,i,j,k);
            }

        }
    }
}



void calculate(Wave* wave,float pd, int i, int j, int k){

    float up,down,right,left,before,before2;

    if(i>1){
    
        up = wave->data[i-1][j-1][k];
        down = wave->data[i-1][j+1][k];
        right = wave->data[i-1][j][k+1];
        left = wave->data[i-1][j][k-1];
        before = wave->data[i-1][j][k];
        before2 = wave->data[i-2][j][k];
        wave->data[i][j][k] = (pd*(up+right+left+down+before-(4*before)))+(2*before)-before2;
    }
    else if(i==1){
        up = wave->data[0][j-1][k];
        down = wave->data[0][j+1][k];
        right = wave->data[0][j][k+1];
        left = wave->data[0][j][k-1];
        before = wave->data[0][j][k];
        wave->data[1][j][k] = ((pd/2)*(up+right+left+down-(4*before)))+before;
    }
}

Thread_t** threads_init(int n, int m, int int_threads){
    int casillas = n*m;
    int i,j;
    int positions;
    int modulo = casillas%int_threads;

    Thread_t** threads = (Thread_t**)malloc(sizeof(Thread_t*)*int_threads+1);
    threads[int_threads] = NULL;

    if(modulo == 0){
        positions = casillas/int_threads;
    }else{
        positions = (casillas/int_threads) + 1;
    }

    for(i = 0; i < int_threads; i++){
        threads[i] = (Thread_t*)malloc(sizeof(Thread_t));
        threads[i]->positions = (Position_t*)malloc(sizeof(Position_t)*positions);
        threads[i]->int_pos = 0;
    }

    
    Position_t pos;
    int counter = 0;
    for(i=1;i<n-1;i++){
        for(j=1;j<m-1;j++){
            pos.row = i;
            pos.col = j;
            threads[counter%int_threads]->positions[threads[counter%int_threads]->int_pos] = pos;
            threads[counter%int_threads]->int_pos++;
            counter++;
        }
    }
    return threads;
}

void threads_destroy(Thread_t** threads,int int_threads){
    int i;
    for(i = 0; i < int_threads; i++){
        free(threads[i]);
        free(threads[i]->positions); 
    }
    free(threads);
}

void threads_show(Thread_t** threads){
    int i = 0; 
    int j;
    while(threads[i] != NULL){
        printf("Hebra %d\n", i);
        printf("IntPos: %d\n",threads[i]->int_pos);
        for(j = 0; j < threads[i]->int_pos; j++){
            printf("%d,%d\n",threads[i]->positions[j].row,threads[i]->positions[j].col);
        }

        i++;
        printf("\n");
    }
}