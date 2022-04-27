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
typedef struct {
    int idOrigen;
    int idDestino;
    int hora;
    float tiempoMedioVuelo;

    
} Vuelo;
Vuelo vuelo;

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
	int idO, idD, h, hashNum;
 	float meanTime;

 	

	FILE *arch = fopen("intento2salida", "rb");
 	if (arch == NULL) {
 		printf("Problema al crear el archivo %s. Termina el programa.\n", "practica1Sal.dat");
 		exit(-1);
 	}
 	int cont=0;
	hashNum =hash(idOrigen);
 	while (!feof(arch)){
		fseek(arch, (HASH_RANGE*cont + hashNum)*sizeof(vuelo), SEEK_SET);
		
	fread(&idO, sizeof(int), 1, arch);
 	fread(&idD, sizeof(int), 1, arch);
 	fread(&h, sizeof(int), 1, arch);
 	fread(&meanTime, sizeof(float), 1, arch);
	 if (idO == idOrigen && idD == idDestino && h == hora) {
		printf("Se encontro el vuelo: %i, %i, %i con tiempo de vuelo medio: %.2f.\n", idO, idD, h, meanTime);
		break;
 	} else {
 		fputs("No se ha encontrado ningun vuelo.\n", stdout);
 	}
	 cont++;
	 }

 	
 		
 	
 	
 	fclose(arch);		
 	
}


int main() {	
	buscarVuelo(525, 900, 10);
	fputs("Esperando...\n", stdout);
	int a;
	int x = scanf("%d", &a);
 	return 0;
}
