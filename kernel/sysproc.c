#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

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
sys_getppid(void)
{
    struct proc *p = myproc();
    if (p->parent)
        return p->parent->pid;
    else
        return -1;  // Si no hay proceso padre
}

uint64
sys_getancestor(void)
{
    int n;  // Variable temporal de tipo int para almacenar el argumento
    // Obtener el valor del parámetro n usando argint
    if (argint(0, &n) < 0)
        return -1;

    struct proc *p = myproc();  // Obtén el proceso actual
    
    // Iterar sobre los ancestros
    while (n > 0 && p->parent) {
        p = p->parent;  // Subir un nivel en la jerarquía
        n--;
    }

    // Si n es mayor que 0, no hay suficientes ancestros
    if (n > 0)
        return -1;

    return p->pid;  // Retornar el PID del ancestro encontrado
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
