Ejercicio 6 - Uso de exec() para ejecutar nuevos procesos
Descripción

Este programa en C demuestra el uso de la función execvp() dentro de procesos creados con fork().
A diferencia de fork(), que crea un nuevo proceso duplicando el actual, la llamada exec() reemplaza completamente el código del proceso hijo por el de otro programa.
El objetivo es mostrar cómo el proceso hijo puede ejecutar comandos del sistema como ls, date, pwd o uname.

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
Explicación

La función fork() crea un proceso hijo.

Dentro del hijo se usa execvp() para ejecutar un programa externo del sistema.

Cuando execvp() se ejecuta correctamente, reemplaza completamente la imagen del proceso hijo, de modo que las líneas siguientes no se ejecutan.

El padre utiliza wait() para esperar a que cada hijo termine antes de continuar.

Programas ejecutados:

ls -l -a → Muestra la lista de archivos en el directorio actual, incluyendo los ocultos.

date → Muestra la fecha y hora actuales.

pwd → Muestra el directorio de trabajo actual.

uname -a → Muestra información del sistema operativo.


=== DEMOSTRACIÓN DEL USO DE EXEC ===
Proceso padre - PID: 5401

--- Ejemplo 1: Listado de archivos ---
Hijo (PID: 5402) ejecutando: ls
total 12
-rw-r--r-- 1 user user  1234 Nov 4  main.c
-rw-r--r-- 1 user user   512 Nov 4  README.md
drwxr-xr-x 2 user user  4096 Nov 4  bin
El proceso hijo con PID 5402 ha ejecutado 'ls -l -a'

--- Ejemplo 2: Fecha y hora ---
Hijo (PID: 5403) ejecutando: date
Mon Nov  4 18:23:12 UTC 2025
El proceso hijo con PID 5403 ha ejecutado 'date'

--- Ejemplo 3: Directorio actual ---
Hijo (PID: 5404) ejecutando: pwd
/home/user/Practica3
El proceso hijo con PID 5404 ha ejecutado 'pwd'

--- Ejemplo 4: Información del sistema ---
Hijo (PID: 5405) ejecutando: uname
Linux workstation 6.1.0-12-amd64 #1 SMP Debian 6.1.52-1 (2023-09-07) x86_64 GNU/Linux
El proceso hijo con PID 5405 ha ejecutado 'uname -a'

=== Todos los procesos hijos han terminado ===


Conclusión

Este programa demuestra el uso de execvp() para ejecutar programas externos desde un proceso hijo.
Permite entender cómo el sistema operativo reemplaza el contexto de un proceso por uno nuevo, conservando el mismo PID.
La combinación de fork() y exec() es el mecanismo fundamental que utilizan los sistemas UNIX/Linux para iniciar nuevos programas.
