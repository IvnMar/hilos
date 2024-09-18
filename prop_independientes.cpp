#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_ENEMIGOS 4

// Función que simula el movimiento del jugador
void *mover_jugador(void *arg) {
	int avanza=0;
	
    while(avanza < 6){
    	
        	printf("\n Soldado cambia de posicion\n");
         	// Espera 1 segundo
         	avanza ++ ;
         	
         	sleep(1);
	}
}

// Función que simula el disparo de un enemigo
void *disparar_enemigo(void *arg) {
    int id = *((int *)arg),dispa=0;
    while (dispa<5) {
		sleep(2);
        printf("\n Enemigo %d dispara!\n", id);
        dispa ++;
    }
}

int main() {
    pthread_t hilo_jugador;
    pthread_t hilos_enemigos[NUM_ENEMIGOS];
    int ids[NUM_ENEMIGOS];

    srand(time(NULL));  // Inicializar la semilla para los números aleatorios

    // Crear hilo para el jugador
    pthread_create(&hilo_jugador, NULL, mover_jugador, NULL);

    // Crear hilos para los enemigos
    for (int i = 0; i < NUM_ENEMIGOS; i++) {
        ids[i] = i + 1;  // Asignar ID a cada enemigo
        pthread_create(&hilos_enemigos[i], NULL, disparar_enemigo, (void *)&ids[i]);
        
    }

    // Esperar la finalización del hilo del jugador (nunca terminará en este ejemplo)
    pthread_join(hilo_jugador, NULL);

    // Esperar la finalización de los hilos de enemigos (nunca terminarán en este ejemplo)
    for (int i = 0; i < NUM_ENEMIGOS; i++) {
        pthread_join(hilos_enemigos[i], NULL);
    }

    return 0;
}

