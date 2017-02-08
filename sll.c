#include <stdio.h>
#include <stdlib.h>
#include "sll.h"

/* Creates a new singly linked list with variables initialized to zero */
sll *newSLL(void (*d)(FILE *,void *)) //d is the display function
{
  sll *items = malloc(sizeof(sll));
  if (items == 0)
  {
    fprintf(stderr,"out of memory");
    exit(-1);
  }
  items->head = 0;
  items->tail = 0;
  items->size = 0;
  items->display = d;
  return items;
}

/* Inserts a new node to the singly linked list at the specified location */
void insertSLL(sll *items, int index, void *value)
{
  int i;
  sllnode *newnode = malloc(sizeof(sllnode));

  if (newnode == 0)
  {
    fprintf(stderr, "out of memory");
    exit(-1);
  }

  sllnode *traversenode = items->head;
  // Error Checking for Index input
  newnode->value = value;
  if(index == 0) // If at front of list
  {
    newnode->next = items->head;
    if(items->tail == 0) items->tail = newnode;
    items->head = newnode;
  }
  else if(index == sizeSLL(items)) // If at back of list
  {
    newnode->next = 0;
    items->tail->next = newnode;
    items->tail = newnode;
  }
  else  // All other locations in the SLL
  {
    for(i = 0; i < index-1; i++)
    {
      traversenode = traversenode->next;
    }
    newnode->next = traversenode->next;
    traversenode->next = newnode;
  }
  items->size++;
}

/* Removes a node from the singly linked list at a specified location */
/* and returns the value of the removed node.                         */
void *removeSLL(sll *items, int index)
{
  int i;
  if (items->size == 0)
  {
    fprintf(stderr, "ERROR: EMPTY LIST, No values to be removed.");
    exit(-1);
  }
  sllnode *traversenode = items->head;
  sllnode *temp;
  void *delval;
  if(index == 0)
  {
    temp = items->head;
    delval = temp->value;
    items->head = items->head->next;
    if(items->size == 1) items->tail = 0;
    free(temp);
  }
  else if (index == sizeSLL(items)-1)
  {
    temp = items->tail;
    delval = temp->value;
    while(traversenode->next != temp) traversenode = traversenode->next;
    items->tail = traversenode;
    items->tail->next = 0;
    free(temp);
  }
  else
  {
    for(i = 0; i < index-1; i++)
    {
      traversenode = traversenode->next;
    }
    temp = traversenode->next;
    delval = temp->value;
    traversenode->next = traversenode->next->next;
    free(temp);
  }
  items->size--;
  return delval;
}

/* Combines the two lists into the recipient list */
void unionSLL(sll *recipient, sll*donor)
{
  if(recipient->head == 0 && donor->head != 0) recipient = donor;
  else if(donor->head == 0) return;
  recipient->tail->next = donor->head;
  recipient->tail = donor->tail;
  recipient->size += donor->size;
  donor->head = donor->tail = 0;
  donor->size = 0;
}

/* Retrieves the value of a node at a specified index in the list */
void *getSLL(sll *items, int index)
{
  int i;
  if (items->size == 0)
  {
    fprintf(stderr, "ERROR: EMPTY LIST, no values to be retrieved.");
    exit(-1);
  }
  sllnode *traversenode = items->head;
  if(index == 0)
  {
    return items->head->value;
  }
  else if(index == sizeSLL(items)-1)
  {
    return items->tail->value;
  }
  else
  {
    for(i = 0; i < index; i++)
    {
      traversenode = traversenode->next;
    }
    return traversenode->value;
  }
}

/* Returns the value of the size of the SLL */
int sizeSLL(sll *items)
{
  return items->size;
}

/* Displays the SLL using the associated display function */
void displaySLL(FILE *fp, sll *items)
{
  sllnode *traversenode = items->head;
  fprintf(fp, "[");
  if(traversenode != 0)
  {
    while(traversenode->next != 0)
      {
        items->display(fp,traversenode->value);
        traversenode = traversenode->next;
        fprintf(fp, ",");
      }
    items->display(fp,traversenode->value);
  }
  fprintf(fp, "]\n");
}
