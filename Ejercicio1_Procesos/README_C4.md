Ejercicio 4 - Creación de múltiples procesos hijos con tareas distintas
Descripción

Este programa en C demuestra cómo un proceso padre puede crear varios procesos hijos usando la función fork(), y cómo cada hijo puede realizar una tarea diferente de manera independiente.
En este caso, se crean tres hijos, cada uno con una función específica:

Calcular cuadrados.

Identificar números pares e impares.

Calcular factoriales.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

#define NUM_PROC 3

void hijoHasAlgo(int numero);

int main() {
    int i, pid;
    
    for (i = 1; i <= NUM_PROC; i++) {
        pid = fork();
        
        switch(pid) {
            case -1:
                fprintf(stderr, "Error al crear el proceso\n");
                break;
                
            case 0:
                // Proceso hijo
                hijoHasAlgo(i);
                exit(0); // Importante: el hijo debe terminar después de su tarea
                break;
                
            default:
                // Proceso padre
                printf("Padre: Creando hijo %d con PID: %d\n", i, pid);
                break;
        }
    }
    
    // El padre espera a todos los hijos
    for (i = 0; i < NUM_PROC; i++) {
        int status;
        pid_t child_pid = wait(&status);
        printf("Padre: Hijo con PID %d ha terminado.\n", child_pid);
    }
    
    printf("Padre: Todos los hijos han terminado.\n");
    return 0;
}

void hijoHasAlgo(int numero) {
    int i, MAX = 10;
    
    switch(numero) {
        case 1:
            // Hijo 1: Calcula cuadrados
            printf("=== HIJO %d: CALCULANDO CUADRADOS ===\n", numero);
            for (i = 1; i <= MAX; i++) {
                printf("%d² = %d\t", i, i * i);
                if (i % 3 == 0) printf("\n");
            }
            printf("\n");
            break;
            
        case 2:
            // Hijo 2: Calcula números pares e impares
            printf("=== HIJO %d: NUMEROS PARES E IMPARES ===\n", numero);
            for (i = 1; i <= MAX; i++) {
                if (i % 2 == 0)
                    printf("PAR: %d\t", i);
                else
                    printf("IMPAR: %d\t", i);
                if (i % 4 == 0) printf("\n");
            }
            printf("\n");
            break;
            
        case 3:
            // Hijo 3: Calcula factoriales
            printf("=== HIJO %d: CALCULANDO FACTORIALES ===\n", numero);
            for (i = 1; i <= MAX; i++) {
                long factorial = 1;
                for (int j = 1; j <= i; j++) {
                    factorial *= j;
                }
                printf("%d! = %ld\t", i, factorial);
                if (i % 2 == 0) printf("\n");
            }
            printf("\n");
            break;
            
        default:
            printf("Hijo %d: Tarea por defecto - contando del 1 al %d\n", numero, MAX);
            for (i = 1; i <= MAX; i++) {
                printf("%d\t", i);
            }
            printf("\n");
    }
    
    printf("Hijo %d (PID: %d) ha terminado su tarea.\n", numero, getpid());
}
Explicación

La constante NUM_PROC define la cantidad de procesos hijos a crear (3 en este caso).

Cada vez que se ejecuta fork(), se genera un nuevo proceso hijo.

La función hijoHasAlgo() define una tarea distinta para cada hijo:

Hijo 1: Calcula los cuadrados del 1 al 10.

Hijo 2: Determina si los números del 1 al 10 son pares o impares.

Hijo 3: Calcula los factoriales del 1 al 10.

El padre crea los hijos y luego espera su finalización con wait().

Cada hijo termina su ejecución con exit(0) para no continuar el bucle del padre.

Padre: Creando hijo 1 con PID: 5291
Padre: Creando hijo 2 con PID: 5292
Padre: Creando hijo 3 con PID: 5293

=== HIJO 1: CALCULANDO CUADRADOS ===
1² = 1    2² = 4    3² = 9
4² = 16   5² = 25   6² = 36
7² = 49   8² = 64   9² = 81   10² = 100

=== HIJO 2: NUMEROS PARES E IMPARES ===
IMPAR: 1  PAR: 2  IMPAR: 3  PAR: 4
IMPAR: 5  PAR: 6  IMPAR: 7  PAR: 8
IMPAR: 9  PAR: 10

=== HIJO 3: CALCULANDO FACTORIALES ===
1! = 1    2! = 2
3! = 6    4! = 24
5! = 120  6! = 720
7! = 5040 8! = 40320
9! = 362880 10! = 3628800

Hijo 1 (PID: 5291) ha terminado su tarea.
Hijo 2 (PID: 5292) ha terminado su tarea.
Hijo 3 (PID: 5293) ha terminado su tarea.

Padre: Hijo con PID 5291 ha terminado.
Padre: Hijo con PID 5292 ha terminado.
Padre: Hijo con PID 5293 ha terminado.
Padre: Todos los hijos han terminado.

Conclusión

Este ejercicio demuestra cómo un proceso padre puede crear múltiples procesos hijos y asignarles tareas distintas.
También se observa el uso correcto de fork() dentro de un bucle y la importancia de exit(0) para evitar que los hijos repliquen el comportamiento del padre.
El uso de wait() garantiza que el padre no finalice hasta que todos los hijos hayan completado su ejecución.
