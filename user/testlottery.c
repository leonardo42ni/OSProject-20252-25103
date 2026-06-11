#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int pid1, pid2, pid3;

    printf("Bat dau test Lottery Scheduling...\n");

    pid1 = fork();
    if(pid1 == 0) {
        settickets(10); // Tiến trình 1 có 10 vé
        for(;;); // Vòng lặp vô hạn để ngốn CPU
    }

    pid2 = fork();
    if(pid2 == 0) {
        settickets(20); // Tiến trình 2 có 20 vé
        for(;;);
    }

    pid3 = fork();
    if(pid3 == 0) {
        settickets(30); // Tiến trình 3 có 30 vé
        for(;;);
    }

    // Tiến trình cha chờ các con (thực ra các con lặp vô hạn nên cha sẽ chờ mãi mãi)
    wait(0);
    wait(0);
    wait(0);
    
    exit(0);
}
