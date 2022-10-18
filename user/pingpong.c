//pingpong.c
#include "kernel/types.h"
#include "user/user.h"

#define READ 0
#define WRITE 1
int main() {
    int p1[2];//parent->child
    int p2[2];//child->parent
    pipe(p1);
    pipe(p2);

    if (fork() == 0) {
        char ping = 0;
        read(p1[READ], &ping, sizeof(ping));
        if (ping != 0) {
            printf("%d: received ping\n", getpid());
        }
        char pong = 'b';
        write(p2[WRITE], &pong, sizeof(pong));
    } else {
        char ping = 'a';
        write(p1[WRITE], &ping, sizeof(ping));
        char pong = 0;
        read(p2[READ], &pong, sizeof(pong));
        if (pong != 0) {
            printf("%d: received pong\n", getpid());
        }
        wait(0);
    }
    exit(0);
}
