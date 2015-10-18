#include "malloc-free.h"

static char memory[MAX_SIZE];
static char is_alloc[MAX_SIZE];
static int size_of_chunk[MAX_SIZE];

static unsigned int front_index;
static unsigned int rear_index = MAX_SIZE;
static unsigned int bytes_used;


/*
* allocate() is BLIND--in the sense that it will allocate memory in memory[] blindly.
* The only function that should be calling this is malloc(), and so malloc() should
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
		printf("bytes_used: %d\n", bytes_used);
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
		if(front_index + t >= rear_index){
			printf("Not enough memory for this allocation.\n");
			return NULL;
		}
		return allocate((int)t,'n');
	}

	/* If the amount of memory to be allocated is considered 'large'*/
	else{
		if(MAX_SIZE - rear_index - t <= front_index){
			printf("Not enough memory for this allocation.\n");
			return NULL;
		}
		return allocate((int)t,'y');
	}
}

void my_free(void* ptr){
	printf("Address of ptr: %p\n", ptr);
	printf("Address of memory[0]: %p\n", memory);
	/*
	* Freeing pointer that was never malloc'd
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
	* 1. Update char is_alloc 
	* 2. Update int size_of_chunk
	* 	->For both of these, in order to find the corresponding entry,
		  you have to calculate the byte offset of memory[0] and 
		  memory[wherever_this_pointer_is]
		->Then, the corresponding entry in is_alloc is is_alloc[offset]
		->In size_of_chunk, it should be size_of_chunk[offset]
	* 3. Update bytes_allocated
	*/
	int offset = sizeof(*ptr) - sizeof(memory[0]);
	printf("Offset: %d\n", offset);
	int iter = offset;
	int size_of_ptr = size_of_chunk[offset];
	/* (1) */
	int i;
	for(i = 0; i < size_of_ptr; i++){
		is_alloc[iter] = '0';
		iter++;
	}
	/* (3) */
	bytes_used = bytes_used - size_of_chunk[offset];
	/* (2) */
	size_of_chunk[offset] = 0;

}

void print_memory(){
	int i;
	printf("Memory:{ ");
	for(i = 0; i < MAX_SIZE; i++){
		printf("%c ", memory[i]);
	}
	printf("}\n");

	printf("is_alloc:{ ");
	for(i = 0; i < MAX_SIZE; i++){
		printf("%c ", is_alloc[i]);
	}
	printf("}\n");
	
	printf("size_of_chunk:{ ");
	for(i = 0; i < MAX_SIZE; i++){
		printf("%d ", size_of_chunk[i]);
	}
	printf("}\n");
	
}
