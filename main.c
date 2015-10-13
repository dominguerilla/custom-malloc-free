#include "malloc-free.h"

int main(){
	char *x = malloc(sizeof(char));
	x = "asd";
	printf("%s\n", x);
	return 0;
}
