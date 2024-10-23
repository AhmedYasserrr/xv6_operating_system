#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

/* My Logic while solving */
//reading fist number from pipe (fn)
// print fn
// delare newpipe of x+1
// fork();
// if child call primes()
// else 
// for loop from prev_pipe (read until reciving 0)
// if divisable by fn will send though new_pipe
// wait

void primes(int) __attribute__((noreturn));

int pipes[60][2];
void primes(int x){
    int fn;
    int n = read(pipes[x][0],&fn, 4);
    
    // terminate when reading 0 or write part of pipe is closed
    if(n == 0 || fn == 0){
        close(pipes[x][0]);
        close(pipes[x][1]);
        exit(0);
    }
    if(n < 0){
        printf("read error\n");
        exit(1);}

    printf("prime %d\n", fn);

    pipe(pipes[x+1]);
    if(fork() == 0){
        // close unrlated pipes for the new process 
        close(pipes[x][0]);
        close(pipes[x][1]);
        primes(x+1);
    }
    else{

        int buf;
        while(n != 0){
            n = read(pipes[x][0],&buf, 4);
            if(buf == 0) break;
            if(buf % fn != 0){
                write(pipes[x+1][1], &buf, 4);
            }
        }
        buf = 0;
        write(pipes[x+1][1], &buf, 4);

        close(pipes[x+1][1]);
        close(pipes[x+1][0]);
        close(pipes[x][1]);
        close(pipes[x][0]);
        wait(0);
    }
    exit(0);
}

int main(int argc, char *argv[])
{
    pipe(pipes[0]);
    if(fork() == 0){
        primes(0);
    }
    else{
        int i=2;
        for(; i<= 280; i++){
            write(pipes[0][1], &i, 4);
        }

        // End pipe with 0 to know when to stop reading
        i=0; 
        write(pipes[0][1], &i, 4);

        close(pipes[0][1]);
        close(pipes[0][0]);
        wait(0);
    }
    exit(0);
}

