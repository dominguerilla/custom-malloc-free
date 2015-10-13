#include "malloc-free.h"

static unsigned int front_index;
static unsigned int rear_index = MAX_SIZE;
static char memory[MAX_SIZE];
static unsigned int bytes_used;

void* my_malloc(size_t t){
	printf("my_malloc!\n");
	if(bytes_used >= MAX_SIZE){
		printf("Out of memory!\n");
		return NULL;
	}
	if(bytes_used + t > MAX_SIZE){
		printf("Not enough memory for this allocation.\n");
		return NULL;
	}
	if(t < LARGE_CHUNK_SIZE){
		if(front_index + t + 1 > rear_index){
			printf("Not enough memory for this allocation.\n");
			return NULL;
		}
		bytes_used = bytes_used + t + 1;
		memory[front_index] = t;
		int position = front_index + 1;
		front_index = position + t;
		return &memory[position];
	}
	else{
		if(MAX_SIZE - rear_index - t - 1 < front_index){
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
	printf("my_free!\n");
	void* prev = ptr-1;
	int size = *((int*)prev);
	int i = 0;
	for(i = 0; i < size; i++){
		memory[i] = '0';
	}
}
