#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int ejecutarNuevoProc(char *programa, char *arg_list[]);

int main() {
    printf("=== DEMOSTRACIÓN DEL USO DE EXEC ===\n");
    printf("Proceso padre - PID: %d\n", getpid());
    
    // Ejemplo 1: Listar archivos con ls -l
    printf("\n--- Ejemplo 1: Listado de archivos ---\n");
    char *programa1 = "ls";
    char *arg_list1[] = {"ls", "-l", "-a", NULL};
    int pid1 = ejecutarNuevoProc(programa1, arg_list1);
    wait(0);
    fprintf(stdout, "El proceso hijo con PID %d ha ejecutado 'ls -l -a'\n\n", pid1);
    
    // Ejemplo 2: Mostrar fecha y hora
    printf("--- Ejemplo 2: Fecha y hora ---\n");
    char *programa2 = "date";
    char *arg_list2[] = {"date", NULL};
    int pid2 = ejecutarNuevoProc(programa2, arg_list2);
    wait(0);
    fprintf(stdout, "El proceso hijo con PID %d ha ejecutado 'date'\n\n", pid2);
    
    // Ejemplo 3: Mostrar el directorio actual
    printf("--- Ejemplo 3: Directorio actual ---\n");
    char *programa3 = "pwd";
    char *arg_list3[] = {"pwd", NULL};
    int pid3 = ejecutarNuevoProc(programa3, arg_list3);
    wait(0);
    fprintf(stdout, "El proceso hijo con PID %d ha ejecutado 'pwd'\n\n", pid3);
    
    // Ejemplo 4: Mostrar información del sistema
    printf("--- Ejemplo 4: Información del sistema ---\n");
    char *programa4 = "uname";
    char *arg_list4[] = {"uname", "-a", NULL};
    int pid4 = ejecutarNuevoProc(programa4, arg_list4);
    wait(0);
    fprintf(stdout, "El proceso hijo con PID %d ha ejecutado 'uname -a'\n\n", pid4);
    
    printf("=== Todos los procesos hijos han terminado ===\n");
    return 0;
}

int ejecutarNuevoProc(char *programa, char *arg_list[]) {
    int pid;
    pid = fork();
    
    switch(pid) {
        case -1:
            fprintf(stderr, "No se pudo crear el proceso\n");
            exit(1);
            
        case 0:
            // Proceso hijo
            printf("Hijo (PID: %d) ejecutando: %s\n", getpid(), programa);
            execvp(programa, arg_list);
            // Si llegamos aquí, hubo un error con execvp
            fprintf(stderr, "Error al ejecutar %s\n", programa);
            exit(1);
            
        default:
            // Proceso padre
            return pid;
    }
}

