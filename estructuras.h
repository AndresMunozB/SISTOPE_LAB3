#ifndef _STRUCTS_H_
#define _STRUCTS_H_
#include <pthread.h>

typedef struct wave{
    float ***data;
    int row;
    int col;
    int steps;
    pthread_barrier_t *barriers;
}Wave;

#endif