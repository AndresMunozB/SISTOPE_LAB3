all:
	gcc -o wave wave.c funciones.c -lpthread -Wall
	echo "./wave -N 256 -T 4000 -H 14 -f archivo_de_salida -t 4000"
	
