#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

/* Creates a new DLL with a specified display function as the input parameter */
dll *newDLL(void (*d)(FILE *, void *))
{
    dll *items = malloc(sizeof(dll));
    if(items == 0)
    {
        fprintf(stderr, "out of memory");
        exit(-1);
    }
    items->head = 0;
    items->tail = 0;
    items->size = 0;
    items->display = d;
    return items;
}

/* Inserts node to DLL with a specified value at a specified location */
void insertDLL(dll *items, int index, void *value)
{
    int i;
    dllnode *newnode = malloc(sizeof(dllnode));
    if(newnode == 0)
    {
        fprintf(stderr, "out of memory");
        exit(-1);
    }
    dllnode *traversenode;
    newnode->value = value;
    if(index == 0) // if at start of list
    {
      if(items->size == 0)
      {
        items->head = newnode;
        items->tail = newnode;
        newnode->prev = 0;
        newnode->next = 0;
      }
      else
      {
        newnode->next = items->head;
        items->head->prev = newnode;
        newnode->prev = 0;
        items->head = newnode;
      }
    }
    else if(index == sizeDLL(items))
    {
        newnode->prev = items->tail;
        items->tail->next = newnode;
        newnode->next = 0;
        items->tail = newnode;
    }
    else
    {
        if(index < sizeDLL(items)/2)
        {
            traversenode = items->head;
            for(i = 0; i < index-1; i++)
            {
                traversenode = traversenode->next;
            }
            newnode->next = traversenode->next;
            newnode->next->prev = newnode;
            newnode->prev = traversenode;
            traversenode->next = newnode;
        }
        else
        {
            traversenode = items->tail;
            for(i = sizeDLL(items)-1; i > index; i--)
            {
                traversenode = traversenode->prev;
            }
            newnode->prev = traversenode->prev;
            newnode->prev->next = newnode;
            newnode->next = traversenode;
            traversenode->prev = newnode;
        }
    }
    items->size++;
}

/* Removes the element of the list at the given index. Returns the value of the removed element in the list. */

void *removeDLL(dll *items, int index)
{
    int i;
    dllnode *traversenode;
    dllnode *temp;
    void *delval;
    if(items->size == 0) 
    {
        fprintf(stderr, "EMPTY LIST, list holds no values.");
        exit(-1);
    }
    if(index == 0)
    {
        temp = items->head;
        delval= temp->value;
        items->head = items->head->next;
        if(items->head != 0) items->head->prev = 0;
        if(sizeDLL(items) == 1) items->tail = 0;
        free(temp);
    }
    else if (index == sizeDLL(items)-1)
    {
        temp = items->tail;
        traversenode = temp->prev;
        traversenode->next = 0;
        delval = temp->value;
        items->tail = traversenode;
        free(temp);
    }
    else
    {
        if(index < sizeDLL(items)/2)
        {
            traversenode = items->head;
            for(i = 0; i < index; i++)
            {
                traversenode = traversenode->next;
            }
            temp = traversenode;
            delval = temp->value;
            traversenode->prev->next = traversenode->next;
            traversenode->next->prev = traversenode->prev;
            free(temp);
        }
        else
        {
            traversenode = items->tail;
            for(i = sizeDLL(items)-1; i > index; i--)
            {
                traversenode = traversenode->prev;
            }
            temp = traversenode;
            delval = temp->value;
            traversenode->next->prev = traversenode->prev;
            traversenode->prev->next = traversenode->next;
            free(temp);
        }
    }
    items->size--;
    return delval;
}

/* Combines two lists into a single list, Donor is set to be an empty list. */
void unionDLL(dll *recipient, dll *donor)
{
    if(recipient->head == 0 && donor->head != 0) recipient = donor;
    else if(donor->head == 0) return;
    recipient->tail->next = donor->head;
    donor->head->prev = recipient->tail;
    recipient->tail = donor->tail;
    recipient->size += donor->size;
    donor->head = donor->tail = 0;
    donor->size = 0;
}

/* Retrieves and returns the value of the node at the specified location */
void *getDLL(dll *items, int index)
{
    int i;
    dllnode *traversenode;
    if(items->size == 0) 
    {
        fprintf(stderr, "EMPTY LIST, value retrieval is not possible.");
        exit(-1);
    }
    if(index == 0) return items->head->value;
    else if (index == sizeDLL(items)-1)
    {
        return items->tail->value;
    }
    else
    {
        if(index < sizeDLL(items)/2)
        {
            traversenode = items->head;
            for(i = 0; i < index; i++)
            {
                traversenode = traversenode->next;
            }
        }
        else
        {
            traversenode = items->tail;
            for(i = sizeDLL(items)-1; i > index; i--)
            {
                traversenode = traversenode->prev;
            }
        }
        return traversenode->value;
    }
}

/* Returns the size of the DLL */
int sizeDLL(dll *items)
{
    return items->size;
}
/* Displays the DLL from front to back */
void displayDLL(FILE *fp, dll *items)
{
    dllnode *traversenode = items->head;
    fprintf(fp, "[");
    if(traversenode != 0)
    {
        while(traversenode->next != 0)
        {
            items->display(fp,traversenode->value);
            traversenode = traversenode->next;
            fprintf(fp,",");
        }
        items->display(fp,traversenode->value);
    }
    fprintf(fp, "]\n");
}
