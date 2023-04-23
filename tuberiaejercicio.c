#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
int main()
{
    int tuberias[3][2];
    int i;
    int suma = 0;

    // Creo una tuberia para cada hijo
    for (i = 0; i < 3; i++)
    {
        if (pipe(tuberias[i]) == -1)
        {
            printf("Error al crear la tuberia");
        }
    }
        // Creando los hijos
    for (i = 0; i < 3; i++)
    {
            pid_t pid = fork();
            if (pid == -1)
            {
                printf("Erroral crear el hijo");
            }
            else if (pid == 0)
            {
                int numero;
                close(tuberias[i][0]); // Cierro el proceso de lectura
                printf("Introduce un numero del Hijo %d : ", i + 1);
                scanf("%d", &numero);
                system("cls");
                write(tuberias[i][1], &numero, sizeof(numero)); // Escribo el numero
                close(tuberias[i][1]);                          // Cierro tuberia en escritura
            }
    }
    
    // Padre
    for (i = 0; i < 3; i++)
    {
        close(tuberias[i][1]); // Cierro escritura del lado de padre
        int numero_hijo;
        read(tuberias[i][0], &numero_hijo, sizeof(numero_hijo)); // Leo el numero de hijo en la tuberia
        close(tuberias[i][0]);                                   // Cierro lectura
        printf("Padre:\n Numero recibido del hijo %d: , %d", i + 1, numero_hijo);
        system("cls");
        suma += numero_hijo; // sumo los numeros que recibo de cada hijo
    }
    printf("Padre: \n La suma de los numeros de todos mis hijos es: %d", suma);
}