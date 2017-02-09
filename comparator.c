#include <stdio.h>
#include <string.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "comparator.h"


int intComparator(void*v, void*w) {
  return ((integer *) v)->value - ((integer *) w)->value;
}

int realComparator(void*v, void*w) {
  if(((real *) v)->value > ((real *) w)->value) return 1;
  else if (((real *) v)->value == ((real *) w)->value) return 0;
  else return -1;
}

int stringComparator(void *v, void *w) {
  return strcmp(v,w);
}
