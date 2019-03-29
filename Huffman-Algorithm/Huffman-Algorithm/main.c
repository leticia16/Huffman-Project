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

int main()
{
	int i = 0;
	int option;
	while(1){
		Byte input[100];
		printf("Escolha uma opção: \n");
		printf("(1) Comprimir Arquivo\n");
		printf("(2) Descomprimir Arquivo\n");
		printf("(3) Sair\n");
		scanf("%d",&option);
		if (option == 1){
			printf("\nDigite o nome do Arquivo: ");
			scanf("%s", input);
			printf("\n");
			FILE *inputFile = fopen(input,"rb");
			int *frequency = create_frequency_array(input, inputFile);
			P_QUEUE *p_queue = create_p_queue();

			for(i = 0; i < 256; i++)
			{	
				if(frequency[i])
				{
					NODE huff_node = create_node();
					huff_node -> frequency = frequency[i];
					huff_node -> symbol = (void*)i;
					enqueue(p_queue,huff_node);
				}
			}
			node *aux = p_queue->head;
			NODE root = build_tree(p_queue);
			HASH *hash = create_hash();
			USHORT binary = 0;
			Byte trash_size = 0;
			BuildHash(root, hash, binary, 0, &trash_size);
			trash_size = 8 - (trash_size % 8);
			int treeSize = 0;
			Byte treeString[100000] = {0};
			get_size_tree(root, &treeSize, treeString);
			Byte output[256];
			strcpy(output, input);
			strcat(output, ".huff");
			FILE* compressedFile = fopen(output, "wb");
			write_header(compressedFile, trash_size, treeSize, treeString);
			Byte ch;
			compress(compressedFile, inputFile, hash, trash_size);
			fclose(compressedFile);
			fclose(inputFile);
		}
		else if (option == 2){
			printf("\nDigite o nome do Arquivo: ");
			scanf("%s", input);
			printf("\n");
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
		    NODE root = building_tree(root, compressedFile);
		    decompress(compressedFile, input, root,sizeTree,trash, 0);   
		}
		else if (option == 3){
			return 0;
		}
		else {
			printf("Digite uma opcao valida:\n");
		}
	}
}
