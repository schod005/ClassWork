#include <stdio.h>
#include "mm_public.h"

int main() {
    
    struct timeval time_start, time_end;
    int j;
    void *test[10000];
	mm_t *MM = malloc(sizeof(mm_t));
    mm_init(MM,10000,40);

    /* start timer */
    j = gettimeofday (&time_start, (void *)NULL);

    int i;
    for(i = 0; i<10000; i++)
		test[i] = mm_get(MM);
	for(i = 0; i<10000; i++)
		mm_put(MM,test[i]);
	mm_release(MM);
    
    j = gettimeofday (&time_end, (void *)NULL);

    fprintf (stderr, "Time taken =  %f msec\n",
	    comp_time (time_start, time_end)/1000.0);
	    
    return 0;
}

