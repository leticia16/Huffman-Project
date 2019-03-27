#include <stdio.h>
#include <stdlib.h>
#include "libs/hufman_tree.h"

NODE create_node(){
	NODE htree = (NODE) malloc(sizeof(Node));
	htree->left = NULL;
	htree->right = NULL;
	htree->frequency = 0;
	return htree;
} 

// node *create_nodezinho(){
// 	node *nodezinho = (node*) malloc(sizeof(node));
// 	// htree->left = NULL;
// 	// htree->right = NULL;
// 	// htree->frequency = 0;
// 	nodezinho -> value = create_node();
// 	nodezinho -> next = NULL;
// 	return htree;
// } 

NODE create_node_h(NODE n1, NODE n2){
	NODE htree = (NODE) malloc(sizeof(Node));
	htree->left = n1;
	htree->right = n2;
	htree->frequency = n1->frequency + n2->frequency;
	htree->symbol = '*';
	return htree;
}

void** create_htree_array(int size){
	void** array = (void**) malloc(size * sizeof(void*));
	return array;
}

short compare_nodes(void* m, void* n){
	NODE a, b;
	a = (NODE) m;
	b = (NODE) n;
	if (a->frequency < b->frequency) return 1;
	return 0;
}

int* create_frequency_array(char* arq, FILE *file) {

	int* freq = (int*)calloc(MAX_SIZE, sizeof(int));
	Byte c;
	while (fscanf(file, "%c", &c) != EOF) {
		freq[c] += 1;
	}
	rewind(file);
	return freq;
}

// void printing_frequency_array(int *array)
// {
// 	int i;
// 	for (i = 0; i < MAX_SIZE; i++)
// 	{
// 		if (array[i])
// 		{
// 			printf("%c %d\n", i, array[i]);
// 		}
// 	}
// }

// HEAP heap_frequency(int* array) {
// 	HEAP heap = create_heap();
// 	NODE aux;
// 	int i, count = 0;

// 	for (i = 255; i >= 0; i--) {
// 		if (array[i]) {
// 			aux = create_node();
// 			aux->symbol = i;
// 			aux->frequency = array[i];
// 			enqueue(heap, aux);
// 		}
// 	}
// 	return heap;
// }

NODE construct_h_tree(HEAP heap, NODE root){
	if (heap->size == 1){
		NODE aux = create_node_h(dequeue(heap), NULL);
		aux->symbol = '*';
		enqueue(heap,aux);
	}
	NODE smaller1, smaller2;
	while (heap->size > 1){
		smaller1 = dequeue(heap);
		smaller2 = dequeue(heap);
		enqueue(heap,create_node_h(smaller1,smaller2));
	}
	return dequeue(heap);
}

