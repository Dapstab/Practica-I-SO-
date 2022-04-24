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
#define TABLE_SIZE 5904703


unsigned int hash(int x) { // Mejorar la función hash
	int c2=0x27d4eb2d; 
	x = (x ^ 12) ^ (x >> 16);
	x = x + (x << 3);
	x = x ^ (x >> 4);
	x = x * c2;
	x = x ^ (x >> 15);
	
    	return x % HASH_RANGE;
}


void generarArchivoSal() {
	char nombreArchivoEnt[] = "practica1.csv";
 	char nombreArchivoSal[] = "practica1Sal.dat";
 	 
 	FILE *arch = fopen(nombreArchivoEnt, "r");
 	if (arch == NULL) {
 		printf("Problema al abrir el archivo %s. Termina el programa.\n", nombreArchivoEnt);
 		exit(-1);
 	}
 	
 	FILE *archSal = fopen(nombreArchivoSal, "wb");
 	if (archSal == NULL) {
 		printf("Problema al crear el archivo %s. Termina el programa.\n", nombreArchivoSal);
 		exit(-1);
 	}
 	 	
 	// Primero llegamos a la segunda linea
 	char linea[1000];
	 		 
 	fgets(linea, sizeof(linea), arch); // Titulos de campos
 	unsigned int hashNum;
 	int i, idOrigen;
 	for (i=0; i<TABLE_SIZE; i++) {
 		fgets(linea, 1000, arch);
 		char nro1[5] = "\0";
		int j = 0, k = 0;
		while (linea[j] != ',') nro1[k++] = linea[j++];
		nro1[j] = '\0';
 		int idOrigen = atoi(nro1);	

 		j++;
 		k = 0;
		char nro2[5] = "\0";
 		while (linea[j] != ',') nro2[k++] = linea[j++];
 		nro2[j] = '\0';	
 		int idDestino = atoi(nro2);
 		
 		j++;
 		k = 0;
 		char nro3[5] = "\0";
 		while (linea[j] != ',') nro3[k++] = linea[j++];
 		nro3[j] = '\0';
 		int hora = atoi(nro3);
 		
 		j++;
 		k = 0;
 		
 		char nro4[10] = "\0";
 		while (linea[j] != ',') nro4[k++] = linea[j++];
 		nro4[j] = '\0';
 		float meanTime = atof(nro4);

		
		int hashNum = hash(idOrigen);
 		printf("ID DE ORIGEN/HASH: %i, %i\n", idOrigen, hashNum);
		fseek(archSal, hashNum*16, SEEK_SET);
		
		// ID ORIGEN
		fwrite(&idOrigen, sizeof(int), 1, archSal);
		int pos = ftell(archSal); // Nos informa en que byte del archivo esta el puntero.
		printf("Posición del puntero (id Origen) de archivo luego de grabar un entero: %i\n", pos);
		
		//ID DESTINO
		fwrite(&idDestino, sizeof(int), 1, archSal);
		pos = ftell(archSal); // Nos informa en que byte del archivo esta el puntero.
		printf("Posición del puntero (id Destino) de archivo luego de grabar un entero: %i\n", pos); 
		
		// HORA
		fwrite(&hora, sizeof(int), 1, archSal);
		pos = ftell(archSal); // Nos informa en que byte del archivo esta el puntero.
		printf("Posición del puntero (hora) de archivo luego de grabar un entero: %i\n", pos); 
 		
 		// MEAN TIME
		fwrite(&meanTime, sizeof(float), 1, archSal);
		pos = ftell(archSal); // Nos informa en que byte del archivo esta el puntero.
		printf("Posición del puntero (mean time) de archivo luego de grabar un entero: %i\n", pos); 
 		
 		printf("%i, %i, %i, %.2f\n", idOrigen, idDestino, hora, meanTime);
 	}
 	
 	fclose(arch);
 	fclose(archSal); 	
}


int main() {	
	generarArchivoSal();		
 	return 0;
}
