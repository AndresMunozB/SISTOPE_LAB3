#ifndef _FUNCIONES_H
#define _FUNCIONES_H
#include "estructuras.h"


Wave_t* wave_create(int n,int m,int t, int h);
void wave_destroy(Wave_t* wave);
void wave_show(Wave_t* wave);
void wave_save(Wave_t* wave,char* file_name, int step);
Thread_t** threads_init(int n, int m, int int_threads);
void threads_destroy(Thread_t** threads);
void threads_show(Thread_t** threads);
void secuencial(Wave_t* wave);
void calculate(Wave_t* wave,float pd, int i, int j, int k);
int opt_get(int argc, char** argv,int* Nvalue,int* Tvalue,int* Hvalue,char fvalue[300],int* tvalue);
int fileExists(char* nombreArchivo);
int verifyArguments(int Nvalue, int Tvalue, int Hvalue, char* fvalue, int tvalue);
void impulso(Wave_t* wave);

#endif