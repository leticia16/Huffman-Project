#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hufman_tree.h"


typedef long long int lli;
typedef struct p_queue P_QUEUE;
typedef unsigned short USHORT;
typedef struct node node;
	
	struct node {
	NODE value;
	node *next;
};
	
struct p_queue {
	node *head;
	lli size;
};



// node *create_nodezinho()
// NODE create_node(NODE huff_node);
/*
 *
 */

P_QUEUE *create_p_queue();
/*
 *
 */

USHORT p_queue_is_empty(P_QUEUE *p_queue);
/*
 *
 */

void enqueue(P_QUEUE *p_queue, NODE huff_node);
/*
 *
 */

void print_p_queue(P_QUEUE *p_queue, void (*print)(DATATYPE));
/*
 *
 */

node* dequeue(P_QUEUE *p_queue, void* key);
/*
 *
 */

#endif