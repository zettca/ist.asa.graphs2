#include <stdio.h>
#include <stdlib.h>
#include "list.h"


int main(int argc, char const *argv[]){
	int N, C, HQ;	// Locals, Paths/Costs, Headquarters
	int i, u, v, w;	

	/* INPUT */
	scanf("%d %d", &N, &C);
	scanf("%d", &HQ);
	
	for(i=0; i<C; i++){	// spot, spot, loss
		scanf("%d %d %d", &u, &v, &w);
	}
	

	// GRAPHING STUFFS

	
	/* OUTPUT */
	for (i=0; i<M; i++)
		printf("%d\n", i); 
	
	return 0;
}