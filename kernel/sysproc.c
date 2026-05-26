#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "vm.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  kexit(n);
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
  return kfork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return kwait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int t;
  int n;

  argint(0, &n);
  argint(1, &t);
  addr = myproc()->sz;

  if(t == SBRK_EAGER || n < 0) {
    if(growproc(n) < 0) {
      return -1;
    }
  } else {
    // Lazily allocate memory for this process: increase its memory
    // size but don't allocate memory. If the processes uses the
    // memory, vmfault() will allocate it.
    if(addr + n < addr)
      return -1;
    if(addr + n > TRAPFRAME)
      return -1;
    myproc()->sz += n;
  }
  return addr;
}

uint64
sys_pause(void)
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
  return kkill(pid);
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

uint64
sys_hello(void)
{
  struct proc *p = myproc();
  // In ra màn hình console của QEMU (Kernel-mode)
  printf("kernel: hello() duoc goi boi User (PID %d)\n", p->pid);
  return 0; // Tra ve 0 cho User-space
}

// 1. Allocate memory trong Kernel
uint64
sys_memtest(void)
{
  // kalloc() la ham cap phat 1 trang bo nho (4096 bytes) trong Xv6
  char *mem = kalloc();
  
  if(mem == 0){
    printf("kernel: Het bo nho\n");
    return -1;
  }

  printf("kernel: Da cap phat 4KB tai dia chi: %p\n", mem);
  
  // Luon nho giai phong bo nho sau khi test de tranh "Memory Leak"
  kfree(mem);
  printf("kernel: Da giai phong bo nho.\n");
  
  return 0;
}

// 2. Liet ke danh sach tien trinh
// Luu y: Ban can include "spinlock.h" va "proc.h" o dau file neu chua co
uint64
sys_pslist(void)
{
  // Trong Xv6, moi thu deu nam trong mang 'proc' (Process Table)
  // Chung ta can dung extern de truy cap mang nay tu proc.c
  extern struct proc proc[]; 
  struct proc *p;

  printf("\n--- PID --- NAME --- STATE ---\n");
  for(p = proc; p < &proc[NPROC]; p++){
    if(p->state != UNUSED){
      char *state;
      if(p->state == SLEEPING) state = "SLEEP";
      else if(p->state == RUNNABLE) state = "RUNABLE";
      else if(p->state == RUNNING) state = "RUNNING";
      else if(p->state == ZOMBIE) state = "ZOMBIE";
      else state = "UNKNOWN";

      printf("    %d      %s      %s\n", p->pid, p->name, state);
    }
  }
  return 0;
}
//25103 nghen
// Hàm này được gọi khi User-space gọi settickets(n)
uint64
sys_settickets(void)
{
  int n;
  argint(0, &n);

  if(n < 1)
    return -1;

  myproc()->tickets = n;
  
  return 0;
}

