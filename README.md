Descripción general del proyecto

El presente proyecto, titulado “Creación y gestión de procesos en sistemas operativos”, forma parte del Laboratorio de Sistemas Operativos y tiene como objetivo principal comprender el funcionamiento interno de los procesos dentro de sistemas tipo UNIX/Linux.

A lo largo de la práctica se implementan diversos programas en lenguaje C que emplean las funciones fundamentales del manejo de procesos:

fork(), para la creación de procesos hijos.

exec(), para la sustitución del código de un proceso por un nuevo programa.

system(), para ejecutar comandos de la shell desde un proceso en C.

Cada ejercicio aborda un escenario diferente del control de procesos:

Creación de un proceso hijo y visualización de los identificadores PID y PPID.

Comunicación indirecta entre procesos mediante un archivo de texto.

Ejecución sin espera, observando la creación de procesos huérfanos.

Generación de múltiples hijos con tareas independientes.

Simulación de procesos zombie, comprendiendo su aparición y eliminación.

Ejecución de programas externos con exec().

Uso de system() para la ejecución de comandos del sistema.

Mediante la ejecución y análisis de estos programas, el estudiante logra identificar la estructura jerárquica de los procesos, su sincronización, y la interacción entre procesos padre e hijo.
El proyecto refuerza conceptos teóricos sobre la administración de procesos, el manejo de la memoria y la planificación que realiza el sistema operativo.

En conjunto, esta práctica consolida el entendimiento de cómo el sistema operativo gestiona la creación, ejecución, comunicación y finalización de procesos, proporcionando una base sólida para el estudio de temas avanzados como concurrencia, hilos y comunicación entre procesos (IPC).
