#include "malloc-free.h"


int main(){
	


	/*FREE-ING TESTS*/
	int *test, x, y=0;
	char *test2, c, v='0';
	float *test3, l, k=0.0f;
	
	printf("int *test, x, y=0;\n");
	printf("Case 1: Freeing a pointer not malloc'd:\n");
	printf("free(test); free(&x); free(&y);\n");
	free(test); 
	free(&x); 
	free(&y);
	printf("free(test2); free(&c); free(&y)\n");
	free(test2); 
	free(&c); 
	free(&y);
	printf("free(test3); free(&l); free(&k);\n");
	free(test3); 
	free(&l); 
	free(&y);
	printf("END Case 1 testing.\n\n\n\n");
	

	printf("test  = malloc(sizeof(int)*15);\n");
	test  = malloc(sizeof(int)*15);
	printf("test2 = malloc(sizeof(char)*20);\n");
	test2 = malloc(sizeof(char)*20);
	printf("test3 = malloc(sizeof(float)*14);\n");
	test3 = malloc(sizeof(float)*14);
	printf("\n\n\n\n");
	
	printf("Case 2: Freeing a pointer pointing to the middle of malloc'd memory:\n");
	printf("free(test + 5)\n");
	free(test + 5);
	printf("free(test2+ 4)\n");
	free(test2+ 4);
	printf("free(test3+ 3)\n");
	free(test3+ 3);
	printf("END Case 2 testing.\n\n\n\n");

	printf("Case 3: Freeing a pointer multiple times:\n");
	printf("free(test); free(test);\n");
	free(test); 
	free(test);
	printf("free(test2); free(test2);\n");
	free(test2); 
	free(test2);
	printf("free(test3); free(test3);\n");
	free(test3); 
	free(test3);
	printf("END Case 3 testing.\n\n\n\n");
	

	return 0;
}
