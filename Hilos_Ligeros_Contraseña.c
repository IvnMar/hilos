#include <stdio.h>
#include <stdlib.h>
#include <string.h>//Lineria de strings para usar funciones de comparaciones de cadenas 
#include <pthread.h>////Libreria que permite usar la biblioteca POSIX Threads (pthreads), que proporciona un conjunto de funciones para trabajar con hilos en sistemas UNIX y Linux.

// Estructura para pasar datos al hilo de verificaci�n de contrase�a
typedef struct {
    char *contrasena_real;//Apuntador donde va a contener la contrase�a real de tipo char
    char *contrasena_ingresada;//Apuntador que va a contener la contrase�a ingresada
    int *verificado;//Apuntador donde contenga la verificaci�n  si es 1 esta correctamente si es o no esta bien 
} DatosContrasena;//  Nombre de la estructrura DatosContrase�a

// Funci�n para verificar la contrase�a
void *verificar_contrasena(void *arg) {  // Funcion que no regresa nada,  el nombre de la funci�n es Verifica contrase�a que a su ves esta funci�n es de tipo apuntador 
    DatosContrasena *datos = (DatosContrasena *) arg;/* Convertimos el argumento gen�rico 'arg' (puntero de tipo void*) un puntero de tipo DatosContrasena*.
 De esta forma, podemos acceder a los campos de la estructura DatosContrasena 
 (como contrasena_real, contrasena_ingresada, y verificado)
a trav�s del puntero 'datos'.*/

    // Verificaci�n de contrase�a
    if (strcmp(datos->contrasena_real, datos->contrasena_ingresada) == 0) {/*La funci�n strcmp es para comparar cadenas, y ver si realmente coinciden las 2 contrase�as
	 Si da 0 en la com�raci�n de las cadenas es porque son coincidentes si da otro valor es que es inccorecto */
        *datos->verificado = 1; // Contrase�a correcta ,Se le asigna el valor de 1 a la verificaci�n ya que si son iguales. 
        printf("Contrase�a correcta.\n");
    } else {
        *datos->verificado = 0; // Contrase�a incorrecta
        printf("Contrase�a incorrecta.\n");
    }

    pthread_exit(NULL);//Finaliza un hilo de forma controlada, liberando sus recursos.
}

int main() {
    char contrasena_real[] = "7754"; // Contrase�a correcta almacenada
    char contrasena_ingresada[20];
    int verificado = 0;

    // Instancia de la estructura DatosContrasena
    DatosContrasena datos; //Estas reservando memoria para el tipo de variable de estrcutura
    datos.contrasena_real = contrasena_real;
    datos.contrasena_ingresada = contrasena_ingresada;
    datos.verificado = &verificado;  //Estas guardando la dirreci�n de memoria en verificado 

    // Solicitar la contrase�a al usuario
    printf("Ingrese su contrase�a: ");
    scanf("%s", contrasena_ingresada);

    // Crear el hilo de verificaci�n de contrase�a
    pthread_t hilo_verificacion;
    pthread_create(&hilo_verificacion, NULL, verificar_contrasena, (void *)&datos); /*Se pone como primer parametro la direcci�n del hilo para la verificaci�n
    como segundo parametro se pone el NULL porque se esta estableciendo la configuraci�n por defecto del hilo 
    Como tercer parametro se pone el puntero a la funci�n que se va a ejecutar y por ultimo se pone los datos 
	que se van a pasar en el hilo se pone void porque cualquier tipo de dato se puede convertir en un tipo de void  */

    // Esperar a que el hilo de verificaci�n termine
    pthread_join(hilo_verificacion, NULL);/*pthread_join garantiza que el hilo principal espere a que un hilo secundario termine 
	antes de continuar con la ejecuci�n.
      El NULL en el segundo argumento significa que no te interesa recoger el valor de retorno del hilo.*/

    // Informar el resultado de la verificaci�n
    if (verificado) {
        printf("Acceso concedido.\n");
    } else {
        printf("Acceso denegado.\n");
    }

    return 0;
}

