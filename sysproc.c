#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "pstat.h"
#include "spinlock.h"
int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
//Set the desired number of tickets
int 
sys_settickets(void){    
  int n;
  if(argint(0, &n) < 0)  
    return -1;  
  myproc()->tickets = n;  
  return 0;  
} 
//Call the getpinfo function in proc.c
int 
sys_getpinfo(void){
  struct pstat* info;
  if(argint(0, (int*)(&info)) < 0) {
	  return -1;
  }
  getpinfo(info);
  return 0; 
}
int sys_mprotect(void) {
	void* addr;
	int len;
	if (argptr(0, (char **)&addr, sizeof(void *)) || argint(1, &len) < 0)
		return -1;
	if ((uint)addr % PGSIZE != 0 || len <= 0 || (uint)addr < PGSIZE)
		return -1;
	return mprotect(addr, len);
}
	
int sys_munprotect(void) {
	void * addr;
	int len;
	if (argptr(0, (char **)&addr, sizeof(void *)) || argint(1, &len) < 0)
		return -1;
	if ((uint)addr % PGSIZE != 0 || len <= 0 || (uint)addr < PGSIZE)
		return -1;
	return munprotect(addr, len);
}
