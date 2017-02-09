/* Sqsort.c - reads in and implements a sorting mechanism using two queues and a stack, printing each iteration through the stack
 *
 * Code written, implemented, and tested by Bryant M. Hall, Senior at the University of Alabama 
 * Credit is given where credit is due. Copyright 2017 */ 

#include "integer.h"
#include "real.h"
#include "queue.h"
#include "string.h"
#include "stack.h"
#include "scanner.h"
#include "comparator.h"
#include <stdio.h>
#include <stdlib.h>


/* Function that reads in queue from designated file pointer location, ignoring whitespace, utilizes scanner.c and scanner.h 
 * written by John C. Lusth */
queue *readQueue(FILE *fp, Printer p, char type) {
  queue *input = newQueue(p);
  if(type == 'd') {
    int val = readInt(fp);
    while(!feof(fp)) {
      enqueue(input, newInteger(val));
      val = readInt(fp);
    }
  }
  else if(type == 's') {
    char* val = readString(fp);
    while(!feof(fp)) {
      enqueue(input, val);
      val = readString(fp);
    }
  }
  else if(type == 'r') {
    double val = readReal(fp);
    while(!feof(fp)) {
      enqueue(input, newReal(val));
      val = readReal(fp);
    }
  }
  return input;
}


/* Recursive function that sorts using an input queue using two queues and a stack for arbitrary data types*/
void sortQueue(queue* input, Comparator comp, Printer disp) {
  queue *output = newQueue(disp);
  stack *s = newStack(disp);
  int sorted = 1; // flag for whether to keep recursing or not (checks if sorted)
  void *temp;
  displayQueue(stdout, input);
  fprintf(stdout, "\n");
  while(sizeQueue(input) > 0 || sizeStack(s) > 0) { // execute until both input queue and stack are empty
    if(sizeStack(s) > 0 && (sizeQueue(input) == 0 || comp(peekQueue(input), peekStack(s)) <= 0)) enqueue(output,pop(s)); // pop from stack, enqueue output
    else {
      temp = dequeue(input);
      if(sizeQueue(input) == 0 || comp(temp,peekQueue(input)) > 0) enqueue(output,temp); // dequeue from input, enqueue output
      else { // dequeue from input, push stack
        push(s, temp);  
        sorted = 0;
      }
    }
  }
  if(sorted) {
    return;
  }
  else {
    free(input);  // Clear memory of empty stacks and queues
    free(s);
    sortQueue(output, comp, disp);
  }
}

int main(int argc, char* argv[]) {
    Comparator comp;
    Printer print;
    if(argc > 1) {
      if(argv[1][0] == '-') {
        switch(argv[1][1]) {
          case 'v': // Prints Name
            fprintf(stdout, "Bryant M. Hall\n");
            return 0;
          case 'd': // Integer based
            comp = intComparator;
            print = displayInteger;
            break;
          case 'r': // Real number based
            comp = realComparator;
            print = displayReal;
            break;
          case 's': // String based 
            comp = stringComparator;
            print = displayString;
            break;
          default:
            printf("unknown flag '%s', valid flags are -d, -r, -s, and -v\n", argv[1]);
            exit(1);
        }
      }
      FILE *fp;
      if(argc == 2) {
        fp = stdin;
      }
      else if (argc == 3) {
        fp = fopen(argv[2], "r");
      }
      queue *input = readQueue(fp, print, argv[1][1]); // Reads in Queue
      if(sizeQueue(input) == 0) {
        displayQueue(stdout, input);
        fprintf(stdout, "\n");
      }
      sortQueue(input, comp, print);                   // Sorts and Prints Queue
    }
    else {
      printf("Invalid input. Please input using the format 'sqsort -<flag> <optional filename>'.\n");
      return 1;
    }
  return 0;
}
