#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define MAX_SIZE 5000
#define LARGE_CHUNK_SIZE 150

#define malloc(x) my_malloc(x, __FILE__, __LINE__)
#define free(x) my_free(x, __FILE__, __LINE__)

void* my_malloc(size_t size, char *_file, int line);
void my_free(void* ptr, char *_file, int line);
void print_ptr_infoo(void* ptr, int offset);
int checkForRoom(int index, int size, int isRear );
