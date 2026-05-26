#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
  printf("--- Thuc thi Exercise ---\n");
  
  printf("\n1. Test Kernel Memory Allocation:\n");
  memtest();

  printf("\n2. Test Process Table Listing:\n");
  pslist();

  exit(0);
}
