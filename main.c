#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define FALSE	0
#define TRUE	1
#define TREE	2
#define INF 	2147000000
#define BIG		2000000000
#define NONE	-1

typedef struct vertex{
	int value, dist, prev, loop;
	list_t *adj;
} vertex_t;


void BBFS(vertex_t *vertices, int source){	
	list_t *queue = list_init();
	list_node_t *node;
	int v, w;

	list_push(queue, source, 0);
	vertices[source-1].loop = TREE;
	
	while (!list_empty(queue)){
		v = list_peek(queue)->value;
		list_pop(queue);
		for (node=vertices[v-1].adj->head; node!=NULL ; node=node->next ){
			w = node->value;
			if (!vertices[w-1].loop){
				vertices[w-1].loop = TREE;
				list_push(queue, w, 0);
			}
		}
		vertices[v-1].loop = TRUE;
	}
	
	list_destroy(queue);
}

void BBellmanFord(vertex_t *vertices, int source, int N){
	int i, j, v;
	list_node_t *node;
	
	for (j=0; j<N; j++){ /* vertices init */
		vertices[j].value = j+1;
		vertices[j].dist = INF;
		vertices[j].prev = NONE;
		vertices[j].loop = FALSE;
	}
	vertices[source-1].dist = 0;
	vertices[source-1].prev = 0;
	

	for (i=0; i<N-1; i++) /* relaxation iterations */
		for (j=0; j<N; j++)
			for (node=vertices[j].adj->head; node!=NULL; node=node->next)
				if (vertices[j].dist+node->weight < vertices[node->value-1].dist){
					vertices[node->value-1].dist = vertices[j].dist+node->weight;
					vertices[node->value-1].prev = j;
				}

	for (j=0; j<N; j++) /* negative cycles iteration, finds cycle root  */
		for (node=vertices[j].adj->head; node!=NULL; node=node->next)
			if (vertices[j].dist+node->weight < vertices[node->value-1].dist)
				BBFS(vertices, j+1);

}


int main(int argc, char const *argv[]){
	int N=2, C=2, HQ=1;	/* Locals, Paths/Costs, Headquarters */
	int j, u, v, w;
	
	vertex_t *local;

	/* INPUT */
	scanf("%d %d %d", &N, &C, &HQ);
	
	local = (vertex_t*) malloc(N*sizeof(vertex_t));
	for (j=0; j<N; j++) local[j].adj = list_init();
	
	for(j=0; j<C; j++){	/* spot, spot, loss */
		scanf("%d %d %d", &u, &v, &w);
		list_push(local[u-1].adj, v, w);
	}


	BBellmanFord(local, HQ, N);
	
	
	/* OUTPUT */
	/* TOO MANY Ns, should be Is */
	/* TOO MANY Is, should be Us */
	for (j=0; j<N; j++){
		if ((local[j].prev==NONE) || local[j].dist>=BIG){ /* Unlinkable */
			printf("U\n");
		} else if (local[j].loop==TRUE){ /* Indeterminable */
			printf("I\n");
		} else {
			printf("%d\n", local[j].dist);
		}
	}

	/* FREE MEMORY */
	for(j=0; j<N; j++) list_destroy(local[j].adj);
	free(local);

	return 0;
}