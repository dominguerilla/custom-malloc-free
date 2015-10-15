#include "malloc-free.h"

static char memory[MAX_SIZE] = {'x'};
static char is_alloc[MAX_SIZE] = {'0'};
static int size_of_chunk[MAX_SIZE] = {0};

static unsigned int front_index;
static unsigned int rear_index = MAX_SIZE;
static unsigned int bytes_used;

void* allocate(int size, char IS_LARGE){
	if(IS_LARGE == 'n'){
		/*
		* First, update the tracking values--bytes_used, size_of_chunk,
		* and is_alloc.
		*
		*/
		bytes_used = bytes_used + size;
		size_of_chunk[front_index] = size;
		int i;
		for(i = front_index; i < size; i++){
			is_alloc[i] = '1';
		}
		
		/*
		* Now that the proper tracking values are updated, the position of
		* 'frontier' between the allocated space and 'free space' is updated
		* and its position returned.
		*
		*/
		int start_of_chunk = front_index;
		front_index = front_index + size;
		return &memory[start_of_chunk];
	}else{
		/*
		* First, update the tracking values--bytes_used, size_of_chunk,
		* and is_alloc.
		*
		*/
		bytes_used = bytes_used + size;
		size_of_chunk[rear_index - size] = size;
		int i;
		for(i = rear_index; i < size; i++){
			is_alloc[rear_index] = '1';
			rear_index--;
		}

		/*
		* Now that the proper tracking values are updated, the position of
		* 'frontier' between the allocated space and 'free space' is updated
		* and its position returned.
		*
		*/
		return &memory[rear_index];
	}
}

void* my_malloc(size_t t){
	printf("size_t: %zd\n", t);
	/* If there is no more memory...*/
	if(bytes_used >= MAX_SIZE){
		printf("Out of memory!\n");
		return NULL;
	}
	
	/* If the used memory + the size of the attempted allocation is greater
	*  than maximum...
	*/
	if(bytes_used + t > MAX_SIZE){
		printf("Not enough memory for this allocation.\n");
		return NULL;
	}

	/* If the amount of memory to be allocated is considered 'small'*/
	if(t < LARGE_CHUNK_SIZE){
		if(front_index + t + 1 >= rear_index){
			printf("Not enough memory for this allocation.\n");
			return NULL;
		}
		return allocate((int)t,'n');
	}

	/* If the amount of memory to be allocated is considered 'large'*/
	else{
		if(MAX_SIZE - rear_index - t - 1 <= front_index){
			printf("Not enough memory for this allocation.\n");
			return NULL;
		}
		return allocate((int)t,'y');
	}
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
