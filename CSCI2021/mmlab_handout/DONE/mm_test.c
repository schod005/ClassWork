#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mm_public.h"

#define NUM_CHUNKS 20
#define CHUNK_SIZE 32


int main() {

  typedef struct {
    int val;
  } chunk_t;

  mm_t MM;
  mm_t MM1;
  mm_t MM2;

  int i;
  int j;
  int found;

  void* address;

  unsigned long int* addresses = (unsigned long int*) malloc(NUM_CHUNKS * sizeof(unsigned long int));
  unsigned long int* free_addresses = (unsigned long int*) malloc(NUM_CHUNKS * sizeof(unsigned long int));

  srand(time(NULL));


  /*
   * Initialize memory
   */

  if (mm_init(&MM, NUM_CHUNKS, CHUNK_SIZE) == -1) {
	printf("Failed to initialize memory!\n");
        exit(-1);
  }
  
  /*
   * Allocate all chunks
   */

  for (i = 0; i < NUM_CHUNKS; i++) {
    if (!(address = mm_get(&MM))) {
      printf("Failed to allocate a chunk %d while chunks available!\n", i);
      return 1;
    } else {
		addresses[i] = (unsigned long int) address;
    }
  }


  
  /*
   * Sort Address in ascending order
   */

  unsigned long int temp;
  
  for (i = 0; i < NUM_CHUNKS; i++) {
    for (j = i; j < NUM_CHUNKS; j++) {
      if (addresses[i] > addresses[j]) {
        temp = addresses[i];
        addresses[i] = addresses[j];
        addresses[j] = temp;
      }
    }
  }


  /*
   * Addresses are distinct
   */
  
  for (i = 1; i < NUM_CHUNKS; i++) {
    if (addresses[i] == addresses[i-1]) {
      printf("Not all chunk addresses are Distinct!\n");
      break;
    }
  }


  /*
   * Memory is contiguous
   * Chunk size OK
   */

  for (i = 1; i < NUM_CHUNKS; i++) {
    if (addresses[i] != addresses[i-1] + CHUNK_SIZE) {
      printf("Contiguity and Chunk Size NOT OK!\n");
      break;
    }
  }


  /*
   * Does not allocate more than NUM_CHUNKS
   */

  if (mm_get(&MM) != NULL) {
    printf("Allocating more than %d\n possible chunks!", NUM_CHUNKS);
  }


  /*
   * Deallocate a random number of chunks
   * Reallocate only these
   */
  
  for (i = 0; i < NUM_CHUNKS; i += (rand() % (NUM_CHUNKS/5)) + 1) {
    mm_put(&MM, (void*) addresses[i]);
    free_addresses[i] = addresses[i];
  }

  while (address = mm_get(&MM)) {
    found = 0;
    for (i = 0; i < NUM_CHUNKS; i++) {
      if (free_addresses[i] == (unsigned long int) address) {
        found = 1;
        break;
      }
    }
    if (found == 0) {
      printf("A chunk in use (or unmanaged) is being Allocated!\n");
      break;
    }
  }

  mm_release(&MM);
  free(free_addresses);
  free(addresses);


  /*
   * What about allocation and
   * deallocation of just a few chunks?
   */

  addresses = (unsigned long int*) malloc(10 * sizeof(unsigned long int));

  if (mm_init(&MM1, 10, 20) == -1) {
	printf("Failed to initialize memory!\n");
        exit(-1);
  }

  for (i = 0; i < 4; i++)
    addresses[i] = (unsigned long int) mm_get(&MM1);

  mm_put(&MM1, (void*) addresses[1]);
  addresses[1] = 0;

  while (address = mm_get(&MM1)) {
    found = 0;
    for (i = 0; i < 4; i++) {
      if (addresses[i] == (unsigned long int) address) {
        printf("A chunk in use is being reallocated!\n");
        break;
      }
    }
  }

  mm_release(&MM1);
  free(addresses);

  /*
   * Finally, Can we use the chunks?
   * Expect no segmentation fault.
   */
 
  if (mm_init(&MM2, NUM_CHUNKS, sizeof(chunk_t)) == -1) {
	printf("Failed to initialize memory!\n");
        exit(-1);
  }
/*
  chunk_t *my_chunk;
  for (i = 0; i < NUM_CHUNKS; i++) {
    chunk_t new_chunk;
    new_chunk.val = i;
    my_chunk = (chunk_t*) mm_get(&MM2);  
    memcpy(my_chunk, &new_chunk, sizeof(chunk_t));
  }

  mm_release(&MM2);
*/
  return 0;
}
