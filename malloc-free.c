#include "malloc-free.h"

static unsigned int front_index;
static unsigned int rear_index = MAX_SIZE;

static char memory[MAX_SIZE] = {'x'};
/*static char is_alloc[MAX_SIZE] = {'0'};*/
static unsigned int bytes_used;

void* my_malloc(size_t t){
	printf("size_t: %zd\n", t);
	if(bytes_used >= MAX_SIZE){
		printf("Out of memory!\n");
		return NULL;
	}
	if(bytes_used + t > MAX_SIZE){
		printf("Not enough memory for this allocation.\n");
		return NULL;
	}
	if(t < LARGE_CHUNK_SIZE){
		if(front_index + t + 1 >= rear_index){
			printf("Not enough memory for this allocation.\n");
			return NULL;
		}
		bytes_used = bytes_used + t + 1;
		memory[front_index] = t;
		printf("memory[front_index] = %c\n", memory[front_index]);
		int position = front_index + 1;
		front_index = position + t;
		return &memory[position];
	}
	else{
		if(MAX_SIZE - rear_index - t - 1 <= front_index){
			printf("Not enough memory for this allocation.\n");
			return NULL;
		}
		bytes_used = bytes_used + t + 1;
		rear_index = rear_index - t - 1;
		memory[rear_index] = t;
		return &memory[rear_index];
	}

	printf("you shouldn't have gotten here\n");
	return NULL;
}

void my_free(void* ptr){
	/*Freeing pointer that was never malloc'd
	* means that the address of that pointer is not
	* within range of memory[0] and memory[MAX_SIZE-1]
	*/
	if((void*)ptr < (void*)memory || (void*)ptr > (void*)&memory[MAX_SIZE-1]){
		printf("You did not malloc this pointer.\n");
		return;
	}
	void* prev = ptr-1;
	int size = *((int*)prev);
	printf("the size of this pointer is %d\n", size);
	
	int i = 0;
	for(i = 0; i < size; i++){
		memory[i] = ' ';
	}
}
