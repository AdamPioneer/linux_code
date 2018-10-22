#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
struct test_node {
		struct list list;
		int value;
	};
int main(int argc, char *argv[])
{
	int i = 0;
	

	struct list list_head = {0,0};
	list_init(&list_head);
	
	struct test_node *node1 = (struct test_node*) malloc(sizeof(struct test_node));
	node1->value = 1;
	struct test_node *node2 = (struct test_node*) malloc(sizeof(struct test_node));
	node2->value = 2;
	struct test_node *node3 = (struct test_node*) malloc(sizeof(struct test_node));
	node3->value = 3;
	
	list_add(&list_head, node1);
	list_insert(&list_head, node2);
	list_insert(&list_head, node3);

	struct list *pos;
	struct test_node *nod;
	list_for_each(pos, &list_head) {
		nod = container_of(pos, struct test_node, list);	
		printf("i = %d, value = %d \n", i, nod->value);
		i++;
	}	
	
	free(node1);
	free(node2);
	free(node3);

	return 0;
}
