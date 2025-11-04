#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    int pid;
    
    printf("Proceso principal - PID: %d, PPID: %d\n", getpid(), getppid());
    
    pid = fork();
    
    switch (pid) {
        case -1:
            printf("Error: No se pudo crear el proceso hijo\n");
            exit(1);
            
        case 0:
            // Proceso hijo
            printf("\n=== PROCESO HIJO ===\n");
            printf("Hijo - PID: %d\n", getpid());
            printf("Hijo - PPID (Padre real): %d\n", getppid());
            
            // Simular trabajo del hijo
            for(int i = 0; i < 3; i++) {
                printf("Hijo trabajando... PPID: %d\n", getppid());
                sleep(1);
            }
            
            printf("Hijo terminando. PPID final: %d\n", getppid());
            break;
            
        default:
            // Proceso padre
            printf("\n=== PROCESO PADRE ===\n");
            printf("Padre - PID: %d\n", getpid());
            printf("Padre - PID del hijo: %d\n", pid);
            
            // El padre espera al hijo
            printf("Padre esperando al hijo...\n");
            wait(0);
            printf("Padre: Hijo ha terminado\n");
    }
    
    return 0;
}

