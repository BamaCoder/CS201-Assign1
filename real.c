/* Implementation of real.c, rewritten based off
 * the implementation of integer.c written by
 * Dr. John Lusth, modified by Bryant Hall */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "real.h"


real *
newReal(double x)
    {
    real *p = malloc(sizeof(real));
    if (p == 0) 
    {
      fprintf(stderr, "out of memory\n");
      exit(-1);
    }
    p->value = x;
    return p;
    }

double
getReal(real *v)
    {
    return v->value;
    }

double 
setReal(real *v,double x)
    {
    double old = v->value;
    v->value = x;
    return old;
    }

void 
displayReal(FILE *fp,void *v)
    {
    fprintf(fp,"%f",getReal((real *) v));
    }

void
freeReal(real *v)
    {
    free(v);
    }
