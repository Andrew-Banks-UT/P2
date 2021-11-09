#include "types.h"
#include "user.h"

int main() {
	int ret;
	//Protect and unprotect an address
	if((ret = mprotect((void *)4096, 4096))==-1){
		printf(1, "mprotect failed %d\n", ret);
	}
	printf(1, "mprotect called\n");
	if((ret = munprotect((void *)4096, 4096))==-1){
		printf(1, "munprotect failed %d\n", ret);
	}
	printf(1, "munprotect called, attempting to overwrite...\n");
	//Check if it was sucessfully unprotected
	*(int *)4096 = 1;
	printf(1, "Overwrite successful, address=%d\n",  *(int *)4096);
	//Protect it again and try to write to it, this should result in a trap error and terminate the program
	if((ret = mprotect((void *)4096, 4096))==-1){
		printf(1, "mprotect failed %d\n", ret);
	}
	printf(1, "mprotect called, attempting to overwrite...\n");
	*(int *)4096 = 2;
	printf(1, "Overwrite successful, mprotect failed\n");
	exit();
}
