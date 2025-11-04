#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid;
    
    printf("=== DEMOSTRACIÓN DE PROCESO ZOMBIE ===\n");
    printf("Proceso padre - PID: %d\n", getpid());
    
    pid = fork();
    
    if (pid > 0) {
        // Proceso padre
        printf("\nSoy el proceso padre (PID: %d)\n", getpid());
        printf("Mi hijo tiene PID: %d\n", pid);
        printf("El hijo ha terminado pero no lo he esperado (wait()), por lo que se convierte en ZOMBIE.\n");
        printf("Mientras el padre espera 60 segundos, el proceso hijo %d será ZOMBIE.\n", pid);
        
        // Instrucciones para verificar el proceso zombie
        printf("\n--- INSTRUCCIONES PARA VERIFICAR EL ZOMBIE ---\n");
        printf("Abre otra terminal y ejecuta:\n");
        printf("ps -elf | grep %d\n", pid);
        printf("ó\n");
        printf("ps aux | grep Z\n");
        printf("Verás el proceso hijo marcado como <defunct> o Z (zombie)\n\n");
        
        // El padre espera 60 segundos sin recoger al hijo
        printf("Padre: Esperando 60 segundos (hijo es zombie durante este tiempo)...\n");
        for(int i = 1; i <= 60; i++) {
            printf("%d segundos...\n", i);
            sleep(1);
        }
        
        printf("\nPadre: Ahora esperaré al hijo para eliminar el estado zombie...\n");
        wait(NULL);
        printf("Padre: Hijo recogido. Ya no hay proceso zombie.\n");
        
    } else if (pid == 0) {
        // Proceso hijo
        printf("Soy el proceso hijo (PID: %d), mi padre es: %d\n", getpid(), getppid());
        printf("Hijo: Terminando inmediatamente...\n");
        exit(0);
    } else {
        // Error
        fprintf(stderr, "Error al crear el proceso hijo\n");
        exit(1);
    }
    
    return 0;
}

