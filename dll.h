#include <stdio.h>

#ifndef __DLL_INCLUDED__
#define __DLL_INCLUDED__

typedef struct dllnode
{
  void *value;
  struct dllnode *next;
  struct dllnode *prev;
} dllnode;

typedef struct dll
{
  dllnode *head;
  dllnode *tail;
  int size;
  void (*display)(FILE *,void *);
} dll;

dll *newDLL(void (*d)(FILE *,void *));            //constructor
void insertDLL(dll *items,int index,void *value); //stores a generic value
void *removeDLL(dll *items,int index);            //returns a generic value
void unionDLL(dll *recipient,dll *donor);         //merge two lists into one
void *getDLL(dll *items,int index);               //get the value at the index
int sizeDLL(dll *items);
void displayDLL(FILE *,dll *items);

#endif
