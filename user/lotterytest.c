#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void heavy_work(int id, int tickets) {
  // 20 dot in ra man hinh
  for (int i = 0; i < 20; i++) {
for (long long j = 0; j < 50000000LL; j++) {
      // Tinh toan nang
	 }
    // Moi dot xong, in ra mot ky tu dai dien cho minh
    if (tickets == 10) printf("1");
    else if (tickets == 30) printf("3");
    else if (tickets == 80) printf("8");
  }
}

int main(int argc, char *argv[]) {
  int tickets[] = {10, 30, 80}; 
  int pid;

  printf("Bat dau thi nghiem Lottery...\n");

  for (int i = 0; i < 3; i++) {
    pid = fork();
    if (pid < 0) {
      exit(1);
    } else if (pid == 0) {
      // CON DAY: Phai truyen i va tickets[i] vao ham
      settickets(tickets[i]);
      heavy_work(i, tickets[i]);
      
      printf("\nCon [%d] (%d ve) XONG!\n", getpid(), tickets[i]);
      exit(0);
    }
  }

  for (int i = 0; i < 3; i++) wait(0);
  printf("\nThi nghiem ket thuc.\n");
  exit(0);
}
