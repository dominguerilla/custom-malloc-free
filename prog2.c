#include "malloc-free.h"

int main(){
	/* DATA FRAGMENTATION TESTS */
	printf("Max size: %d\n", MAX_SIZE);
	char *string1 = malloc(sizeof(char) * 2000);
	printf("string1 malloc'd.\n");
	char *string2 = malloc(sizeof(char) * 2000);
	printf("string2 malloc'd.\n");
	char *string3 = malloc(sizeof(char) * 1000);
	printf("string3 malloc'd.\n");

	printf("Freeing string2.\n");
	free(string2);
	printf("Freeing string1.\n");
	free(string1);
	printf("malloc'ing string1 again.\n");
	string1 = malloc(sizeof(char) * 1000);
	return 0;
}
