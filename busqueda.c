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

#define HASH_RANGE 5904703


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

	FILE *arch = fopen("practica1Sal.dat", "rb");
 	if (arch == NULL) {
 		printf("Problema al crear el archivo %s. Termina el programa.\n", "practica1Sal.dat");
 		exit(-1);
 	}
 	int idO, idD, h, hashNum;
 	float meanTime;
 	hashNum = hash(idOrigen);
 	printf("%i, %i\n", idOrigen, hashNum);
 	fseek(arch, hashNum*16, SEEK_SET);
 	int pos = ftell(arch); // Nos informa en que byte del archivo esta el puntero.
	printf("Posición del puntero de archivo antes de grabar: %i\n", pos); 
 	fread(&idO, sizeof(int), 1, arch);
 	pos = ftell(arch); // Nos informa en que byte del archivo esta el puntero.
	printf("Posición del puntero (id Origen) de archivo luego de grabar un entero: %i\n", pos);
 	fread(&idD, sizeof(int), 1, arch);
 	pos = ftell(arch); // Nos informa en que byte del archivo esta el puntero.
	printf("Posición del puntero (id Destino) de archivo luego de grabar un entero: %i\n", pos);
 	fread(&h, sizeof(int), 1, arch);
 	pos = ftell(arch); // Nos informa en que byte del archivo esta el puntero.
	printf("Posición del puntero (hora) de archivo luego de grabar un entero: %i\n", pos);
 	fread(&meanTime, sizeof(float), 1, arch);
 	pos = ftell(arch); // Nos informa en que byte del archivo esta el puntero.
	printf("Posición del puntero (mean time) de archivo luego de grabar un entero: %i\n", pos);
 	
 	printf("%i, %i, %i, %.2f\n", idO, idD, h, meanTime);
 	
 	if (idO == idOrigen && idD == idDestino && h == hora) {
		printf("Se encontro el vuelo: %i, %i, %i con tiempo de vuelo medio: %.2f.\n", idO, idD, h, meanTime);
 	} else {
 		fputs("No se ha encontrado ningun vuelo.\n", stdout);
 	}
 	
 	fclose(arch);
}


int main() {	
	buscarVuelo(1155, 284, 19);
	fputs("Esperando...\n", stdout);
	int a;
	int x = scanf("%d", &a);
 	return 0;
}
