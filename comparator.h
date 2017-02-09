#include <stdio.h>

#ifndef __COMPARATOR_INCLUDED__
#define __COMPARATOR_INCLUDED__

typedef int (*Comparator)(void*,void*);
typedef void (*Printer) (FILE*,void*);

extern int intComparator(void *,void *);
extern int realComparator(void*, void*);
extern int stringComparator(void*, void*);

#endif
