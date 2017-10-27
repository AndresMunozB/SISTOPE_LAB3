#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

//ENTRADA: Enteros n y m, que representan las filas y columnas respectivamente
//SALIDA: Puntero a la estructura Matriz
//Esta función se encarga de crear una nueva matriz e inicializar cada posicion con caracter espacio.
Wave* wave_create(int n,int m,int t){
    Wave* wave = (Wave*) malloc(sizeof(Wave));
    wave->row = n;
    wave->col = m;
    wave->steps = t;
    wave->data = (float***) malloc (sizeof(float**)*t);
    int i,j,k;
    for(i=0;i<t;i++){
        wave->data[i] = (float**) malloc (sizeof(float*)*n);
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
        for ( j = 0; j < wave->row; j++)
        {
            free(wave->data[i][j]);
        }
        free(wave->data[i]);
    }
    free(wave->data);
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

void first(Wave* wave){
    int i,j;
    float up,down,right,left,before,c,dt,dd,pd;
    c = 1.0;
    dt = 0.1;
    dd = 2.0;
    pd = ((c*c)/2)*((dt/dd)*(dt/dd));
    for ( i = 1; i < wave->row-1; i++)
    {
        for ( j = 1; j < wave->col-1; j++)
        {
            up = wave->data[0][i-1][j];
            down = wave->data[0][i+1][j];
            right = wave->data[0][i][j+1];
            left = wave->data[0][i][j-1];
            before = wave->data[0][i][j];
            wave->data[1][i][j] = (pd*(up+right+left+down-(4*before)))+before;
        }
    }
}
void next(Wave* wave){
    int i,j,k;
    float up,down,right,left,before,before2,c,dt,dd,pd;
    c = 1.0;
    dt = 0.1;
    dd = 2.0;
    pd = ((c*c))*((dt/dd)*(dt/dd));

    for ( i = 2; i < wave->steps; i++)
    {
        for ( j = 1; j < wave->row-1; j++)
        {
            for( k = 1; k < wave->col-1;k++){
                up = wave->data[i-1][j-1][k];
                down = wave->data[i-1][j+1][k];
                right = wave->data[i-1][j][k+1];
                left = wave->data[i-1][j][k-1];
                before = wave->data[i-1][j][k];
                before2 = wave->data[i-2][j][k];
                wave->data[i][j][k] = (pd*(up+right+left+down+before-(4*before)))+(2*before)-before2;
                printf("dentro\n");
            }

        }
    }
}