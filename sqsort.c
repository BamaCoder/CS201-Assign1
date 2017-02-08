#include "integer.h"
#include "real.h"
#include "queue.h"
#include "string.h"
#include "stack.h"
#include "scanner.h"
#include "comparator.h"
#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char* argv[]) {
    //Comparator comp;
    Printer print;
    //Comparator intComparator = compareInteger;
    //Comparator realComparator = compareReal;
    //Comparator stringComparator = compareString; 
    if(argc > 1) {
      if(argv[1][0] == '-') {
        switch(argv[1][1]) {
          case 'v': 
            printf("Bryant M. Hall\n");
            return 0;
          case 'd':
            //comp = intComparator;
            print = displayInteger;
            break;
          case 'r':
            //comp = realComparator;
            print = displayReal;
            break;
          case 's':
            //comp = stringComparator;
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
      queue *input = readQueue(fp, print, argv[1][1]);
      displayQueue(stdout, input);
    }
    else {
      printf("Invalid input. Please input using the format 'sqsort -<flag> <optional filename>'.\n");
      return 1;
    }
  return 0;
}
