#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

pthread_t threads[10];
sem_t semaphore;

void* function(void* args){
	sem_wait(&semaphore);
	printf("Hola:%li\n",pthread_self());
	//sem_post(&semaphore);
}

int main(){

	int i;
	sem_init(&semaphore, 1, 0);
	printf("inciio\n");
    for(i=0;i<10;i++){
        pthread_create(&threads[i] , NULL , function , NULL );
    }
    printf("hola\n");

    for(i=0;i<10;i++){
    	sem_post(&semaphore);
	    
   	} 
    for(i=0;i<10;i++){
    	
        pthread_join ( threads[i] , NULL ) ;
    } 



}