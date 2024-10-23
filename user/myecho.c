#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int i;

  for(i = 1; i < argc; i++){
    write(1, argv[i], strlen(argv[i]));
    if(i + 1 < argc){
      write(1, " ", 1);
    } else {
        char arg_num = (char)(argc + '0');
        write(1, &arg_num, 1);
        write(1, "\n", 1);
    }
  }
  exit(0);
}
