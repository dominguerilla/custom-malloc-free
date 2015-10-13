#include "malloc-free.c"

int main(){
	char *x = malloc(sizeof(char));
	x = "asd";
	printf("%s", x);
	return 0;
}
