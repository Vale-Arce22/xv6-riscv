#include "types.h"
#include "user.h"

int main() {
  printf("Hola mundo!\n");

  int pid = getpid();
  printf("El ID del proceso es: %d\n", pid);

  int ppid = getppid();
  printf("El ID del proceso padre es: %d\n", ppid);

  exit(0);
}
