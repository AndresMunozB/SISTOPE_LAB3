all:
	gcc -o wave wave.c funciones.c -lpthread -Wall
	echo "./wave -N tamano_grilla -T número_de_pasos -H número_de_hebras -f archivo_de_salida -t iteracion_de_salida"
	
