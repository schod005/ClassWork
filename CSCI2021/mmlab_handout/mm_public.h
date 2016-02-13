#ifndef MM_PUBLIC_H
#define MM_PUBLIC_H
#include <sys/time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define INTERVAL 0
#define INTERVAL_USEC 50000

typedef struct {
    void* mm_heap;   
    void** chunk_pointers;
    int* free_chunks;
    int chunk_count;
    int chunk_size;
    int next_free;
} mm_t;

/* 
 * Returns time difference between timee and times in micro-seconds (usec)
 */
double comp_time (struct timeval times, struct timeval timee);


/* 
 * Following are functions that YOU WILL DEFINE in "mm_public.h"
 */


/* allocate all memory, returns -1 on failure */
int mm_init (mm_t* MM, int howmany, int size);

/* get a chunk of memory (pointer to void), NULL on failure */
void* mm_get (mm_t *MM);

/* give back "chunk" to the memory manager, don't free it though! */
void mm_put (mm_t *MM, void *chunk);

/* Release all memory back to the system */
void mm_release (mm_t *MM);


#endif



