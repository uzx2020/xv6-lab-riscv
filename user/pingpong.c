#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char buf;
    int fd1s[2];
    int fd2s[2];
    if (pipe(fd1s) < 0) {
        printf("pipe1 fail");
        exit(1);
    }
    if (pipe(fd2s) < 0) {
        printf("pipe2 fail");
        exit(1);
    }
    int pid = fork();
    if (pid == 0) {
        // child
        // close(fd1s[1]);
        // close(fd2s[0]);
        read(fd1s[0], &buf, 1);
        printf("<%d>:received ping\n", getpid());

        write(fd2s[1], &buf, 1);
        // close(fd1s[0]);
        // close(fd2s[1]);
        // exit(0);
    } else {
        // parent
        // close(fd1s[0]);
        // close(fd2s[1]);
        write(fd1s[1], &buf, 1);

        read(fd2s[0], &buf, 1);
        printf("<%d>:received pong\n", getpid());
        // close(fd1s[1]);
        // close(fd2s[0]);
        // exit(0);
    }
    exit(0);
}
