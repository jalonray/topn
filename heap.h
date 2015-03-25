#include "term.h"

typedef int (*comparator)(Term, Term);
typedef struct heap_{  
	 Term *array;      
	 int max_index; 
	 int length;
	 comparator cmp;
      
}Heap;  
void init_heap(Heap *heap,Term *array, int length,comparator cmp);
void sort_heap(Heap *hp);
void printf_heap(Heap* hp);
