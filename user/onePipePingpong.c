#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    if(fork() == 0) {
        write(p[1], "pong", 4);
        char buf[50];
        int n = read(p[0],buf, 4);
        char pid = getpid() + '0';
        write(1, &pid, 1);
        write(1, ": received ", strlen(": received "));
        write(1, buf, n);
        write(1, "\n", 1);
        close(p[0]);
        close(p[1]);
        exit(0);
    } else {
        write(p[1], "ping", 4);
        wait(0);
        char buf[50];
        int n = read(p[0],buf, 4);
        char pid = getpid() + '0';
        write(1, &pid, 1);
        write(1, ": received ", strlen(": received "));
        write(1, buf, n);
        write(1, "\n", 1);
        close(p[0]);
        close(p[1]);
        exit(0);
    }

}
