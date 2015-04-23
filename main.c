#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define WHITE	0 /* unvisited node */
#define BLACK	1 /* node is part of a negative cycle*/
#define GREY	2 /* temporary for algorith iterations */
#define INF 	2147000000
#define BIG		2000000000
#define NONE	-1

typedef struct vertex{
	int value, dist, prev, color;
	list_t *adj;
} vertex_t;


void BBFS(vertex_t *vertices, int source){	
	list_t *queue = list_init();
	list_node_t *node;
	int v, w;

	list_push(queue, source, 0);
	vertices[source].color = GREY;
	
	while (!list_empty(queue)){
		v = list_peek(queue)->value;
		list_pop(queue);
		for (node=vertices[v].adj->head; node!=NULL ; node=node->next){
			w = node->value;
			if (!vertices[w].color){
				vertices[w].color = GREY;
				list_push(queue, w, 0);
			}
		}
		vertices[v].color = BLACK;
	}
	
	list_destroy(queue);
}

void BBellmanFord(vertex_t *vertices, int source, int N){
	list_node_t *node;
	int i, j, changed;
	
	vertices[source].dist = vertices[source].prev = 0;
	
	for (i=0; i<N-1; i++){ /* relaxation iterations */
		changed = 0;
		for (j=0; j<N; j++) for (node=vertices[j].adj->head; node!=NULL; node=node->next)
			if (vertices[j].dist+node->weight < vertices[node->value].dist){
				vertices[node->value].dist = vertices[j].dist+node->weight;
				vertices[node->value].prev = j;
				changed = 1;
			}
		if (!changed) break;
	}

	for (j=0; j<N; j++) /* negative cycles iteration, finds cycle root  */
		for (node=vertices[j].adj->head; node!=NULL; node=node->next)
			if (vertices[j].dist+node->weight < vertices[node->value].dist)
				BBFS(vertices, j);
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
		list_push(local[u-1].adj, v-1, w);
	}
	
	for (j=0; j<N; j++){ /* vertices init */
		local[j].value = j;
		local[j].dist = INF;
		local[j].prev = NONE;
		local[j].color = WHITE;
	}

	BBellmanFord(local, HQ-1, N);
	
	/* OUTPUT */
	for (j=0; j<N; j++){
		if ((local[j].prev==NONE) || local[j].dist>=BIG) /* Unlinkable */
			printf("U\n");
		else if (local[j].color==BLACK) /* Indeterminable */
			printf("I\n");
		else
			printf("%d\n", local[j].dist); /* Calculable */
	}

	/* FREE MEMORY */
	for(j=0; j<N; j++) list_destroy(local[j].adj);
	free(local);

	return 0;
}