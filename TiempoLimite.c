//Tiempo Limite Primero (EDF)
// La planificación de tiempo límite, también conocida como Earliest Deadline First (EDF), es un algoritmo de planificación utilizado en sistemas de tiempo real. En EDF, las tareas se programan según su plazo de vencimiento más cercano; es decir, la tarea con el plazo de vencimiento más próximo se ejecuta primero.

//En un sistema EDF, cada tarea tiene un plazo de vencimiento asociado, que es el momento límite en el que debe completarse. Durante la ejecución del sistema, se planifican las tareas de manera que se cumplan todos sus plazos de vencimiento

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#define NUM_TAREAS 3

// Estructura para almacenar información de tarea
typedef struct {
    int id;
    int periodo; // Periodo en unidades de tiempo
    int plazo;   // Plazo en unidades de tiempo
    int tiempo_ejecucion; // Tiempo de ejecución en unidades de tiempo
} Tarea;

// Arreglo de tareas
Tarea tareas[NUM_TAREAS] = {
    {1, 5, 5, 1},   // Tarea 1 con periodo de 5 unidades de tiempo, plazo de 5 unidades y tiempo de ejecución de 1 unidad
    {2, 10, 10, 2}, // Tarea 2 con periodo de 10 unidades de tiempo, plazo de 10 unidades y tiempo de ejecución de 2 unidades
    {3, 20, 20, 4}  // Tarea 3 con periodo de 20 unidades de tiempo, plazo de 20 unidades y tiempo de ejecución de 4 unidades
};

// Función para manejar la señal de temporizador
void timer_handler(int signum) {
    static int contador = 0;
    printf("Tick %d\n", contador++);

    // Verificar si alguna tarea debe ser planificada
    for (int i = 0; i < NUM_TAREAS; i++) {
        if (contador % tareas[i].periodo == 0) {
            printf("Planificando tarea %d\n", tareas[i].id);
            // Aquí se ejecutaría la lógica de la tarea
        }
    }
}

// Función para configurar el temporizador
void configurar_temporizador() {
    struct itimerval timer;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 100000; // Intervalo de 100 ms
    timer.it_value = timer.it_interval;
    setitimer(ITIMER_REAL, &timer, NULL);
}

int main() {
    // Configurar el manejador de señal para SIGALRM
    signal(SIGALRM, timer_handler);
    
    // Configurar el temporizador
    configurar_temporizador();

    // Ejecutar el programa de manera infinita
    while (1) {
        // Aquí podrían realizarse otras tareas en paralelo con la planificación de las tareas periódicas
        usleep(1000); // Pequeña pausa para no ocupar demasiado tiempo de CPU
    }

    return 0;
}

