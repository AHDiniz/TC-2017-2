#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmpfunc (const void *, const void *);

void main(){

	int i;
	int v[10] = {43,89,25,7,11,45,62,5};

	// Impressao para teste
	for(i = 0 ; i < 8 ; i++)
		printf("%d ", v[i]);

	printf("\n");
	
	qsort(v, 8, sizeof(int), cmpfunc);

	// Impressao para teste
	for(i = 0 ; i < 8 ; i++)
		printf("%d ", v[i]);

	printf("\n");

	
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
