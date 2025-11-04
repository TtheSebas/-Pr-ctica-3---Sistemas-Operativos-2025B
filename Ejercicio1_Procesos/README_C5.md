Ejercicio 5 - Creación y verificación de un proceso Zombie
Descripción

Este programa en C demuestra cómo se crea un proceso zombie en un sistema operativo tipo UNIX/Linux.
Un proceso zombie aparece cuando un proceso hijo termina su ejecución, pero su proceso padre no ha recogido su estado mediante la función wait().
En este ejemplo, el padre se retrasa intencionalmente para mostrar al hijo en estado zombie.


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

Explicación

La función fork() crea un nuevo proceso hijo.

El proceso hijo imprime su PID y termina inmediatamente con exit(0).

El proceso padre no ejecuta wait() inmediatamente, lo que provoca que el hijo quede en estado ZOMBIE.

Durante 60 segundos, el usuario puede abrir otra terminal y comprobar el estado del hijo con:

ps -elf | grep <PID_del_hijo>


o

ps aux | grep Z


El hijo aparecerá como <defunct> o con una Z en la columna de estado.

Una vez transcurrido el tiempo, el padre ejecuta wait(NULL) y el hijo desaparece del listado de procesos.

=== DEMOSTRACIÓN DE PROCESO ZOMBIE ===
Proceso padre - PID: 3205

Soy el proceso padre (PID: 3205)
Mi hijo tiene PID: 3206
El hijo ha terminado pero no lo he esperado (wait()), por lo que se convierte en ZOMBIE.
Mientras el padre espera 60 segundos, el proceso hijo 3206 será ZOMBIE.

--- INSTRUCCIONES PARA VERIFICAR EL ZOMBIE ---
Abre otra terminal y ejecuta:
ps -elf | grep 3206
ó
ps aux | grep Z
Verás el proceso hijo marcado como <defunct> o Z (zombie)

Padre: Esperando 60 segundos (hijo es zombie durante este tiempo)...
1 segundos...
2 segundos...
...
60 segundos...

Padre: Ahora esperaré al hijo para eliminar el estado zombie...
Padre: Hijo recogido. Ya no hay proceso zombie.


Conclusión

Este programa demuestra de forma práctica cómo un proceso puede quedar en estado zombie cuando su padre no recoge su estado final.
También muestra que, al ejecutar la función wait(), el proceso padre libera correctamente los recursos del hijo, eliminando el zombie del sistema.
Comprender este comportamiento es esencial para evitar fugas de procesos en aplicaciones que crean múltiples hijos.

