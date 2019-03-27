#ifndef _HUFMAN_TREE_H_
#define _HUFMAN_TREE_H_

#define MAX_SIZE 256

#include <stdio.h>

typedef unsigned char Byte;

typedef struct h_tree{
	void* symbol;
	int frequency;
	struct h_tree *left;
	struct h_tree *right;
} Node;

typedef Node* NODE;

typedef struct heap {
    int size;
    NODE data[257];
} Heap;

typedef Heap* HEAP;


NODE create_node();

// node *create_nodezinho();

// HEAP heap_frequency(int* array);

void** create_htree_array(int size);

short compare_nodes(void* m, void* n);

int* create_frequency_array(char *arq, FILE* file);

NODE construct_h_tree(HEAP heap, NODE root);

#endif
