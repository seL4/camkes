/* @TAG(DATA61_BSD) */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    printf("Hello %s\n", argv[1]);
    printf("sleep 1 sec\n");
    sleep(1);
    printf("sleep 10 sec\n");
    sleep(10);
    printf("finished sleep\n");
}
