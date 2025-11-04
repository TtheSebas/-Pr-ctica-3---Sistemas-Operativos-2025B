Ejercicio 7 - Uso de system() para ejecutar comandos del sistema
Descripción

Este programa en C demuestra cómo utilizar la función system() para ejecutar comandos del sistema operativo desde un proceso hijo creado con fork().
La función system() ejecuta un comando en una nueva instancia de la shell, permitiendo al programa interactuar con el sistema operativo de forma sencilla.
En este caso, el proceso hijo lista los procesos activos del sistema usando varios comandos (ps, ps aux, ps -u, pstree), mientras que el proceso padre espera su finalización.


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
Explicación

fork() crea un proceso hijo que hereda el contexto del padre.

En el proceso hijo, se usa system() para ejecutar comandos directamente en la shell.

El hijo ejecuta los siguientes comandos:

ps → Lista los procesos activos.

ps aux → Muestra un listado completo con todos los usuarios.

ps -u $USER → Filtra los procesos del usuario actual.

pstree → Muestra los procesos en forma de árbol jerárquico.

Mientras tanto, el proceso padre espera al hijo con wait(NULL) y, una vez que termina, ejecuta uname -a para mostrar información del sistema operativo.

=== USANDO system() PARA LISTAR PROCESOS ===
Hola! Soy el proceso padre y mi PID es: 4100

--- Creando proceso hijo ---

SOY EL HIJO:
   Mi PID es: 4101
   Mi padre es: 4100
   Voy a listar los procesos del sistema...

=== LISTADO DE PROCESOS CON system() ===

1. Listado básico de procesos (ps):
------------------------------------
    PID TTY          TIME CMD
   4100 pts/0    00:00:00 main
   4101 pts/0    00:00:00 ps

2. Listado completo de procesos (ps aux):
-----------------------------------------
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root         1  0.0  0.1  16900  1300 ?        Ss   09:00   0:00 init
user      4100  0.0  0.0   5000   400 pts/0    S+   09:05   0:00 ./main
user      4101  0.0  0.0   6000   700 pts/0    R+   09:05   0:00 ps aux

3. Procesos del usuario actual:
------------------------------
... (salida similar filtrada por usuario)

4. Árbol de procesos (pstree):
-----------------------------
init─┬─bash───main───ps
     └─systemd───(otros procesos)

El hijo ha terminado de listar los procesos!

SOY EL PADRE:
   Mi PID es: 4100
   Mi hijo tiene PID: 4101
   Esperando a que mi hijo termine...

El hijo ha terminado su trabajo!
   Volvemos al proceso padre...

--- El padre sigue ejecutándose ---
Mostrando información del sistema:
Linux workstation 6.1.0-12-amd64 #1 SMP Debian 6.1.52-1 x86_64 GNU/Linux

=== PROGRAMA TERMINADO ===


Conclusión

Este ejercicio demuestra el uso de la función system() para ejecutar comandos de la shell desde un programa en C.
Se observa cómo los procesos hijo y padre pueden realizar tareas diferentes, y cómo system() permite interactuar directamente con el sistema operativo sin necesidad de usar exec().
El ejemplo también refuerza el control de procesos y la sincronización entre padre e hijo mediante fork() y wait().

