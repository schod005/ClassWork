#include "dl_list.h"

/* 
 * Implemented the following functions
 * DL_LIST_INIT: Initialize list
 * INSERT_ITEM: Insert item at the end of the list
 * DELETE_ITEM: Delete all items with a specified value
 * COUNT_ITEMS: Count all items with a specified value
 * PRINT_LIST: Print the list from head to tail
 * JOIN_LISTS: Join two lists
 * DELETE_LIST: Delete all items in the list + the list itself
 */



/* 
 * Initiate the list
 * Takes as argument a newly created dl_list
 * Initialize all members with appropriate values.
 */
void dl_list_init(dl_list* list){
	list->head = NULL;
	list->cursor = NULL;
	list->tail = NULL;
}


/* 
 * Insert an item with value "val" at the end of "list" 
 */
void insert_item(dl_list* list, long int val, mm_t* mm) {
	node * newNode = mm_get(mm);
	newNode->value = val;
	if(list->head == NULL)
	{
		list->head = newNode;
		list->tail = newNode;
		list->cursor = newNode;
		newNode->next = NULL;
		newNode->prev = NULL;
	}
	else
	{
		newNode->prev = list->tail;
		list->tail->next = newNode;
		list->tail = newNode;
		newNode->next = NULL;
	}
	
}


/* 
 * Delete all items with value "val" from "list"
 * Return the number of items deleted.
 */
int delete_item(dl_list* list, long int val, mm_t* mm) {
	
	int count = 0;
	while(list->cursor != NULL)
	{
		if(list->cursor->value == val)
		{
			list->cursor->prev->next = list->cursor->next;
			count++;
			mm_put(mm,list->cursor);
		}
		list->cursor = list->cursor->next;
	}
	list->cursor = list->head;
    return count;
}


/*
 * Count the number of items with value "val"
 */
int count_items(dl_list* list, long int val) {
	
	int count = 0;
	while(list->cursor != NULL)
	{
		if(list->cursor->value == val)
		{
			count++;
		}
		list->cursor = list->cursor->next;
	}
	list->cursor = list->head;
    return count;
}


/*
 * Print out the value of all items in "list" in order
 * In order means: From head to tail; NOT sorted values.
 * Value are separated by spaces
 */
void print_list(dl_list* list) {

	while(list->cursor != NULL)
	{
		printf("%ld\n",list->cursor->value);
		list->cursor = list->cursor->next;
	}
	list->cursor = list->head;
}


/* 
 * Joins two lists
 * Attach list_b to list_a, and Leave list_b empty
 */
void join_lists(dl_list* list_a, dl_list* list_b) {
	
	list_a->tail = list_b->head;
	list_b->head = NULL;
	list_b->cursor = NULL;
	list_b->tail = NULL;
}


/*
 * Delete all items in the list.
 * Return the number of all items delete.
 */
int empty_list(dl_list* list, mm_t* mm) {
	
	int count = 0;
	while(list->cursor != NULL)
	{
		count++;
		mm_put(mm,list->cursor);
		list->cursor = list->cursor->next;
	}
    return count;
}

long int get_element(dl_list* list, int element)
{
	long int i;
	for(i = 0; i<element;i++)
		list->cursor = list->cursor->next;
	i = list->cursor->value;
	list->cursor = list->head;
	return i;
}
