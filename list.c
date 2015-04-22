#include <stdlib.h>
#include "list.h"

list_t *list_init(){
	list_t *list = (list_t*) malloc(sizeof(list_t));
	list->head = (list->tail = NULL);
	return list;
}

int list_empty(list_t *list){
	return (list->head == NULL);
}

void list_push(list_t *list, int value, int weight){
	list_node_t *node;
	node = (list_node_t*) malloc(sizeof(list_node_t));
	node->value = value;
	node->weight = weight;
	node->next = NULL;

	if (list_empty(list)){
		list->head = (list->tail = node);
	} else{
		list->tail->next = node;
		list->tail = list->tail->next;
	}
}

void list_pop(list_t *list){
	list_node_t *temp = list->head;
	list->head = list->head->next;
	free(temp);
}

list_node_t *list_peek(list_t *list){
	return list->head;
}

void list_destroy(list_t *list){
	while(list->head != NULL)
		list_pop(list);
	free(list);
}