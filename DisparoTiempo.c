// Disparo de tiempo : 
// Las tareas se ejecutan en intervalos de tiempos determinadso o momentos especificos.
// Este enfoque proporciona un comportamiento determinista, lo cual lo hace adecuado para
// sistemas de tiempo real donde se deben cumplir resticciones de tiempo.

/*
#include <stdio.h>
#include <unistd.h>

int main() {
    int tiempo = 5; // Tiempo en segundos

    printf("El programa se ejecutará durante %d segundos.\n", tiempo);

    // Espera durante el tiempo especificado
    sleep(tiempo);

    printf("¡Tiempo terminado! El programa ha terminado de ejecutarse.\n");

    return 0;
}

*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Función que se ejecuta cuando el temporizador finaliza
void temporizador_handler(int signum) {
    printf("¡Tiempo terminado! El temporizador ha finalizado.\n");
}

int main() {
    int tiempo = 5; // Tiempo en segundos

    // Establecer el manejador de señal para SIGALRM (temporizador)
    signal(SIGALRM, temporizador_handler);

    printf("El temporizador se ha iniciado para %d segundos.\n", tiempo);

    // Configurar el temporizador
    alarm(tiempo);

    // Esperar a que el temporizador finalice
    pause();

    printf("El programa ha finalizado.\n");

    return 0;
}


