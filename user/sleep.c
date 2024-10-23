#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
// #include <unistd.h>

int main(int argc, char *argv[])
{
    if(argc < 2){
        char error[] = "Error: missing argument\n";
        write(1, error, strlen(error));
        exit(0);
    }
    else if(argc > 2){
        char error[] = "Error: too many argument\n";
        write(1, error, strlen(error));
        exit(0);
    }

    write(1, argv[1], strlen(argv[1]));
    write(1, "\n", 1);
    sleep(atoi(argv[1]));
    exit(0);
}
