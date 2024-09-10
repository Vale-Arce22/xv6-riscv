#include "types.h"
#include "user.h"

int main() {
printf("Mi PID: %d\n", getpid());
  printf("Mi PID usando getancestor(0): %d\n", getancestor(0));
   printf("PID de mi padre usando getancestor(1): %d\n", getancestor(1));
   printf("PID de mi abuelo usando getancestor(2): %d\n", getancestor(2));
   exit(0);
}
