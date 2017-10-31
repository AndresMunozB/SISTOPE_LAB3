#ifndef _STRUCTS_H_
#define _STRUCTS_H_
#include <pthread.h>

typedef struct position{
    int row;
    int col;
}Position_t;

typedef struct thread{
	int int_pos;
    Position_t* positions;
    pthread_t thread;
}Thread_t;

typedef struct wave{
    float ***data;
    int row;
    int col;
    int steps;
    pthread_barrier_t *barriers;
}Wave_t;

#endif