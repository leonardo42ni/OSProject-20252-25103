#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void calculate_pi(int tickets) {
    settickets(tickets);
    
    int n = 2000; 
    long long pi_scaled = 0;
    
    for (int i = 0; i < n; i++) {
        // Vòng lặp
        for (int j = 0; j < 5000000; j++) {
            asm volatile(""); 
        }

        long long term = 100000000 / (2 * i + 1);
        if (i % 2 == 0) pi_scaled += term;
        else pi_scaled -= term;

        // Giãn khoảng cách in ra  
        // Mục đích: Ép các tiến trình phải dùng CPU tính toán nhiều hơn là đứng chờ tranh nhau cái màn hình
        if (i % 50 == 0) { 
            if (tickets == 10) printf("1");
            else if (tickets == 30) printf("3");
            else if (tickets == 80) printf("8");
        }
    }
    
    // Báo cáo rõ ràng PID đi kèm với số vé
    printf("\n[PID %d - %d VE] DONE! Pi: %d\n", getpid(), tickets, (int)(pi_scaled * 4));
    exit(0);
}

int main() {
    int tickets[] = {10, 30, 80};
    
    printf("Bat dau cuoc dua tinh so Pi (Leibniz)...\n");
    printf("Ky hieu: 1 = 10 ve | 3 = 30 ve | 8 = 80 ve\n");
    printf("==================================================\n");

    for (int i = 0; i < 3; i++) {
        int pid = fork();
        if (pid == 0) {
            calculate_pi(tickets[i]);
        } else if (pid > 0) {
            // In ánh xạ ngay lúc tạo tiến trình để thầy giáo dễ đối chiếu
            printf("[He thong] Tao tien trinh PID %d voi %d ve.\n", pid, tickets[i]);
        }
    }

    for (int i = 0; i < 3; i++) wait(0);
    printf("\nThi nghiem ket thuc. Kiem tra dac tinh Lottery Scheduling.\n");
    exit(0);
}
