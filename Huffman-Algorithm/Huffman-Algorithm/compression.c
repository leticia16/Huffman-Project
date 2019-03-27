#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libs/hufman_tree.h"
#include "libs/hash.h"
#include "libs/priority_queue.h"

typedef unsigned short USHORT;

int is_bit_i_set_byte(Byte b, int i){
	Byte mask = 1 << i;
	return mask & b;
}

Byte set_bit_i_byte(Byte b, int i){
	Byte mask = 1 << i;
	return mask | b;
}

int is_leaf(NODE node) {
	return  node->left == NULL && node->right == NULL;
}

void write_header(FILE* compressedFile, Byte trash, USHORT sizeTree, Byte *treeString)
{
	// printf("PRINT DA ARVORE NA write_header:\n");
	int i;
	// for (i = 15; i >= 0; i--){
	// 	if (is_bit_i_set_byte(sizeTree,i)) printf("1");
	// 	else printf("0");
	// }
	// printf("\n");
	Byte aux = trash << 5;;
	Byte firstBytes[2] = {0};
	// trash <<= 5;
	// firstBytes[0] = trash;
	for(i = 12; i>=0; i--)
	{
		if(i>7)
		{
			firstBytes[0] <<= 1;
			if(sizeTree >> i & 1)
			{
				firstBytes[0]++;
			}
		}
		else
		{ 
			firstBytes[1] <<= 1;
			if(sizeTree >> i & 1)
			{
				firstBytes[1]++;
			}

		}
	}
	// for (i = 15; i >= 8; i--){
	// 	if (is_bit_i_set_byte(sizeTree,i))
	// 	{
	// 		aux++;
	// 	} 
	// 	aux <<= 1;
	// }
	firstBytes[0] |= aux;
	firstBytes[1] = sizeTree;
	fprintf(compressedFile, "%c", firstBytes[0]);
	fprintf(compressedFile, "%c", firstBytes[1]);
	printf("%d %d\n",firstBytes[0], firstBytes[1]);
	for (i = 0; i < strlen(treeString); i++){
		fprintf(compressedFile, "%c", treeString[i]);
	}
}

NODE build_tree(P_QUEUE *huff_p_queue) {
	// printf("size%d\n",huff_p_queue->size);
    if(huff_p_queue->size == 1)
     { //Se só tiver 1 nó na fila
    	node *aux1 = dequeue(huff_p_queue, huff_p_queue->head->value->symbol);
        lli frequency = aux1->value->frequency; // usamos long long int pq a frequecia pode ser muito grande
        Byte id_dad = '*';

        NODE huff_node = create_node();
    	huff_node -> frequency = frequency;
    	huff_node -> symbol = id_dad;
    	huff_node -> left = aux1->value;
    	huff_node -> right = NULL;

    	enqueue(huff_p_queue,huff_node);

    } while(huff_p_queue->size > 1) { // Para quando resta apenas 1 nó na fila
    	node *aux1 = dequeue(huff_p_queue, huff_p_queue->head->value->symbol);
    	node *aux2 = dequeue(huff_p_queue, huff_p_queue->head->value->symbol); 
    	// printf("%d %d\n", aux1->value->symbol,aux2->value->symbol); 
    	// printf("aux1 = %c\n",aux1 -> head -> value -> symbol);
    	// printf("aux2 = %c\n",aux1 -> head -> value -> symbol);     
    	lli frequency = aux1->value->frequency + aux2->value->frequency;
    	// printf("%lld\n",frequency);
    	Byte id_dad = '*';

    	NODE huff_node = create_node();
    	huff_node -> frequency = frequency;
    	huff_node -> symbol = id_dad;
    	huff_node -> left = aux1->value;
    	huff_node -> right = aux2->value;
    	enqueue(huff_p_queue,huff_node);
    }
    return huff_p_queue->head->value;
}

void get_size_tree(NODE node, int *size, Byte *treeString)
{
	if(node == NULL)
	{
		return;
	}
    treeString[*size] = node->symbol; // Atribui cada caractere à posição size do array
    if((treeString[(*size)] == '*' || treeString[(*size)] == '\\') && is_leaf(node))
    { 
    	Byte aux;
    	aux = treeString[*size];
    	treeString[*size] = '\\';
    	treeString[++(*size)] = aux; 
    }
	++(*size); // ponteiro que soma o tamanho da árvore
	get_size_tree(node->left, size,treeString);
	get_size_tree(node->right, size, treeString);
}

void compress(FILE *compressedFile, FILE *inputFile, HASH *hash, Byte trashSize)
{
	int i = 0;
	Byte ch, bitThatIsBeingSet = 0, totalBitsSet = 0;
	USHORT binarySize = 0, binary = 0;
	while ((fscanf(inputFile, "%c", &ch)) != EOF){
		binarySize = hash->table[ch]->size;
		binary = hash->table[ch]->binary;
		for (i = binarySize - 1; i >= 0; i--){
			if (binary >> i & 1){ //verifica se o ultimo bit do byte eh 1
				bitThatIsBeingSet++;
				// printf("1");
			}
			// else printf("0");
			if (totalBitsSet == 7){ //verifica se ja foi preenchido um byte completo
				fprintf(compressedFile, "%c", bitThatIsBeingSet);
				totalBitsSet = -1;
				bitThatIsBeingSet = 0;
				// puts("");
			}
			bitThatIsBeingSet <<= 1;
			totalBitsSet++;
		}
	}
	bitThatIsBeingSet >>= 1; //Correção do loop
	// if (trashSize != 0){
	// }
	bitThatIsBeingSet <<= trashSize;
	fprintf(compressedFile, "%c", bitThatIsBeingSet);
	// printf("asd\n");
}