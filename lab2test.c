#include "types.h"
#include "user.h"

int main() {
        int ret;
        int *addr=(int*) 4096;
        //Protect and unprotect an address
        if((ret = mprotect((void*)addr, 1))==-1){
                printf(1, "mprotect failed %d\n", ret);
        }
        printf(1, "mprotect called\n");
        if((ret = munprotect((void *)addr, 1))==-1){
                printf(1, "munprotect failed %d\n", ret);
        }
        printf(1, "munprotect called, attempting to overwrite...\n");
        //Check if it was sucessfully unprotected
        *addr = 1;
        printf(1, "Overwrite successful, address=%d\n",  *(int *)4096);
        //Protect it again and try to write to it, this should result in a trap error and terminate the program
        if((ret = mprotect((void *)addr, 1))==-1){
                printf(1, "mprotect failed %d\n", ret);
        }
        printf(1, "mprotect called, attempting to overwrite...\n");
        *addr = 2;
        printf(1, "Overwrite successful, mprotect failed\n");
        exit();
}
