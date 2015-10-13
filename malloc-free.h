#ifndef MAX_SIZE
#define MAX_SIZE 5000
#endif

#ifndef LARGE_CHUNK_SIZE
#define LARGE_CHUNK_SIZE 100
#endif

#define malloc my_malloc
#define free my_free

void* my_malloc(size_t size);
void my_free(void* ptr);
