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

