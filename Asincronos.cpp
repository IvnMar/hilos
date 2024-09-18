#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Estructura para pasar multiples argumentos a la funcion del hilo
typedef struct {
    int thread_id;
    char* message;
    int repeat_count;
} ThreadArgs;

// Funcion que se ejecutara en el primer hilo
void* threadFunction1(void* args) {
    ThreadArgs* thread_args = (ThreadArgs*)args;
    for (int i = 0; i < thread_args->repeat_count; i++) {
        printf("Hilo %d: %s (Iteracion %d)\n", thread_args->thread_id, thread_args->message, i + 1);
    }
    pthread_exit(NULL); // Terminar el hilo
}

// Funcion que se ejecutara en el segundo hilo
void* threadFunction2(void* args) {
    ThreadArgs* thread_args = (ThreadArgs*)args;
    for (int i = 0; i < thread_args->repeat_count; i++) {
        printf("Hilo %d: %s (Iteracion %d)\n", thread_args->thread_id, thread_args->message, i + 1);
    }
    pthread_exit(NULL); // Terminar el hilo
}

// Funcion que se ejecutara en el tercer hilo
void* threadFunction3(void* args) {
    ThreadArgs* thread_args = (ThreadArgs*)args;
    for (int i = 0; i < thread_args->repeat_count; i++) {
        printf("Hilo %d: %s (Iteracion %d)\n", thread_args->thread_id, thread_args->message, i + 1);
    }
    pthread_exit(NULL); // Terminar el hilo
}

int main() {
    // Definir la estructura de argumentos para cada hilo
    ThreadArgs args1 = {1, "Hola mundo desde el primer hilo!", 3}; // 3 iteraciones
    ThreadArgs args2 = {2, "Hola mundo desde el segundo hilo!", 4}; // 4 iteraciones
    ThreadArgs args3 = {3, "Hola mundo desde el tercer hilo!", 2}; // 2 iteraciones

    // Declarar las variables de hilo
    pthread_t thread1, thread2, thread3;

    // Crear los hilos y pasar las funciones junto con los argumentos
    if (pthread_create(&thread1, NULL, threadFunction1, (void*)&args1) != 0) {
        perror("Error al crear el primer hilo"); // Imprimir error si falla la creacion del hilo
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread2, NULL, threadFunction2, (void*)&args2) != 0) {
        perror("Error al crear el segundo hilo"); // Imprimir error si falla la creacion del hilo
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread3, NULL, threadFunction3, (void*)&args3) != 0) {
        perror("Error al crear el tercer hilo"); // Imprimir error si falla la creacion del hilo
        exit(EXIT_FAILURE);
    }

    // Esperar a que los hilos terminen su ejecucion
    if (pthread_join(thread1, NULL) != 0) {
        perror("Error al unir el primer hilo"); // Imprimir error si falla la espera del hilo
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread2, NULL) != 0) {
        perror("Error al unir el segundo hilo"); // Imprimir error si falla la espera del hilo
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread3, NULL) != 0) {
        perror("Error al unir el tercer hilo"); // Imprimir error si falla la espera del hilo
        exit(EXIT_FAILURE);
    }

    // Imprimir mensaje del hilo principal
    printf("Hilo principal: Todos los hilos han terminado su ejecucion.\n");

    return 0;
}

