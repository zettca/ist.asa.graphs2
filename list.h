#include <stdlib.h>

typedef struct list_node {
	int value, weight;
	struct list_node *next;
} list_node_t;

typedef struct {
	list_node_t *head, *tail;
} list_t;

list_t *list_init();
int list_empty(list_t *list);
void list_push(list_t *list, int value, int weight);
void list_pop(list_t *list);
list_node_t *list_peek(list_t *list);
void list_destroy(list_t *list);