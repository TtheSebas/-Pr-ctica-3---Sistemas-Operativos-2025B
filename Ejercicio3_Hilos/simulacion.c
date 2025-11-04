#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("=== USANDO system() PARA LISTAR PROCESOS ===\n");
    printf("Hola! Soy el proceso padre y mi PID es: %d\n", getpid());
    
    // Crear un proceso hijo
    printf("\n--- Creando proceso hijo ---\n");
    int pid = fork();
    
    if (pid == 0) {
        // Este es el proceso hijo
        printf("\nSOY EL HIJO:\n");
        printf("   Mi PID es: %d\n", getpid());
        printf("   Mi padre es: %d\n", getppid());
        printf("   Voy a listar los procesos del sistema...\n\n");
        
        // Usando system() para ejecutar comandos
        printf("=== LISTADO DE PROCESOS CON system() ===\n");
        
        printf("\n1. Listado básico de procesos (ps):\n");
        printf("------------------------------------\n");
        system("ps");
        
        printf("\n2. Listado completo de procesos (ps aux):\n");
        printf("-----------------------------------------\n");
        system("ps aux");
        
        printf("\n3. Procesos del usuario actual:\n");
        printf("------------------------------\n");
        system("ps -u $USER");
        
        printf("\n4. Árbol de procesos (pstree):\n");
        printf("-----------------------------\n");
        system("pstree");
        
        printf("\nEl hijo ha terminado de listar los procesos!\n");
        exit(0);  // El hijo termina aquí
        
    } else if (pid > 0) {
        // Este es el proceso padre
        printf("\nSOY EL PADRE:\n");
        printf("   Mi PID es: %d\n", getpid());
        printf("   Mi hijo tiene PID: %d\n", pid);
        printf("   Esperando a que mi hijo termine...\n");
        
        wait(NULL);  // Esperar a que el hijo termine
        
        printf("\nEl hijo ha terminado su trabajo!\n");
        printf("   Volvemos al proceso padre...\n");
        
    } else {
        printf("Error: No se pudo crear el proceso hijo\n");
        return 1;
    }
    
    // El padre puede seguir haciendo cosas
    printf("\n--- El padre sigue ejecutándose ---\n");
    printf("Mostrando información del sistema:\n");
    system("uname -a");
    
    printf("\n=== PROGRAMA TERMINADO ===\n");
    return 0;
}

