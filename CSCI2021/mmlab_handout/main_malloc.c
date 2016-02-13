#include <stdio.h>
#include "mm_public.h"
int main() {
	
	struct timeval time_start, time_end;
    int j;
    void *test[10000];
    /* start timer */
    j = gettimeofday (&time_start, (void *)NULL);

	int i;
	for(i = 0; i<10000; i++)
		test[i] = malloc(40);
	for(i = 0; i<10000; i++)
		free(test[i]);
    
    j = gettimeofday (&time_end, (void *)NULL);

    fprintf (stderr, "Time taken =  %f msec\n",
	    comp_time (time_start, time_end)/1000.0);
	
    return 0;	
}

