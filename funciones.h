#ifndef _FUNCIONES_H
#define _FUNCIONES_H
#include "estructuras.h"

Wave* wave_create(int n,int m,int t, int h);
void wave_destroy(Wave* wave);
void wave_show(Wave *wave);
Thread_t** threads_init(int n, int m, int int_threads);
void threads_destroy(Thread_t** threads,int int_threads);
void threads_show(Thread_t** threads);
void secuencial(Wave* wave);
void calculate(Wave* wave,float pd, int i, int j, int k);




#endif