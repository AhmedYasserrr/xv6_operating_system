#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int ping_pipe[2];
    int pong_pipe[2];
    pipe(ping_pipe);
    pipe(pong_pipe);
    if(fork() == 0) {
        write(pong_pipe[1], "pong", 4);
        char buf[4];
        int n = read(ping_pipe[0],buf, 4);
        char pid = getpid() + '0';
        write(1, &pid, 1);
        write(1, ": received ", strlen(": received "));
        write(1, buf, n);
        write(1, "\n", 1);
        close(pong_pipe[0]);
        close(pong_pipe[1]);
        close(ping_pipe[0]);
        close(ping_pipe[1]);
        exit(0);
    } else {
        write(ping_pipe[1], "ping", 4);
        wait(0);
        char buf[4];
        int n = read(pong_pipe[0],buf, 4);
        char pid = getpid() + '0';
        write(1, &pid, 1);
        write(1, ": received ", strlen(": received "));
        write(1, buf, n);
        write(1, "\n", 1);
    }
    close(pong_pipe[0]);
    close(pong_pipe[1]);
    close(ping_pipe[0]);
    close(ping_pipe[1]);
    exit(0);
}
