#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int t = 50; // Thử set 50 vé
  
  if(settickets(t) < 0){
    printf("Lỗi! Không set được vé.\n");
  } else {
    printf(" Đã set thành công %d vé cho tiến trình này.\n", t);
  }
  
  exit(0);
}
