// Importaci�n de librer�as
#include <stdio.h>      // Librer�a de entrada y salida est�ndar
#include <pthread.h>    // Librer�a POSIX para manejo de hilos

// Funci�n que se ejecutar� en el primer hilo (cuenta de 1 a 5)
void* funcionHilo1(void* arg) {
    for (int i = 1; i <= 5; ++i) {       // Ciclo que cuenta del 1 al 5
        printf("Hilo 1 (Conteo ascendente): %d\n", i);  // Imprime el n�mero actual
    }
    return NULL; // Finaliza el hilo retornando NULL
}

// Funci�n que se ejecutar� en el segundo hilo (cuenta de 5 a 1)
void* funcionHilo2(void* arg) {
    for (int i = 5; i >= 1; --i) {       // Ciclo que cuenta del 5 al 1
        printf("Hilo 2 (Conteo descendente): %d\n", i); // Imprime el n�mero actual
    }
    return NULL; // Finaliza el hilo retornando NULL
}

// Funci�n que se ejecutar� en el tercer hilo (imprime n�meros pares del 2 al 10)
void* funcionHilo3(void* arg) {
    for (int i = 2; i <= 10; i += 2) {   // Ciclo que imprime los n�meros pares
        printf("Hilo 3 (Numeros pares): %d\n", i);  // Imprime el n�mero par actual
    }
    return NULL; // Finaliza el hilo retornando NULL
}

int main() {
    // Declaraci�n de identificadores de hilos
    pthread_t hilo1, hilo2, hilo3; // Declaramos 3 hilos

    // Creaci�n de los hilos
    pthread_create(&hilo1, NULL, funcionHilo1, NULL);  // Crea el hilo1 que ejecuta funcionHilo1
    pthread_create(&hilo2, NULL, funcionHilo2, NULL);  // Crea el hilo2 que ejecuta funcionHilo2
    pthread_create(&hilo3, NULL, funcionHilo3, NULL);  // Crea el hilo3 que ejecuta funcionHilo3

    // Esperar a que los hilos terminen su ejecuci�n
    pthread_join(hilo1, NULL);  // Espera a que hilo1 termine su ejecuci�n
    pthread_join(hilo2, NULL);  // Espera a que hilo2 termine su ejecuci�n
    pthread_join(hilo3, NULL);  // Espera a que hilo3 termine su ejecuci�n

    printf("\nPrograma principal: Todos los hilos han finalizado\n");  // Mensaje final
    return 0; // Fin del programa
}

