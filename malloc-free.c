#include "malloc-free.h"

static char memory[MAX_SIZE];
static char is_alloc[MAX_SIZE];
static int size_of_chunk[MAX_SIZE];

static unsigned int front_index;
static unsigned int rear_index = MAX_SIZE - 1;
static unsigned int bytes_used;


/*
* allocate() is BLIND--in the sense that it will allocate memory in memory[] blindly.
* The only function that should be calling this is malloc(), and so malloc() should
* be the one to do error checking.
*/
void* allocate(int size, char IS_LARGE){
	
	/*
	printf("Sample is_alloc[50]: %c", is_alloc[50]);
	printf("Size to allocate: %d\n", size);
	*/
	if(IS_LARGE == 'n'){
		/*printf("Small malloc.\n");
		
		* First, update the tracking values--bytes_used, size_of_chunk,
		* and is_alloc.
		*
		*/
		bytes_used = bytes_used + size;
		/*printf("bytes_used: %d\n", bytes_used);*/
		size_of_chunk[front_index] = size;
		int i, iter = front_index;
		for(i = 0; i < size; i++){
			is_alloc[iter] = '1';
			iter++;
		}
		
		/*
		* Now that the proper tracking values are updated, the position of
		* 'frontier' between the allocated space and 'free space' is updated
		* and its position returned.
		*
		*/
		int start_of_chunk = front_index;
		front_index = front_index + size;
		printf("bytes_used after malloc: %d\n", bytes_used);
		return &memory[start_of_chunk];
	}else{
		/*printf("Large malloc.\n");
		
		* First, update the tracking values--bytes_used, size_of_chunk,
		* and is_alloc.
		*
		*/
		bytes_used = bytes_used + size;
		rear_index = rear_index - size + 1;
		size_of_chunk[rear_index] = size;
		int i, iter = rear_index;
		for(i = 0; i < size; i++){
			is_alloc[iter] = '1';
			iter++;
		}
		/*
		printf("END: Rear index: %d\n", rear_index);
		printf("&memory[rear_index] = %p\n", &memory[rear_index]);
		*/
		/*
		* Now that the proper tracking values are updated, the position of
		* 'frontier' between the allocated space and 'free space' is updated
		* and its position returned.
		*
		*/
		printf("&memory[%d]: %p\n", rear_index, &memory[rear_index]);
		return &memory[rear_index];
	}
}

void* my_malloc(size_t t, char *_file, int _line){
	/* If there is no more memory...*/
	if(bytes_used >= MAX_SIZE){
		printf("Out of memory!\n");
		printf("Line %d, %s\n", _line, _file);
		return NULL;
	}
	
	/* If the used memory + the size of the attempted allocation is greater
	*  than maximum...
	*/
	if(bytes_used + t > MAX_SIZE){
		printf("Not enough memory for this allocation -- MAX_SIZE+t.\n");
		printf("front_index: %d, rear_index: %d, t: %lu\n", front_index, rear_index, t);
		printf("Line %d, %s\n", _line, _file);
		return NULL;
	}

	/* If the amount of memory to be allocated is considered 'small'*/
	if(t < LARGE_CHUNK_SIZE){
		int check = checkForRoom(front_index, t, 0);
		if(check == 0){
			printf("Line %d, %s\n", _line, _file);
			return NULL;
		}
		if(front_index + t > rear_index + 1){
			
			printf("Not enough memory for this allocation -- FRONT_INDEX+t.\n");
			printf("front_index: %d, rear_index: %d, t: %lu\n", front_index, rear_index, t);
			printf("Line %d, %s\n", _line, _file);
			return NULL;
		}
		return allocate((int)t,'n');
	}

	/* If the amount of memory to be allocated is considered 'large'*/
	else{
		int check = checkForRoom(rear_index, t, 1);
		if(check == 0){
			printf("Line %d, %s\n", _line, _file);
			return NULL;
		}
		if(rear_index + 1 < front_index + t){
			printf("Not enough memory for this allocation -- REAR_INDEX-t.\n");
			printf("front_index: %d, rear_index: %d, t: %lu\n", front_index, rear_index, t);
			printf("Line %d, %s\n", _line, _file);
			return NULL;
		}
		return allocate((int)t,'y');
	}
}

