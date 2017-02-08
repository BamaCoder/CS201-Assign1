#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stack *newStack(void (*d)(FILE *,void *)) 
{
  stack *items = malloc (sizeof(stack));
  if(items == 0) 
  {
    fprintf(stderr, "out of memory");
    exit(-1);
  }
  items->list = newDLL(d);
  return items;
}

void push(stack *items,void *value)
{
  insertDLL(items->list, 0, value);
}

void *pop(stack *items) 
{
  return removeDLL(items->list, 0);
}

void *peekStack(stack *items)
{
  return getDLL(items->list, 0);
}

int sizeStack(stack *items)
{
  return sizeDLL(items->list);
}

void displayStack(FILE *fp,stack *items) 
{
  return displayDLL(fp, items->list);
}

