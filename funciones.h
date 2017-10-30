#ifndef _FUNCIONES_H
#define _FUNCIONES_H
#include "estructuras.h"

Wave* wave_create(int n,int m,int t, int h);
void wave_destroy(Wave* wave);
void wave_show(Wave *wave);
void next(Wave* wave);
void calculate(Wave* wave,float pd, int i, int j, int k);

#endif