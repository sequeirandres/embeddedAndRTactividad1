// Prioridad Estatica en c:
// Prioridades se asignan a las tareas en forma estatica en tiempo de diseño y no cambian durante el tiempo de ejecucion. Este enfoque simplifica las decisiones de programaciòn, pero pueden generar ineficiencias si las prioridades no se eligen cuidadosamente.

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#define NUM_TAREAS 3

// Estructura para almacenar información de tarea
typedef struct {
    int id;
    int prioridad;
    void (*funcion)(); // Puntero a la función de la tarea
} Tarea;

// Prototipos de las funciones de las tareas
void tarea1();
void tarea2();
void tarea3();

// Arreglo de tareas
Tarea tareas[NUM_TAREAS] = {
    {1, 3, tarea1}, // Tarea 1 con prioridad 3
    {2, 2, tarea2}, // Tarea 2 con prioridad 2
    {3, 1, tarea3}  // Tarea 3 con prioridad 1
};

// Función para manejar la señal de temporizador
void timer_handler(int signum) {
    static int contador = 0;
    printf("Tick %d\n", contador++);

    // Verificar si alguna tarea debe ser planificada
    for (int i = 0; i < NUM_TAREAS; i++) {
        if (contador % tareas[i].prioridad == 0) {
            printf("Planificando tarea %d\n", tareas[i].id);
            // Ejecutar la tarea
            tareas[i].funcion();
        }
    }
}

// Funciones de las tareas
void tarea1(void) {
    printf("Ejecutando tarea 1...\n");
    // Lógica de la tarea 1
}

void tarea2(void) {
    printf("Ejecutando tarea 2...\n");
    // Lógica de la tarea 2
}

void tarea3(void) {
    printf("Ejecutando tarea 3...\n");
    // Lógica de la tarea 3
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

