#include <stdio.h>
#include <stdlib.h>
#include <string.h>//Lineria de strings para usar funciones de comparaciones de cadenas 
#include <pthread.h>////Libreria que permite usar la biblioteca POSIX Threads (pthreads), que proporciona un conjunto de funciones para trabajar con hilos en sistemas UNIX y Linux.

// Estructura para pasar datos al hilo de verificación de contraseña
typedef struct {
    char *contrasena_real;//Apuntador donde va a contener la contraseña real de tipo char
    char *contrasena_ingresada;//Apuntador que va a contener la contraseña ingresada
    int *verificado;//Apuntador donde contenga la verificación  si es 1 esta correctamente si es o no esta bien 
} DatosContrasena;//  Nombre de la estructrura DatosContraseña

// Función para verificar la contraseña
void *verificar_contrasena(void *arg) {  // Funcion que no regresa nada,  el nombre de la función es Verifica contraseña que a su ves esta función es de tipo apuntador 
    DatosContrasena *datos = (DatosContrasena *) arg;/* Convertimos el argumento genérico 'arg' (puntero de tipo void*) un puntero de tipo DatosContrasena*.
 De esta forma, podemos acceder a los campos de la estructura DatosContrasena 
 (como contrasena_real, contrasena_ingresada, y verificado)
a través del puntero 'datos'.*/

    // Verificación de contraseña
    if (strcmp(datos->contrasena_real, datos->contrasena_ingresada) == 0) {/*La función strcmp es para comparar cadenas, y ver si realmente coinciden las 2 contraseñas
	 Si da 0 en la comáración de las cadenas es porque son coincidentes si da otro valor es que es inccorecto */
        *datos->verificado = 1; // Contraseña correcta ,Se le asigna el valor de 1 a la verificación ya que si son iguales. 
        printf("Contraseña correcta.\n");
    } else {
        *datos->verificado = 0; // Contraseña incorrecta
        printf("Contraseña incorrecta.\n");
    }

    pthread_exit(NULL);//Finaliza un hilo de forma controlada, liberando sus recursos.
}

int main() {
    char contrasena_real[] = "7754"; // Contraseña correcta almacenada
    char contrasena_ingresada[20];
    int verificado = 0;

    // Instancia de la estructura DatosContrasena
    DatosContrasena datos; //Estas reservando memoria para el tipo de variable de estrcutura
    datos.contrasena_real = contrasena_real;
    datos.contrasena_ingresada = contrasena_ingresada;
    datos.verificado = &verificado;  //Estas guardando la dirreción de memoria en verificado 

    // Solicitar la contraseña al usuario
    printf("Ingrese su contraseña: ");
    scanf("%s", contrasena_ingresada);

    // Crear el hilo de verificación de contraseña
    pthread_t hilo_verificacion;
    pthread_create(&hilo_verificacion, NULL, verificar_contrasena, (void *)&datos); /*Se pone como primer parametro la dirección del hilo para la verificación
    como segundo parametro se pone el NULL porque se esta estableciendo la configuración por defecto del hilo 
    Como tercer parametro se pone el puntero a la función que se va a ejecutar y por ultimo se pone los datos 
	que se van a pasar en el hilo se pone void porque cualquier tipo de dato se puede convertir en un tipo de void  */

    // Esperar a que el hilo de verificación termine
    pthread_join(hilo_verificacion, NULL);/*pthread_join garantiza que el hilo principal espere a que un hilo secundario termine 
	antes de continuar con la ejecución.
      El NULL en el segundo argumento significa que no te interesa recoger el valor de retorno del hilo.*/

    // Informar el resultado de la verificación
    if (verificado) {
        printf("Acceso concedido.\n");
    } else {
        printf("Acceso denegado.\n");
    }

    return 0;
}

