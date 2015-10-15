#include "malloc-free.h"

static char memory[MAX_SIZE] = {'x'};
static char is_alloc[MAX_SIZE] = {'0'};
static int size_of_chunk[MAX_SIZE] = {0};

static unsigned int front_index;
static unsigned int rear_index = MAX_SIZE;
static unsigned int bytes_used;

/*
* Given two addresses, the start of an array array_start and the position of some
* value in the array, calculateOffset will return the offset (the 'index') of the
* value in the array. So, if array[x] = value, this function returns x.
*/
int calculateOffset(void* array_start, void* value){
	
	return 0;
}

/*
* allocate() is BLIND--in the sense that it will allocate memory in memory[] blindly.
* The only method that should be calling this is malloc(), and so malloc() should
* be the one to do error checking.
*/
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
	
	/* For error 2, check the size_of_chunk array */

	/* For error 3, check the is_alloc array */
	
	/* 
	* To free the memory block,  free() must:
	* 1. Update is_alloc 
	* 2. Update size_of_chunk
	* 	->For both of these, in order to find the corresponding entry,
		  you have to calculate the offset of memory[0] and memory[wherever_this_pointer_is]
	* 3. Update bytes_allocated
	*/
}
