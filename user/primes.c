#include "kernel/types.h"
#include "user/user.h"

#define READ 0
#define WRITE 1

int main()
{
    int p1[2];
    pipe(p1);
    int i;
    for (i = 2; i <= 35; i++) {
        write(p1[WRITE], &i, sizeof(i));
    }
    i = 0;
    write(p1[WRITE], &i, sizeof(i));

    while (1) {
        int n;
        int prime;
        int p2[2];
        pipe(p2);
        read(p1[READ], &prime, sizeof(prime));
        printf("pid:%d start, prime: %d\n", getpid(), prime);
        if (read(p1[READ], &n, sizeof(n)) && n) {
            if (fork() == 0) {
                close(p1[READ]);
                close(p2[WRITE]);
                p1[READ] = p2[READ];
                p1[WRITE] = p2[WRITE];
                continue;
            } else {
                do {
                    if (n % prime != 0) {
                        write(p2[WRITE], &n, sizeof(n));
                    }
                } while (read(p1[READ], &n, sizeof(n)) && n);
                write(p2[WRITE], &n, sizeof(n));
            }
        }
        close(p1[READ]);
        close(p1[WRITE]);
        close(p2[READ]);
        close(p2[WRITE]);
        wait(0);
        break;
    }

    printf("pid:%d end\n", getpid());
    wait(0);
    exit(0);
}
