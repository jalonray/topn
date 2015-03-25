#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "heap.h"

typedef struct item_ {
	 int id;
	 int pos;
	 Term term;
}Item;

int printf_item(Term a)
{
	 Item* ai = (Item*)a;
	 int d = (int)ai->term;
	 printf("%d ",d);
}
int comparator_func(Term a,Term b)
{
	 Item *ai = (Item *)a;
	 Item *bi = (Item *)b;
	 if ((int)ai->term > (int)bi->term)
		  return 1;
	 else if((int)ai->term < (int)bi->term)
		  return -1;
	 return 0;
}
Item *alloc_item(int id,int pos,Term term)
{
	 Item *item = malloc(sizeof(Item));
	 item->id = id;
	 item->pos = pos;
	 item->term = term;
	 return item;
}

void free_item(Item *item)
{
	 free(item);
}

Term get_term(Term *array,int pos)
{
	 return array[pos];
}

void heap_topn(Term **arrays,int array_count,int array_length,Term* result,int topn)
{
	 int i,j = array_count;
	 Item **items = malloc(sizeof(Item*) *(topn + array_count));
	 Term term;
	 Item *item;
	 Heap* heap = malloc(sizeof(Heap));
	 for(i = 0; i < array_count; i++){
		  term = get_term(arrays[i],0);
		  items[i] = alloc_item(i,0,term);
	 }
	 init_heap(heap,(Term*)items,array_count,comparator_func);
	 sort_heap(heap);
	 while((j - array_count) < topn){
		  items[j] = heap->array[0];
		  item = items[j];
		  j++;
		  term = get_term(arrays[item->id],item->pos + 1);
		  heap->array[0] = alloc_item(item->id,item->pos + 1,term);
		  if(j - array_count >= topn){
			   break;
		  }
		  sort_heap(heap);	 
	 }
	 free(heap);
	 for(i = array_count; i < (array_count + topn); i++){
		  result[i - array_count] = items[i]->term;
		  free(items[i]);
	 }
	 for(i = 0; i < array_count; i++){
		  free(items[i]);
	 }
	 free(items);
	 
}
