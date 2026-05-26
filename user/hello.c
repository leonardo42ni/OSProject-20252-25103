#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
  hello(); // Goi System Call chung ta vua tao
  printf("user: hello() da tro lai, quay ve user mode\n");
  exit(0);
}
