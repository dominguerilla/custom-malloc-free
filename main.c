#include "malloc-free.h"

typedef struct test_struct{
	char character;
} *Test;

int main(){
	


	/*FREE-ING TESTS*/
	int *test;
	
	printf("Case 1 free...\n");
	free(test);
	test = malloc(sizeof(int)*15);
	printf("\n\n\n\n\n");
	
	printf("Case 2 free...\n");
	free(test + 5);
	printf("\n\n\n\n\n");

	printf("Case 3 free...\n");
	free(test);
	free(test);
	printf("\n\n\n\n\n");
	

	return 0;
}
