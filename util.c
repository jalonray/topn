#include <stdio.h>
#include <time.h>
#include <openssl/rand.h>

#include "util.h"
void default_printf_func(Term a)
{
	 int ai = (int)a;
	 printf("%d ",ai);
}	 
void printf_array(Term *p, int size,printf_func pf)  
{  
	 int i;  
	 printf_func cpf;
	 if(NULL == pf)
		  cpf = default_printf_func;
	 else
		  cpf = pf;
	 for(i = 0; i < size; i++){  
		  cpf(p[i]);
	 }  
	 printf("\r\n");
}  

Term **create_arrays(int array_count,int array_length)
{
	 int i;
	 int j;
	 int k;
	 Term **arrays;
	 arrays = malloc(sizeof(Term*) * array_count);
	 for(i = 0; i < array_count; i++){
		  arrays[i] = malloc(sizeof(Term) * array_length);
	 }
	 for(i = 0; i < array_count; i++){
		  srand(time(0));
		  for(j = 0; j < array_length; j++){
			   RAND_bytes((unsigned char *)&k, 4);
			   arrays[i][j] = (Term) abs(k % MAX_TO_SORT);
 		  }
	 }
	 return arrays;
}
Term **duplicate_arrays(Term **origin,int array_count,int array_length)
{
	 int i;
	 int j;
	 Term **arrays;
	 arrays = malloc(sizeof(Term*) * array_count);
	 for(i = 0; i < array_count; i++){
		  arrays[i] = malloc(sizeof(Term) * array_length);
	 }
	 for(i = 0; i < array_count; i++){
		  for(j = 0; j < array_length; j++){
			   arrays[i][j] = origin[i][j];
 		  }
	 }
	 return arrays;
}

void free_arrays(Term **arrays,int array_count)
{
	 int i;
	 for(i = 0; i < array_count; i++){
		  free(arrays[i]);
	 }
	 free(arrays);
}
	 
