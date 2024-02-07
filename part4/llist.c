// Implement a double linked-list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

// Initialize the linked list by setting head to NULL
// PRE: head is the pointer variable that points to the
//      first node of the linked list
// POST: head is set to NULL

void init_llist(TLinkedList **head) {
    // Set head to NULL
    *head = NULL;
}

// Create a new node
// PRE: filename = name of file to be inserted
//      filesize = size of file in blocks
//      startblock = File's starting block
// RETURNS: A new node containing the file information is created.

TLinkedList *create_node(char *filename, int filesize, int startblock) {
  // Explicit memory allocation for the new node
  TLinkedList *newNode = (TLinkedList*) malloc(sizeof(TLinkedList));
  
  // Check if memory allocation is successful (i.e. newNode shouldn't point to NULL)
  if (newNode == NULL) {
    return NULL;
  }

  strcpy(newNode->filename, filename);  

  // Copy value
  newNode->filesize = filesize;
  newNode->startblock = startblock;

  // Points next to NULL and points prev to NULL
  newNode->next = NULL;
  newNode->prev = NULL;
  
  return newNode;
}

// Insert node into the end of the linkedlist indicated by head
// PRE: head = Pointer variable pointing to the start of the linked list
//      node = Node created using create_node
// POST: node is inserted into the linked list.

void insert_llist(TLinkedList **head, TLinkedList *node) {
  if (*head == NULL) {
    *head = node;
  } else {
    TLinkedList *trav = *head;
    while (trav->next != NULL) {
      trav = trav->next;
    }
    
    trav->next = node;
    node->prev = trav;
    node->next = NULL;
  }
}

// Delete node from the linkedlist
// PRE: head = Pointer variable pointing to the start of the linked list
//      node = An existing node in the linked list to be deleted.
// POST: node is deleted from the linked list

void delete_llist(TLinkedList **head, TLinkedList *node) {
  if (*head == NULL || node == NULL) {
    return; // nothing to be deleted
  }

  if (*head == node) { // node is the curr head
    *head = node->next;

    if (*head != NULL) {
      // adjust pointer
      (*head)->prev = NULL;
    }
  } else {
    
    if (node->prev != NULL) {
      node->prev->next = node->next;
    }

    if (node->next != NULL) {
      node->next->prev = node->prev;
    }
  }

  // free node
  free(node);
  node = NULL;
}


// Find node in the linkedlist
// PRE: head = Variable that points to the first node of the linked list
//      fname = Name of file to look for
// RETURNS: The node that contains fname, or NULL if not found.
TLinkedList *find_llist(TLinkedList *head, char *fname) {
  TLinkedList *temp = head;
  while (temp != NULL) {
    if (strcmp(temp->filename, fname)) {
      return temp;
    }
    temp = temp->next;
  }

  return NULL;
}

// Traverse the entire linked list calling a function
// PRE: head = Variable pointing to the first node of the linked list
//      fn = Pointer to function to be called for each node
// POST: fn is called with every node of the linked list.

void traverse(TLinkedList **head, void (*fn)(TLinkedList *)) {
  TLinkedList *temp = *head;
  while (temp != NULL) {
    fn(temp);
    temp = temp->next;
  }
}

