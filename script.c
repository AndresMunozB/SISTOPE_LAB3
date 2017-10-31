#include <stdio.h> //sprintf
#include <stdlib.h> //malloc
#include <unistd.h> //getpid,fork, execvp
#include <sys/wait.h> //waitpid

int main(){
	int nvalue = 14;
	int i;
    pid_t pidFather = getpid();
    pid_t *arrayPid = (pid_t*) malloc(sizeof(pid_t)*nvalue);
    int *arrayStatus = (int*) malloc(sizeof(int)*nvalue);
    


    
    char Nvalue[10]= "256"; //cambiar a 256
    char Tvalue[10]="8000"; //cambiar a 4000 y 8000
    char Hvalue[10];
    char fvalue[30];
    char tvalue[10]="2000";//no se para que sirve

   	
    
    for(i=1;i<=nvalue;i++){
        arrayPid[i]=fork();
        if(arrayPid[i]==0){
            sprintf(Hvalue,"%d",i);
            sprintf(fvalue,"%s-%s-%s",Nvalue,Tvalue,Hvalue);
		
			
			//SE JUNTAN LOS ARGUMENTOS Y SE EJECUTA EL PROGRAMA COMPARADOR PARA EL PROCESO RECIEN CREADO
           	char *args[] = {"-N",Nvalue,"-T",Tvalue,"-H",Hvalue,"-f",fvalue,"-t",tvalue,NULL};
            execvp("./prueba",args);
            break;
        }
    }
    if(pidFather == getpid()){
		//SE HACE ESPERAR A TODOS LOS HIJOS
        for(i=0;i<nvalue;i++){
            waitpid(arrayPid[i],&arrayStatus[i],0);
		}
	}
}