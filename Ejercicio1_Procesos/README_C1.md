# Ejercicio 1 - Uso básico de fork()

## Descripción
Este programa demuestra el uso de la función `fork()` en C para crear un proceso hijo a partir de un proceso padre.  
Cada proceso (padre e hijo) imprime su propio **PID** (identificador de proceso) y, en el caso del hijo, también el **PPID** (identificador del proceso padre).

---

## Código fuente
```c
#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Ejemplo de fork.\n");
  printf("Inicio del proceso padre. PID=%d\n", getpid());
  if (fork() == 0) {
    /* Proceso hijo */
    printf("Inicio proceso hijo. PID=%d, PPID=%d\n", getpid(), getppid());
    sleep(1);
  } else {
    /* Proceso padre */
    printf("Continuación del padre. PID=%d\n", getpid());
    sleep(1);
  }
  printf("Fin del proceso %d\n", getpid());
  return 0;
}

Explicación

fork() crea un nuevo proceso duplicando el proceso actual.

Si el valor de retorno es 0, se está ejecutando el proceso hijo.

Si el valor es mayor que 0, se está ejecutando el proceso padre.

Cada proceso imprime su propio PID usando getpid() y, en el caso del hijo, el PID del padre con getppid().

La función sleep(1) se usa para hacer una pequeña pausa, permitiendo observar el orden de ejecución.

Ejemplo de fork.
Inicio del proceso padre. PID=4608
Continuación del padre. PID=4608
Inicio proceso hijo. PID=4609, PPID=4608
Fin del proceso 4608
Fin del proceso 4609

Conclusión

Este ejemplo muestra cómo fork() permite la ejecución concurrente de dos procesos.
Cada proceso tiene su propio espacio de memoria y ejecuta el código de forma independiente, lo cual es fundamental en la administración de procesos de los sistemas operativos tipo UNIX/Linux.


