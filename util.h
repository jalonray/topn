#include "term.h"

#define MAX_TO_SORT 1000

typedef void (*printf_func)(Term);

void printf_array(Term *p, int size,printf_func pf);
Term **create_arrays(int array_count,int array_length);
Term **duplicate_arrays(Term** origin,int array_count,int array_length);
void free_arrays(Term **arrays,int array_count);

