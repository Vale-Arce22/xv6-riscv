#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "syscall.h"

extern int mprotect(void *addr, int len);
extern int munprotect(void *addr, int len);

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64 sys_mprotect(void) {
    uint64 addr = myproc()->trapframe->a0;  // Primer argumento (dirección)
    int len = myproc()->trapframe->a1;      // Segundo argumento (longitud)

    // Validar que addr y len tengan valores aceptables
    if (addr == 0 || len <= 0) {
        return -1;  // Error en los parámetros
    }

    // Llamar a mprotect con addr convertido a puntero y len
    return mprotect((void *)addr, len);
}

uint64 sys_munprotect(void) {
    uint64 addr = myproc()->trapframe->a0;  // Primer argumento (dirección)
    int len = myproc()->trapframe->a1;      // Segundo argumento (longitud)

    // Validar que addr y len tengan valores aceptables
    if (addr == 0 || len <= 0) {
        return -1;  // Error en los parámetros
    }

    // Llamar a munprotect con addr convertido a puntero y len
    return munprotect((void *)addr, len);
}