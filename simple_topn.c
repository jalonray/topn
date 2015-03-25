#include <stdio.h>
#include <stdlib.h>
#include "util.h"

typedef struct s_item_ {
	 int id;
	 int pos;
	 int apos;
	 Term term;
}SItem;



SItem *s_alloc_item(int id,int pos,Term term)
{
	 SItem *item = malloc(sizeof(SItem));
	 item->id = id;
	 item->pos = pos;
	 item->term = term;
	 return item;
}

int binary_search(Term *array,Term want,int start,int end)
{
	 int half = (end - start) / 2 + start;
	 int new_start = start,new_end = end;
	 int big = 0;
	 Term in = array[half];
	 int ini = (int)in;
	 int wanti = (int)want;
	 while(1){
		  if(want > ini && new_end >= new_start && big != 1 ){
			   new_end = half - 1;
			   half = (new_end - new_start ) / 2 + new_start;
			   in = array[half];
			   ini = (int)in;
		  }else if(want == ini){
			   return half;
		  }else if(want < ini ){
			   new_start = half + 1;
			   half = (new_end - new_start) / 2 + new_start;
			   in = array[half];
			   ini = (int)in;
			   big = 1;
		  }else{
			   break;
		  }
	 }
	 half = new_start;
	 big = 0;
	 while(half <= (new_end + 1) ){
		  in = array[half];
		  ini = (int)in;
		  if(in >= want){
			   half++;
			   big = 1;
		  }else if(in < want){
			   if(big == 1){
					half--;
					break;
			   }else{
					half--;
					big = -1;
			   }
		  }
	 }
	 return half;
}


void s_free_item(SItem *item)
{
	 free(item);
}

Term s_get_term(Term *array,int pos)
{
	 return array[pos];
}

void simple_topn(Term **arrays,int array_count,int array_length,Term* result,int topn)
{
	 int i,j = 0,k = 0,m = 0,max_index = array_count * 2;
	 SItem **items = malloc(sizeof(SItem*) * max_index);
	 Term term;
	 SItem* first  = NULL;
	 SItem* second = NULL;

	 term = s_get_term(arrays[0],0);
	 items[0] = s_alloc_item(0,0,term);
	 items[0]->apos = 0;
	 first = items[0];
	 int f,s;
	 
	 for(i = 1; i < array_count; i++){
		  term = s_get_term(arrays[i],0);
		  items[i] = s_alloc_item(i,0,term);
		  items[i]->apos = i;
		  if((int)first->term < term){
			   second = first;
			   first = items[i];
		  } else if(second == NULL){
			   second = items[i];
		  }else if((int)second->term < term){
			   second = items[i];
		  }
			   
	 }

	 for(i = array_count; i < max_index; i++){
		  term = s_get_term(arrays[i - array_count],topn -1);
		  items[i] = s_alloc_item(i - array_count,topn - 1,term);
		  items[i]->apos = i;
		  if((int)second->term < term){
			   second = items[i];
		  }
	 }
	 //第一种情况所有的在一个队列里面
	 if(first->id == second->id){
		  for(i = 0; i < topn; i++){
			   result[i] = s_get_term(arrays[first->id],i);
		  }
	 }else{
		  //第二种情况，分段了
		  while(j < topn ){
			   k = binary_search(arrays[first->id],second->term,first->pos,topn);
			   m = k - first->pos + 1;
			   for(i = 0; i < m && j < topn ; i++){
					result[j] = s_get_term(arrays[first->id],first->pos + i);
					j++;
			   }
			   term = s_get_term(arrays[first->id],k + 1);
			   m = first->apos;
			   items[first->apos] = s_alloc_item(first->id,k + 1,term);
			   items[first->apos]->apos = first->apos;
			   free(first);
			   first = second;
			   second = items[m];
			   for(i = 0 ; i < max_index; i++){
					if((items[i] != first) &&( (int)second->term < (int)items[i]->term )){
						 second = items[i];
					}
			   }
		  }
		  
	 }
	 for(i = 0; i < max_index ; i++){
		  if(NULL != items[i]) {
			   free(items[i]);
		  }
	 }
	 free(items);
}
