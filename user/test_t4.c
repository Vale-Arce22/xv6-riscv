#include "user/user.h"
#include "fcntl.h"
#include "user/user.h"

int main() {
    int fd;

    // Crear archivo de prueba
    fd = open("testfile.txt", O_CREATE | O_RDWR);
    if(fd < 0) {
        printf("Error creando el archivo\n");
        exit(1);
    }
    close(fd);

    // Cambiar permisos de archivo a solo lectura
    if(chmod("testfile.txt", 1) < 0) {
        printf("Error cambiando permisos\n");
        exit(1);
    }

    // Intentar escribir en el archivo (debería fallar por permisos)
    fd = open("testfile.txt", O_RDWR);
    if(fd >= 0) {
        printf("Se pudo abrir el archivo para escritura, pero no debería\n");
        exit(1);
    }

    // Cambiar permisos a lectura/escritura
    if(chmod("testfile.txt", 3) < 0) {
        printf("Error cambiando permisos\n");
        exit(1);
    }

    // Intentar escribir después de cambiar permisos (debería funcionar)
    fd = open("testfile.txt", O_RDWR);
    if(fd < 0) {
        printf("Error abriendo archivo para escritura\n");
        exit(1);
    }
    write(fd, "Hello, world!", 14);
    close(fd);

    printf("Pruebas de permisos exitosas\n");
    exit(0);
}
