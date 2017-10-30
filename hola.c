void* thread_function(void* args){
	Wave* wave = (Wave*)args;
	int i,j,k;
	for(i=0;i<wave->steps;i++){
		printf("id:%li,step:%d\n",pthread_self(),i);
		pthread_barrier_wait(&wave->barriers[i]);

	}
}

/*for(i=0;i<THREADS;i++){
    	pthread_create(&threads[i],NULL,thread_function,(void*)wave);
    }
    for(i=0;i<THREADS;i++){
    	pthread_join(threads[i],NULL);
    }
    //wave_show(wave);
    //printf("chao\n");
    wave_destroy(wave);
    //printf("hola\n");
    */