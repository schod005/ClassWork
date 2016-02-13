/*
CSci 4061 Spring 2015 Assignment 2
Henry Grittner, 4560922
David Schoder, 4552990

This file contains data structures and functions that implement a double-linked list. Each node in the list can hold a single string representing the name of a file.
*/

#include "funcs.h"

#ifndef LISTFUNCS_H
#define LISTFUNCS_H


//an instance of a list
struct FileList {
	struct Node *headnode;	//first node in the list
	struct Node *tailnode;	//last node in the list
};

//linked-list node for filenames
struct Node {
	struct Node *next;	//next node in the list
	struct Node *prev;	//previous node in the list
	struct Node *htmlNext;	//set to next node when node is created, never changes
	char *data;		//filename of image
};


//declare functions
struct Node* findNextImage(struct FileList *curList, int imgType);
int addNode(struct FileList *curList, char *newData);
int getListLength(struct FileList *curList);
int deleteNode(struct FileList *curList, struct Node *node);


//return a pointer to the first node of type imgType in the image list
	//1=bmp, 2=gif, 3=png
struct Node* findNextImage(struct FileList *curList, int imgType){
	struct Node *curNode;

	//make sure list is not empty
	if (curList->headnode == NULL){
		return NULL;
	}
	
	//iterate through nodes until we reach the first one of the correct extension
	curNode = curList->headnode;
	while (curNode->next != NULL){
		if (getFileExtension(curNode->data) == imgType){
			return curNode;
		}
		curNode = curNode->next;
	}

	//check last node in the list
	if (getFileExtension(curNode->data) == imgType){
		return curNode;
	}

	return NULL;	//no nodes of the desired type exist
}


//add node to file list. Pass in filename as string
int addNode(struct FileList *curList, char *newData){
	struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));	//create new node
	newNode->data = newData;	//add data to node

	//if list is empty, make new node the new head of the list and exit
	if (curList->headnode == NULL){
		curList->headnode = newNode;			//make newnode the new headnode
		curList->tailnode = curList->headnode;		//make tailnode the headnode
		curList->headnode->htmlNext = curList->headnode;//make headnode point to itself
		return 0;					//exit
	}

	curList->tailnode->next = newNode;			//make tailnode point to newnode as next
	curList->tailnode->htmlNext = newNode;			//make tailnode.htmlNext point to newnode
	newNode->prev = curList->tailnode;			//make newnode point to tailnode as prev
	curList->tailnode = newNode;				//make newnode the new tailnode
	curList->tailnode->htmlNext = curList->headnode;	//link last node back to first node for html
	return 0;
}


//get length of file list
int getListLength(struct FileList *curList){
	struct Node *curNode;
	int i=1;

	//if list is empty, length is zero
	if (curList->headnode == NULL){
		return 0;
	}

	//iterate through list until we reach the last node. Increment i each time
	curNode = curList->headnode;
	while (curNode->next != NULL){
		i++;
		curNode = curNode->next;
	}
	
	return i;	//i is the length of the list
}


//delete node from file list
int deleteNode(struct FileList *curList, struct Node *node){
	//if this is not the last node in the list...
	if ((node->next) != NULL){
		node->next->prev = node->prev;	//make next node point to previous node
	}

	//if this is the first node in the list...
	if ((node->prev) == NULL){
		curList->headnode = node->next;	//make next node the new headnode
	}
	else {
		node->prev->next = node->next;	//otherwise make previous node point to next node
	}
	//DO NOT FREE MEMORY!
		//htmlNext value of node must be used to link up html files
		//htmlNext is constant even if node is deleted
		//ensures that each html file is included in the list
	return 0;
}

#endif

