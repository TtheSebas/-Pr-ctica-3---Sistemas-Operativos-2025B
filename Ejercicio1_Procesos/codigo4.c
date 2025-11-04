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
                if (i % 3 == 0) printf("\n"); // Salto de línea cada 3 números
            }
            printf("\n");
            break;
            
        case 2:
            // Hijo 2: Calcula números pares e impares
            printf("=== HIJO %d: NUMEROS PARES E IMPARES ===\n", numero);
            for (i = 1; i <= MAX; i++) {
                if (i % 2 == 0) {
                    printf("PAR: %d\t", i);
                } else {
                    printf("IMPAR: %d\t", i);
                }
                if (i % 4 == 0) printf("\n"); // Salto de línea cada 4 números
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
                if (i % 2 == 0) printf("\n"); // Salto de línea cada 2 números
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

