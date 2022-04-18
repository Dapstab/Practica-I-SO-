//busqueda
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include "vueloStruct.h"

//#define TABLE_SIZE 5904703
//#define TABLE_SIZE 50

typedef struct {
    int idOrigen;
    int idDestino;
    int hora;
    float tiempoMedioVuelo;
    int hash;
    struct vuelo *next;
    
} vuelo;
int  TABLE_SIZE;
vuelo **hash_table;
char nombreArchivoSal;


//vuelo *hash_table[TABLE_SIZE]; // Es mejor que sea un puntero porque:

// 1) No necesito todo el espacio de toda la tabla sino solamente hasta que llene la tabla, solamente necesito el espacio de algunas direcciones.
// 2) Es mas facil decir cuando un espacio esta vacio ya que un puntero puedo "setearlo" a NULL.
unsigned int hash(int x) {
	int c2=0x27d4eb2d; // a prime or an odd constant
	x = (x ^ 61) ^ (x >> 16);
	x = x + (x << 3);
	x = x ^ (x >> 4);
	x = x * c2;
	x = x ^ (x >> 15);
    	return x % TABLE_SIZE;
}
float busqueda( int idOrigen, int idDestino, int hora){
	char nombreArchivoSal[]= "practica1Sal";
	FILE *archSal = fopen(nombreArchivoSal, "r");
 	if (archSal == NULL) {
 		printf("Problema al crear el archivo %s. Termina el programa.\n", nombreArchivoSal);
 		exit(-1);
 	}
 	 	
 	// Primero llegamos a la segunda linea
 	char linea[1000];
	
	
 	fgets(linea, sizeof(linea), archSal); // Titulos de campos
 	
 	// Recordemos que el fgets tambien alamacena el salto de linea!!
 	linea[strlen(linea)-1] = '\0'; // Colocamos el terminador de cadena en vez del salto de linea, la razón de esto es porque vamos a 	agregar una nueva "columna" luego no queremos que se lea ese salto de linea.
 
 	fgets(linea, sizeof(linea), archSal);//es la linea n 
 	//printf("linea completa: %s",linea);
 	char *field = strtok(linea, ";"); // separate linea with ; esto es un vuelo
 	int arr[3]={idOrigen,idDestino,hora};
 	int cont=0;
 	while (field && cont<3) {
 		
 	    //printf("field: %s \n",field); 	    		
		 char *item = strtok_r(field,",",&field);
		 while (item ){
		 //printf("item: %i - ",atoi(item));
		 if (cont==3){
		 //printf("resultado:%s ",item);
		 return atof(item);
		 break;}
		 if (arr[cont]!=atoi(item)){
		 	//printf(" no coincide/n");
		   	break;
		 }
		 //else {printf("coincide:%i/n",cont);
		 //}
		 		 
		 
		 item=strtok_r(NULL,",",&field);
		 cont++;
		 }
		 
 	    field = strtok(NULL, ";");
 	}
 
    return 0.0;
    
}

int main() {
	int idOrigen=553;	
	int idDestino=871;
	int hora=3;
	
	float result =busqueda( idOrigen, idDestino,hora);
	printf("el tiempo medio de viaje es : %.3f" ,result);
	

 	
 
	
}
