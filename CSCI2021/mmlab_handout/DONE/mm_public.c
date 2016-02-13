#include "mm_public.h"

/* 
 * Returns time difference between "timee" and "times" in micro-seconds (usec)
 */
double comp_time (struct timeval times, struct timeval timee) {

    double elap = 0.0;

    if (timee.tv_sec > times.tv_sec) {
        elap += (((double)(timee.tv_sec - times.tv_sec -1))*1000000.0);
        elap += timee.tv_usec + (1000000-times.tv_usec);
    }
    else {
        elap = timee.tv_usec - times.tv_usec;
    }
    
    return ((unsigned long)(elap));
}

/* 
 * 
 * Allocate the big memory
 * Return 0 on success
 * Return -1 on failure
 */
int mm_init (mm_t* MM, int howmany, int size) {

    if(MM == NULL)
		MM = malloc(sizeof(mm_t));
    if(MM == NULL)
    {
		printf("%s","Memory failed to allocate");
		return -1;
	}	

    MM->chunk_count = howmany;
    MM->chunk_size = size;
    MM->mm_heap = malloc(howmany * size);
    MM->next_free = 0;
    
    void *array[howmany]; //need size
    MM->chunk_pointers = malloc(sizeof(array));
    
    int free[howmany]; //need size
    MM->free_chunks = malloc(sizeof(free));
    
    int i;
    for(i=0;i<howmany;i++){
		MM->chunk_pointers[i] = (void *) MM->mm_heap + i * size;
	}
	for(i=0;i<howmany;i++)
		MM->free_chunks[i] = 1;
	return 0;
}

/* 
 * 
 * Get a chunck of memory
 * On success: Return pointer to void
 * On failure: Return NULL
 */
void* mm_get (mm_t *MM) {

//checks to see if next_free is not out of bounds, then checks to see if
//chunk is free (0 means not free) and if not, check through entire heap
//until chunk is found that is free.  If no chunk is free, return NULL.

	if(MM->next_free >= MM->chunk_count)
		MM->next_free = 0;
		
	
	int count = 0;
	while(MM->free_chunks[MM->next_free] == 0)
	{
		MM->next_free++;
		if(MM->next_free >= MM->chunk_count)
			MM->next_free = 0;
		if(count>MM->chunk_count)
		{
			//printf("%s","WARNING!!  WARNING!!  No free memory");
			return (void *) NULL;
		}
		count++;
	}
	MM->free_chunks[MM->next_free] = 0;
	void *ret = MM->chunk_pointers[MM->next_free];
	MM->next_free++;
	return ret;
}

/* 
 * 
 * Give back chunk of your memory manager 
 * DON'T free it though!
 */
void mm_put (mm_t *MM, void *chunk) {
	
	MM->free_chunks[(int)(chunk-MM->mm_heap)/MM->chunk_size] = 1;
	//if you are confused, this sets the integer in the "free_chunks"
	//array, corresponding to the chunk freed to 1, which signifies it
	//is free.  I'm taking the differences in addresses of the chunk and
	//the beginning of the heap and dividing by the size of the chunk,
	//which will give the integer location of the chunk
}

/* 
 * 
 * Release the big memory back to the system
 */
void mm_release (mm_t *MM) {

	free(MM->mm_heap);
	free(MM->chunk_pointers);
}

/*
 * Example on how to use "comp_time" to time your code
 * Print the time difference in milli-seconds (msec)
 */
void timer_example ()
{
    struct timeval time_start, time_end;
    int j;

    /* start timer */
    j = gettimeofday (&time_start, (void *)NULL);

    /* Code you wish to time goes here */
    
    j = gettimeofday (&time_end, (void *)NULL);

    fprintf (stderr, "Time taken =  %f msec\n",
	    comp_time (time_start, time_end)/1000.0);
}  
/*
int main()
{
	mm_t *MM = malloc(sizeof(mm_t));
	mm_init(MM,50,8);
	int i;
	for(i=0;i<50;i++)
		printf("%p\n",MM->chunk_pointers[i]);

	return 0;
}
*/
