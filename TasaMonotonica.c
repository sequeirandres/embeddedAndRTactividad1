// Ejemplo de Tasa Monotinica (RMS) :
//La planificación de activación por tasa monótona (Rate-Monotonic Scheduling, RMS) es un algoritmo de planificación de tiempo real en sistemas embebidos. En este algoritmo, las tareas se programan de acuerdo con su frecuencia de ejecución relativa, es decir, las tareas con tasas más altas se ejecutan antes que las tareas con tasas más bajas


#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#define NUM_TAREAS 3

// Estructura para almacenar información de tarea
typedef struct {
    int id;
    int periodo; // Periodo en unidades de tiempo
    int tiempo_ejecucion; // Tiempo de ejecución en unidades de tiempo
} Tarea;

// Arreglo de tareas
Tarea tareas[NUM_TAREAS] = {
    {1, 5, 1},    // Tarea 1 con periodo de 5 unidades de tiempo y tiempo de ejecución de 1 unidad
    {2, 10, 2},   // Tarea 2 con periodo de 10 unidades de tiempo y tiempo de ejecución de 2 unidades
    {3, 20, 4}    // Tarea 3 con periodo de 20 unidades de tiempo y tiempo de ejecución de 4 unidades
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


