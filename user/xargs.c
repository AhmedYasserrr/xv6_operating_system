#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char *argv[])
{
    char *new_argv[MAXARG];
    char *waitlist[MAXARG];
    char b[512];

    int i = 1;
    for(; i < argc; i++){
        new_argv[i-1] = argv[i];
    }

    int n, fd=0;
    char buf[1];
    int j = 0;
    int l = 0;
    while((n = read(fd, buf, 1)) > 0) {
        if (*buf == '\n') {
            b[j] = 0; 
            waitlist[l] = malloc(j + 1);  
            memmove(waitlist[l], b, j + 1);
            j = 0;  
            l++;}
        else{
            // b[j] = *buf;
            memmove(b+j, buf, 1);
            j++;
        }
    }
    if(n < 0){
        fprintf(2, "read error\n");
        exit(1);
    }
    
    int max = l;
    for(l=0; l < max; l++){
        if(fork()==0){
            new_argv[i-1] = waitlist[l];
            exec(new_argv[0], new_argv);
            exit(0);
        }
        else{
            wait(0);
        }
    }


  exit(0);
}
