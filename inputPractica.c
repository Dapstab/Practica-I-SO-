#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "vueloStruct.h"

int idLugar(int *a)
{
    while (*a < 1 || *a > 1160)
    {
        printf("EL id ingreado no es valido, debe ser un valor entre 1 y 1160. Ingrese nuevamente el valor\n");
        scanf("%d", a);
    }
}
int formatoHora(int *a)
{
    while (*a < 0 || *a > 23)
    {
        printf("EL hora ingreada no es valido, debe ser un valor entre 0 y 23. Ingrese nuevamente el valor\n");
        scanf("%d", a);
    }
}

void escribirTuberia(char *tuberia, struct Datos buffer, int tamano)
{
    // Descriptor del archivo
    int descriptor = open(tuberia, O_WRONLY);
    if (descriptor < 0)
    {
        perror("Hubo un error abriendo el archivo de la tuberia");
        exit(-1);
    }
    int r = write(descriptor, &buffer, sizeof(buffer));
    if (r < 0)
    {
        perror("No se pudo escribir el origen en la tuberia");
    }
    close(descriptor);
}

void leerTuberia(char *tuberia, struct Datos *buffer, int tamano)
{
    // Descriptor del archivo
    int descriptor;
    // Se abre la tuberia
    do
    {
        // Espera a que se cree el archivo tipo FIFO memuBuscador
        descriptor = open(tuberia, O_RDONLY);
    } while (descriptor == -1);

    if (descriptor < 0)
    {
        perror("Hubo un error abriendo el archivo de la tuberia");
        exit(-1);
    }
    // Lee el archivo FIFO y guarla la informacion en buffer
    int r = read(descriptor, buffer, tamano);
    if (r < 0)
    {
        perror("Hubo un error leyendo el archivo de la tuberia");
        exit(-1);
    }
    close(descriptor);
}

int main()
{
    int opc = 0;
    // Ruta del archivo FIFO (tuberia)
    char *tuberia = "./menuBuscador";
    char *tuberia2 = "./buscadorMenu";
    // Crear archivo de tipo FIFO con sus permisos en octal
    mkfifo(tuberia, 0666);

    // Crea una estructura que guardara los datos
    struct Datos *datos;

    do
    {
        printf("Bienvenido\n\n");
        printf("1. Ingresar origen\n");
        printf("2. Ingresar destino\n");
        printf("3. Ingresar hora\n");
        printf("4. Buscar tiempo de viaje medio\n");
        printf("5. Salir\n");
        scanf("%d", &opc);
        int origen;
        int destino;
        int hora;
        float viajeMedio = 0;
        switch (opc)
        {
        case 1:

            printf("Ingrese el ID del origen ");
            scanf("%d", &origen);
            idLugar(&origen);
            printf("El id ingresado fue %d\n", origen);
            datos->idOrigen = origen;
            break;

        case 2:

            printf("Ingrese el ID del destino ");
            scanf("%d", &destino);
            idLugar(&destino);
            printf("El id ingresado fue %d\n", destino);
            datos->idDestino = destino;
            break;

        case 3:
            printf("Ingrese hora del dia ");
            scanf("%d", &hora);
            formatoHora(&hora);
            printf("\nLa hora ingrasado fue %d\n", hora);
            datos->hora = hora;
            break;

        case 4:
            escribirTuberia(tuberia, *datos,sizeof(*datos));
            //leerTuberia(tuberia2, datos, sizeof(*datos));
            //printf("El mensaje recibido fue %d %d %d\n", datos->idOrigen, datos->idDestino, datos->hora);
            break;
        case 5:
            printf("Adios\n");
            // ELimina el archivo FIFO
            unlink(tuberia);
            unlink(tuberia2);
            break;

        default:
            printf("Opcion incorrecta\n");
            break;
        }

    } while (opc != 5);
}


