#include <stdio.h>
#include "heap.h"
void printf_heap(Heap *hp)
{
	 printf("heap length: %d\r\n",hp->length);
	 printf("heap max index: %d\r\n",hp->max_index);
	 printf("heap array pointer: %p\r\n",hp->array);
	 printf("heap comparator pointer: %p\r\n",hp->cmp);
}

int default_comparator(Term a ,Term b)
{
	 int ai = (int)a;
	 int bi = (int)b;
	 if (ai > bi)
		  return 1;
	 else if(ai < bi)
		  return -1;
	 return 0;
}

void max_heap(Heap *hp, int node)  
{  
	 unsigned int l = (node + 1) << 1 - 1;  
	 unsigned int r = (node + 1) << 1 ; 
	 unsigned int largest = 0;  
	 int max_index = hp->max_index;  
	 comparator cmp = hp->cmp;
	 if(l <= max_index && cmp(hp->array[l],hp->array[node]) > 0 )
		  largest = l ;  
	 else  
		  largest = node;  
      
	 if(r <= max_index && cmp(hp->array[r],hp->array[largest])> 0)
		  largest = r ;

	 if(largest != node){     
		  Term tmp ;  
		  tmp = hp->array[largest];  
		  hp->array[largest] = hp->array[node];  
		  hp->array[node] = tmp;            
		  max_heap(hp,largest);  
	 }  
      
}  

void init_heap(Heap *heap,Term *array, int length, comparator cmp)  
{  
	 heap->array = array;  
	 heap->max_index = length - 1;  
	 heap->length = length;
	 if(NULL == cmp)
		  heap->cmp = default_comparator;
	 else
		  heap->cmp = cmp;
}  

void sort_heap(Heap *hp)  
{  
	 int i;
	 int length = hp->max_index;
	 for(i = length; i >= 0; i--)   
		  max_heap(hp,i);  
      
}  

	 
