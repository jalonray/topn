#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "heap.h"
#include "util.h"
#include "heap_topn.h"
#include "simple_topn.h" 

int main(void)
{
	 int array_length = 2000;
	 int array_count  = 200;
	 int topn = 50;
	 int i;
	 Term **arrays = create_arrays(array_count,array_length);
	 Term *hresult = (Term *)malloc(sizeof(Term) * topn);
	 Term *sresult = (Term *)malloc(sizeof(Term) * topn);
	 Heap *heap = (Heap *)malloc(sizeof(Heap));
	 struct timeval hstart,hend;
	 struct timeval sstart,send;
	 unsigned long diff1,diff2;
	 for(i = 0; i < array_count; i++){
		  init_heap(heap,arrays[i],array_length,NULL);
		  sort_heap(heap);
	 }
	 printf("start.....\r\n");
//	 for(i = 0; i < array_count; i++){
//		  printf_array(arrays[i],array_length,NULL);
//	 }


	 Term **dup = duplicate_arrays(arrays,array_count,array_length);

	 gettimeofday(&sstart,NULL);
	 simple_topn(arrays,array_count,array_length,sresult,topn);
	 gettimeofday(&send,NULL);

	 diff1 = send.tv_sec - sstart.tv_sec;
	 diff2 = send.tv_usec - sstart.tv_usec;
	 printf("simple sort:%lu,%lu\r\n",diff1,diff2);
	 printf_array(sresult,topn,NULL);

	 gettimeofday(&hstart,NULL);	  
	 heap_topn(dup,array_count,array_length,hresult,topn);
	 gettimeofday(&hend,NULL);

	 diff1 = hend.tv_sec - hstart.tv_sec;
	 diff2 = hend.tv_usec - hstart.tv_usec;
	 printf("heap sort:%lu,%lu\r\n",diff1,diff2);
	 printf_array(hresult,topn,NULL);


	 free_arrays(dup,array_count);
	 free_arrays(arrays,array_count);
	 free(hresult);
	 free(sresult);
	 return 0;
	 
}
