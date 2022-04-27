#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define HASH_RANGE 150//05904703


unsigned int hash(int x) { // Mejorar la función hash
	int c2=0x27d4eb2d; 
	x = (x ^ 12) ^ (x >> 16);
	x = x + (x << 3);
	x = x ^ (x >> 4);
	x = x * c2;
	x = x ^ (x >> 15);
	
    	return x % HASH_RANGE;
}


void buscarVuelo(int idOrigen, int idDestino, int hora) {


}


int main() {	
    	FILE *arch = fopen("intento2salida", "rb");
 	if (arch == NULL) {
 		printf("Problema al crear el archivo %s. Termina el programa.\n", "practica1Sal.dat");
 		exit(-1);
 	}
 	int cont=0;
 	while (!feof(arch)){
 	int idO, idD, h, hashNum;
 	float meanTime;
 	//hashNum = hash(idOrigen);
 	//printf("%i, %i\n", idOrigen, hashNum);
 	//fseek(arch, hashNum*16, SEEK_SET);
 	int pos = ftell(arch); // Nos informa en que byte del archivo esta el puntero.
	//printf("Posición del puntero de archivo antes de grabar: %i\n", pos); 
 	fread(&idO, sizeof(int), 1, arch);
 	pos = ftell(arch); // Nos informa en que byte del archivo esta el puntero.
	//printf("Posición del puntero (id Origen) de archivo luego de grabar un entero: %i\n", pos);
 	fread(&idD, sizeof(int), 1, arch);
 	pos = ftell(arch); // Nos informa en que byte del archivo esta el puntero.
	//printf("Posición del puntero (id Destino) de archivo luego de grabar un entero: %i\n", pos);
 	fread(&h, sizeof(int), 1, arch);
 	pos = ftell(arch); // Nos informa en que byte del archivo esta el puntero.
	//printf("Posición del puntero (hora) de archivo luego de grabar un entero: %i\n", pos);
 	fread(&meanTime, sizeof(float), 1, arch);
 	pos = ftell(arch); // Nos informa en que byte del archivo esta el puntero.
	//printf("%i Posición del puntero (mean time) de archivo luego de grabar un entero: %i\n",cont, pos);
 	cont++;
 	printf("%i, %i, %i, %.2f\n", idO, idD, h, meanTime);
 	}
 	
 	
 	fclose(arch);
 	return 0;
}
