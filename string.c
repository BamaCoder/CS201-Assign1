/* String.c implementation, written by Bryant Hall */

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <string.h>

void displayString(FILE * fp,void *v) {
  fprintf(fp, "\"%s\"",(char*)v);
}

