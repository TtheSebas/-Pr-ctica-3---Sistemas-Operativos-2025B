Ejercicio 3 - Creación de proceso hijo y verificación del PPID
Descripción

Este programa en C demuestra cómo crear un proceso hijo utilizando fork() y observar la relación entre el PID (identificador del proceso) y el PPID (identificador del proceso padre).
El objetivo es visualizar cómo se comporta el proceso hijo y cómo cambia su PPID si el proceso padre termina antes, simulando un caso de proceso huérfano.

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

Explicación

La función fork() crea un proceso hijo duplicando el proceso padre.

El hijo obtiene su propio PID (con getpid()) y el PPID de su padre (con getppid()).

El padre imprime su propio PID y el del hijo, y luego espera su finalización mediante wait(0).

Si se modifica el código y el padre no ejecuta wait() (termina antes), el hijo se vuelve huérfano y su PPID pasa a ser el del proceso init/systemd (PID 1), que lo adopta.

Proceso principal - PID: 5300, PPID: 420
=== PROCESO PADRE ===
Padre - PID: 5300
Padre - PID del hijo: 5301
Padre esperando al hijo...

=== PROCESO HIJO ===
Hijo - PID: 5301
Hijo - PPID (Padre real): 5300
Hijo trabajando... PPID: 5300
Hijo trabajando... PPID: 5300
Hijo trabajando... PPID: 5300
Hijo terminando. PPID final: 5300

Padre: Hijo ha terminado

Conclusión

Este ejemplo permite comprender la relación entre los procesos padre e hijo en un sistema operativo tipo UNIX/Linux.
También muestra cómo los procesos huérfanos son adoptados por el proceso init/systemd, garantizando que el sistema mantenga un control jerárquico adecuado sobre todos los procesos en ejecución.

