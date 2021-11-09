#include "types.h"
#include "user.h"

int main() {
	//Should result in trap error 14
	int *ptr = 0;
	printf(1, "%d\n", *ptr);
	exit();
}
