#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    int pid;
    int parent_pid = getpid();

    // Crear el primer proceso hijo
    pid = fork();
    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    if (pid == 0) {
        // Este es el primer proceso hijo
        printf("First child: PID %d, Parent PID %d\n", getpid(), parent_pid);

        // Crear el segundo proceso hijo (hijo del primer hijo)
        pid = fork();
        if (pid < 0) {
            printf("Fork failed\n");
            exit(1);
        }

        if (pid == 0) {
            // Este es el segundo proceso hijo
            int second_child_pid = getpid();
            int ancestor_pid = getancestor(second_child_pid);  // Pasar el PID actual como argumento
            printf("Second child: PID %d, My ancestor's PID is %d\n", second_child_pid, ancestor_pid);
            exit(0);
        } else {
            // Esperar a que el segundo proceso hijo termine
            int status;
            wait(&status);
            exit(0);
        }
    } else {
        // Proceso padre
        // Esperar a que el primer proceso hijo termine
        int status;
        wait(&status);
    }

    exit(0);
}
