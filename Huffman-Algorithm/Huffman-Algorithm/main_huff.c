#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/compression.h"
#include "libs/hash.h"
#include "libs/hufman_tree.h"
#include "libs/decompress.h"
#include "libs/priority_queue.h"
#define MAX_SIZE 256
typedef unsigned char Byte;


void preOrder_tree(NODE node)
{
	if(node == NULL)
	{ 
		return;
	}
	printf("root = %d\n", node->symbol);
	preOrder_tree(node->left);
	preOrder_tree(node->right);
}

int main()
{
	int i = 0;
	Byte input[100];
	printf("Digite o nome do arquivo que voce gostaria de abrir: ");
	scanf("%s", input);
	// printf("\n");
	// FILE *inputFile = fopen(input,"rb");
	// int *frequency = create_frequency_array(input, inputFile);
	// P_QUEUE *p_queue = create_p_queue();

	// for(i = 0; i < 256; i++)
	// {	
	// 	if(frequency[i])
	// 	{
	// 		NODE huff_node = create_node();
	// 		huff_node -> frequency = frequency[i];
	// 		huff_node -> symbol = (void*)i;
	// 		enqueue(p_queue,huff_node);
	// 	}
	// }
	// node *aux = p_queue->head;
	// // while(aux != NULL)
	// // {
	// // 	printf("%d\n ",aux -> value -> symbol);
	// // 	aux = aux -> next;
	// // }
	// NODE root = build_tree(p_queue);
	// // preOrder_tree(root);
	// 		// printf("%c ",huff_node -> symbol);

	// // for(i = 0; i < 256; i++)
	// // {
	// // 	printf("frequency[%d] = %d\n",i,frequency[i]);
	// // }

	// puts("hello");
	// // NODE root = construct_h_tree(heap,root);
	// HASH *hash = create_hash();
	// USHORT binary = 0;
	// Byte trash_size = 0;
	// BuildHash(root, hash, binary, 0, &trash_size);
	// trash_size = 8 - (trash_size % 8);
	// int treeSize = 0;
	// Byte treeString[100000] = {0};
	// // puts("hello");
	// get_size_tree(root, &treeSize, treeString);
	// printf("\nsizetree = %d\n",treeSize);

	// // for (i = 0; i < strlen(treeString); i++){
	// // 	printf("%c", treeString[i]);
	// // }
	// // printf("\n");
	// // printf("Trash size = %d\n", trash_size);

	// Byte output[256];
	// strcpy(output, input);
	// strcat(output, ".huff");
	// FILE* compressedFile = fopen(output, "wb");
	// write_header(compressedFile, trash_size, treeSize, treeString);
	// Byte ch;
	// compress(compressedFile, inputFile, hash, trash_size);
	// fclose(compressedFile);
	// fclose(inputFile);


	////DECOMPRESSION
	// else if(choice == 1){

    Byte tree_array[100000] = {0};  // Array que receberá a arvore lida no cabeçalho
    USHORT trash , sizeTree;   // Lixo que será passado como ponteiro para a função de leitura do cabeçalho
    FILE *compressedFile = fopen(input,"rb");  // Para teste com o arquivo test.txt
    Byte ch;
    fscanf(compressedFile, "%c", &ch);
    trash = ch >> 5;  
    sizeTree = ch << 11; 
    sizeTree >>= 3;
    fscanf(compressedFile, "%c", &ch);
    sizeTree |= ch;
    // preOrder_tree(root); // Apenas para teste: Printa a árvore em pré ordem 
    NODE root = building_tree(root, compressedFile);
    decompress(compressedFile, input, root,sizeTree,trash, 0);   
	return 0;
}