#include "malloc-free.h"

typedef struct test_struct{
	int integer;
	char character;
	float floatnum;
} *Test;

int main(){
	
	// make simple link list without assign data, allocating the memory address
	Test test = malloc(sizeof(Test));
	printf("Size of test_struct %d\n", (int)sizeof(Test));
	test->integer = 5;
	printf("Test int: %d\n", test->integer);
	
	
	printf("Attempting to free...\n");
	free(test);
	printf("Freed.\n");

	return 0;
}
