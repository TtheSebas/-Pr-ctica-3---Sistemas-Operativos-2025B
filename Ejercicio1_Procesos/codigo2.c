#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>

int main()
{
    int pid;
    int variable = 0;
    FILE *archivo;
    
    pid = fork();
    
    switch(pid)
    {
        case -1: // Si pid es -1 quiere decir que ha habido un error
            printf("No se ha podido crear el proceso hijo\n");
            break;
            
        case 0: // Cuando pid es cero quiere decir que es el proceso hijo
            // El hijo abre el archivo para escritura
            archivo = fopen("valores.txt", "w");
            if (archivo == NULL) {
                printf("Error al abrir el archivo\n");
                exit(1);
            }
            
            // El hijo espera y registra los valores
            for(int i = 0; i < 10; i++) {
                // Podríamos usar algún mecanismo de sincronización aquí
                // Para simplificar, asumimos que el padre actualiza la variable
                // y el hijo la lee periódicamente
                sleep(1); // Pequeña pausa para dar tiempo al padre
                fprintf(archivo, "Valor: %d\n", variable);
                fflush(archivo); // Aseguramos que se escriba inmediatamente
            }
            
            fclose(archivo);
            printf("Hijo: Valores registrados en el archivo\n");
            break;
            
        default: // Cuando es distinto de cero es el padre
            // El padre incrementa la variable 10 veces en pasos de 10
            for(int i = 0; i < 10; i++) {
                variable += 10;
                printf("Padre: Variable incrementada a %d\n", variable);
                sleep(1); // Pequeña pausa para sincronización
            }
            
            // La función wait detiene el proceso padre y se queda esperando hasta
            // que termine el hijo
            wait(0);
            printf("Padre: Proceso hijo terminado\n");
            break;
    }
    
    return 0;
}

