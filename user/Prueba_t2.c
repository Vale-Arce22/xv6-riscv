#include "types.h"
#include "user.h"
#include "stat.h"

#define NUM_PROCESOS 20  // Número de procesos a crear

void proceso_prueba(int id) {
    // Obtener la prioridad del proceso actual usando la syscall
    int priority = getpriority(getpid());

    // Muestra el mensaje del proceso actual junto con su prioridad
    printf("Ejecutando proceso %d con pid %d y prioridad %d\n", id, getpid(), priority);
    sleep(5);  // Hace una pausa para visibilidad
}

int main(void) {
    int pid;

    // Creación de procesos
    for (int i = 0; i < NUM_PROCESOS; i++) {
        pid = fork();
        if (pid < 0) {
            printf("Error al crear el proceso %d\n", i);
            exit(1);
        } else if (pid == 0) {
            // Cada proceso hijo ejecuta su función de prueba
            proceso_prueba(i);
            exit(0);  // El proceso hijo termina después de imprimir
        }

        // Asegura que los procesos se ejecuten de uno en uno
        wait(0);  // Espera a que el proceso hijo termine antes de seguir
    }

    // Todos los procesos han terminado
    printf("Todos los procesos han finalizado.\n");
    exit(0);  // Termina el proceso padre
}