void my_free(void* ptr, char *_file, int _line){
	/*
	printf("Address of ptr: %p\n", ptr);
	printf("Address of memory[0]: %p\n", memory);
	*/
	ptrdiff_t  offset = (char*)ptr - &memory[0];
	
	/*printf("Offset: %td\n", offset);
	
	* Freeing pointer that was never malloc'd
	* means that the address of that pointer is not
	* within range of memory[0] and memory[MAX_SIZE-1]
	
	printf("&memory[MAX_SIZE-1]: %p\n", &memory[MAX_SIZE-1]);
	*/
	if((void*)ptr < (void*)memory || (void*)ptr > (void*)&memory[MAX_SIZE-1]){
		printf("You did not malloc this pointer.\n");
		printf("Line %d, %s\n", _line, _file);
		return;
	}
	
	/* For error 2, check the size_of_chunk array 
	printf("size_of_chunk[%tu]: %d\n",offset, size_of_chunk[offset]);
	*/
	if(size_of_chunk[offset] == 0){
		printf("This is not the pointer to the beginning of allocated data.\n");
		print_ptr_info(ptr, offset);
		printf("Line %d, %s\n", _line, _file);
		return;
	}
	/* For error 3, check the is_alloc array 
	printf("is_alloc[%tu]: %c\n", offset, is_alloc[offset]);
	*/
	if(is_alloc[offset] == '\0'){
		printf("This pointer was never malloc'd.\n");
		print_ptr_info(ptr, offset);
		printf("Line %d, %s\n", _line, _file);
		return;
	}


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
	int iter = offset;
	int size_of_ptr = size_of_chunk[offset];
	/*
	* Updating the rear_index or front_index
	*
	*/
	if(size_of_ptr > LARGE_CHUNK_SIZE){
		if(&memory[rear_index] == &ptr){
			rear_index = rear_index + size_of_ptr;
		}
	}else{
		if(&memory[front_index] == &ptr){
			front_index = front_index - size_of_ptr;
		}
	}
	/* (1) */
	int i;
	for(i = 0; i < size_of_ptr; i++){
		is_alloc[iter] = '\0';
		iter++;
	}
	/* (3) */
	bytes_used = bytes_used - size_of_chunk[offset];
	printf("bytes_used after free: %d\n", bytes_used);
	/* (2) */
	size_of_chunk[offset] = 0;

}

void print_ptr_info(void* ptr, int offset){
	printf("ptr = %p\n", ptr);
	printf("&memory[%d] = %p\n", offset, &memory[offset]);
	printf("is_alloc[%d] = %c\n", offset, is_alloc[offset]);
	printf("size_of_chunk[%d] = %d\n", offset, size_of_chunk[offset]);
}


int checkForRoom(int index, int size, int isRear){
	int i, iter;
	/* If checking for a front allocation */
	if(isRear == 0){
		iter = front_index;
		for(i = 0; i < size; i++){
			if(iter >= MAX_SIZE || is_alloc[iter] == '1'){
				printf("No room for a front allocation!\n");
				printf("front_index: %d, rear_index: %d, t: %d\n", front_index, rear_index, size);
				return 0;
			}
			iter++;
		}
	}
	else{
		iter = rear_index - 1;
		printf("is_alloc[%d]: %c\n", iter, is_alloc[iter]);
		for(i = 0; i < size; i++){
			if(iter <= 0 || is_alloc[iter]== '1'){	
				printf("No room for a rear allocation!\n");
				printf("front_index: %d, rear_index: %d, t: %d\n", front_index, rear_index, size);
				return 0;
			}
			iter--;
		}
	}
	return 1;
}
