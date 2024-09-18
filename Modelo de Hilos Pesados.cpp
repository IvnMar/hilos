#include <stdio.h>
#include <pthread.h>

// Función que simula la reserva de una habitación
void *reservar_habitacion(void *arg) {
    int cliente_id = *((int *) arg);  // Obtener el ID del cliente

    // Simulamos que cada cliente está reservando una habitación
    printf("Cliente %d está intentando reservar una habitación...\n", cliente_id);

    // Simulación de un proceso pesado (reservar habitación)
    printf("Cliente %d ha reservado una habitación con éxito.\n", cliente_id);

    pthread_exit(NULL);  // Termina el hilo después de realizar la reserva
}

int main() {
    pthread_t clientes[3];  // Array para almacenar los identificadores de los hilos (clientes)
    int ids[] = {1, 2, 3};  // IDs de los clientes

    // Crear hilos para simular el proceso de reserva de cada cliente
    for (int i = 0; i < 3; i++) {
        pthread_create(&clientes[i], NULL, reservar_habitacion, (void *) &ids[i]);  // Crear un nuevo hilo para cada cliente
    }

    // Esperar a que todos los hilos (clientes) terminen de hacer sus reservas
    for (int i = 0; i < 3; i++) {
        pthread_join(clientes[i], NULL);  // Esperar a que cada hilo termine su ejecución
    }

    printf("Todas las reservas han sido procesadas.\n");

    return 0;
}
