#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define MAX_SIZE 5000
#define LARGE_CHUNK_SIZE 100

#define malloc my_malloc
#define free my_free

void* my_malloc(size_t size);
void my_free(void* ptr);
