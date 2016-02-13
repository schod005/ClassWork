#include <stdio.h>
#include <stdlib.h>
#include "dl_list.h"
#include "mm_public.h"

int main(){

	srand(time(0));
	//Creating memory managers
	mm_t *MM = malloc(sizeof(mm_t));
	mm_init(MM,1500,sizeof(node));
	
	mm_t *MM2 = malloc(sizeof(mm_t));
	mm_init(MM2,3,sizeof(dl_list));
	
	//Creating Lists
    dl_list *dl_1 = mm_get(MM2);
    dl_list *dl_2 = mm_get(MM2);
    dl_list *dl_3 = mm_get(MM2);
    
    dl_list_init(dl_1);
    dl_list_init(dl_2);
    dl_list_init(dl_3);
	
	int i;
	for(i = 0; i<500; i++)
		insert_item(dl_1,i,MM);
	
	print_list(dl_1);
	
	for(i = 0; i<500; i++)
		insert_item(dl_2,rand()%500,MM);

	print_list(dl_2);
	
	for(i = 0; i<500; i++)
		insert_item(dl_3,get_element(dl_1,i)+get_element(dl_2,i),MM);
		
	print_list(dl_3);
	
	//Deleting items from list 1
	for(i = 0; i<100; i++)
		delete_item(dl_1,get_element(dl_3,i),MM);
	
	print_list(dl_1);
	
	//Joining lists
	join_lists(dl_2,dl_1);
	join_lists(dl_3,dl_2);
	
	print_list(dl_3);
	
	empty_list(dl_3,MM);
	
	//Deallocating and freeing
	mm_put(MM,dl_1);
	mm_put(MM,dl_2);
	mm_put(MM,dl_3);
	free(MM);
	free(MM2);

    return 0;
}
