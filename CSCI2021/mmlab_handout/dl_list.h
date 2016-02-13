#ifndef DL_LIST_H
#define DL_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include "mm_public.h"

/* node in doubly linked list */
struct dl_list_node {
    long int value;
    struct dl_list_node *prev;
    struct dl_list_node *next;
};

typedef struct dl_list_node node;

/* A Doubly Linked list */
struct dl_list {
    node *head;
    node *cursor;
    node *tail;
};

typedef struct dl_list dl_list;


/* 
 * Below are functions that you will have to implement:
 * DL_LIST_INIT: Initialize list
 * INSERT_ITEM: Insert item at the end of the list
 * DELETE_ITEM: Delete all items with a specified value
 * COUNT_ITEMS: Count all items with a specified value
 * PRINT_LIST: Print the list from head to tail
 * JOIN_LISTS: Join two lists
 */



/* 
 * Initiate the list
 * Takes as argument a newly created dl_list
 * Initialize all members with appropriate values.
 */
void dl_list_init(dl_list* list);


/* 
 * Insert an item with value "val" at the end of "list" 
 */
void insert_item(dl_list* list, long int val, mm_t* mm);


/* 
 * Delete all items with value "val" from "list"
 * Return the number of items deleted.
 */
int delete_item(dl_list* list, long int val, mm_t* mm);


/*
 * Count the number of items with value "val"
 */
int count_items(dl_list* list, long int val);


/*
 * Print out the value of all items in "list" in order
 * In order means: From head to tail; NOT sorted values.
 * Value are separated by spaces
 */
void print_list(dl_list* list);


/* 
 * Joins two lists
 * Attach list_b to list_a, and Leave list_b 
 */
void join_lists(dl_list* list_a, dl_list* list_b);

/*
 * Delete all items in the list.
 * Return the number of all items delete.
 */
int empty_list(dl_list* list, mm_t* mm);

long int get_element(dl_list* list, int element);

#endif
