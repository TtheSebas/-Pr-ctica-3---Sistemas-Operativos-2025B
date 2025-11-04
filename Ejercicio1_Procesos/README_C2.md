Ejercicio 2 - Comunicación entre procesos con fork() y archivo
Descripción

Este programa en C demuestra cómo un proceso padre y un proceso hijo pueden ejecutar tareas diferentes después de una llamada a fork().
El proceso padre incrementa una variable en pasos de 10, mientras que el proceso hijo registra los valores en un archivo de texto llamado valores.txt.
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>

int main()
{
    int pid;
    int variable = 0;
    FILE *archivo;
    
    pid = fork();
    
    switch(pid)
    {
        case -1: // Si pid es -1 quiere decir que ha habido un error
            printf("No se ha podido crear el proceso hijo\n");
            break;
            
        case 0: // Cuando pid es cero quiere decir que es el proceso hijo
            // El hijo abre el archivo para escritura
            archivo = fopen("valores.txt", "w");
            if (archivo == NULL) {
                printf("Error al abrir el archivo\n");
                exit(1);
            }
            
            // El hijo espera y registra los valores
            for(int i = 0; i < 10; i++) {
                sleep(1); // Pausa para que el padre actualice la variable
                fprintf(archivo, "Valor: %d\n", variable);
                fflush(archivo);
            }
            
            fclose(archivo);
            printf("Hijo: Valores registrados en el archivo\n");
            break;
            
        default: // Cuando es distinto de cero es el padre
            // El padre incrementa la variable 10 veces en pasos de 10
            for(int i = 0; i < 10; i++) {
                variable += 10;
                printf("Padre: Variable incrementada a %d\n", variable);
                sleep(1);
            }
            
            wait(0);
            printf("Padre: Proceso hijo terminado\n");
            break;
    }
    
    return 0;
}

Explicación

El proceso padre y el proceso hijo no comparten directamente la memoria, por lo que cada uno tiene su propia copia de la variable.

Sin embargo, el programa simula una sincronización temporal usando sleep(1) para que el hijo escriba mientras el padre incrementa.

El hijo abre un archivo de texto (valores.txt) y guarda los valores observados de la variable en cada iteración.

El padre, después de finalizar sus incrementos, espera a que el hijo termine usando wait(0).


Padre: Variable incrementada a 10
Padre: Variable incrementada a 20
Padre: Variable incrementada a 30
...
Padre: Variable incrementada a 100
Hijo: Valores registrados en el archivo
Padre: Proceso hijo terminado

Valor: 0
Valor: 0
Valor: 0
...
Valor: 0

Conclusión

Este ejercicio demuestra que, aunque fork() crea un proceso hijo a partir del padre, no comparten el mismo espacio de memoria.
Para lograr una comunicación real entre procesos (IPC), se deberían usar mecanismos como memoria compartida, tuberías (pipes) o semaforos.
En este caso, el uso de un archivo de texto sirve como medio indirecto de comunicación entre ambos procesos.
