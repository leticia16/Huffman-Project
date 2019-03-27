#include "priority_queue.h"
#include "hufman_tree.h"

P_QUEUE *create_p_queue() {
	P_QUEUE *huff_p_queue = (P_QUEUE*) malloc(sizeof(P_QUEUE));
	huff_p_queue->head = NULL;
	huff_p_queue->size = 0;
	return huff_p_queue;
}

USHORT p_queue_is_empty(P_QUEUE *huff_p_queue) {
	return huff_p_queue->size == 0;
}	

void enqueue(P_QUEUE *huff_p_queue, NODE huff_node) {	
	node *new_node = (node*) malloc(sizeof(node));
	new_node -> value = create_node();
	new_node -> next = NULL;
	new_node -> value = huff_node;
	if(p_queue_is_empty(huff_p_queue)) {
		huff_p_queue->head = new_node;
		huff_p_queue->size++;
		return;
	}
	huff_p_queue->size++;
	node *current = huff_p_queue->head, *prev = NULL;

	
	while(current != NULL && current->value->frequency < new_node->value->frequency) {
			prev = current;
			current = current->next;
	}

	if(prev == NULL) {
		new_node->next = huff_p_queue->head;
		huff_p_queue->head = new_node;
		return;
	}
	prev->next = new_node;
	new_node->next = current;
}

// void print_p_queue(P_QUEUE *huff_p_queue, void (*print)(DATATYPE)) {
// 	NODE current = huff_p_queue->head;
// 	while(current != NULL) {
// 		printf("(");
// 		(*print)(current->value->key);
// 		printf(",%lld)", current->value->frequency);
// 		current = current->next;
// 	}
// 	puts("");
// }

node *dequeue(P_QUEUE *huff_p_queue, void* key) {
	node *current = huff_p_queue->head;
	node *prev = NULL;	
	while(current != NULL && !(current->value->symbol == key)) {
		prev = current;
		current = current->next;
	}
	if(prev != NULL) {
		prev->next = current->next;
	} else {
		huff_p_queue->head = current->next;
	}
	huff_p_queue->size--;
	current->next = NULL;
	return current;
}