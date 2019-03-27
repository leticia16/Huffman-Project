#include <stdio.h>
#include <stdlib.h>
#include "libs/hufman_tree.h"
#include "libs/hash.h"
#include <string.h>

NODE buildTree(NODE root, Byte *tree, int *index, int treeSize)
{
	NODE node = create_node();

    if(tree[*index] == '*')//nó interno
    {
    	node -> symbol = '*';
    	++(*index);
    	node -> left = buildTree(node,tree,index,treeSize);
    	++(*index);
    	node -> right = buildTree(node, tree,index, treeSize);
    }
    else // é folha
    {
        if(tree[*index] == '\\')// se a folha começar com '\' existem duas possibilidades para o próximo char na leitura
        {
            if(tree[++(*index)] == '\\' && (*index)<treeSize) // a folha é do tipo '\\'
            {
            	node -> symbol = '\\';
            	return node;
            }
            if(tree[++(*index)] == '*' && (*index)<treeSize)// a folha é do tipo '\*'
            {
            	node -> symbol = '*';
            	return node;
            }
        }
        else if(!(*index)<treeSize){ //Caso não tenha '\' , a folha será qualquer outro caractere
        	node -> symbol = tree[*index];
        return node;
    }
}
}

NODE building_tree(NODE huff_tree, FILE *compress_archive) {
    Byte character;
    fscanf(compress_archive, "%c", &character);
    if(character == '*') {
        huff_tree = create_node();
        huff_tree -> symbol = character;
        huff_tree->left = building_tree(huff_tree->left, compress_archive);
        huff_tree->right = building_tree(huff_tree->right, compress_archive);

    } else {
        if(character == '\\')
        {
            fscanf(compress_archive, "%c", &character);
        }
        huff_tree = create_node();
        huff_tree -> symbol = character;
    }
    return huff_tree;
}

int read_Header(FILE *file, Byte *tree_array, Byte *trash)
{
	USHORT sizeTree = 0;
	Byte first_byte, second_byte,tree_byte;

    first_byte = fgetc(file); // Pega o primeiro Byte do arquivo
    second_byte = fgetc(file); // Pega o segundo Byte do arquivo

    (*trash) = first_byte >> 5; // Shift bit pra esquerda para obter apenas os 3 bits do lixo, ex: 10100000 ~ (>>5) ~ 00000101
    
    first_byte = first_byte << 3; // Shift bit pra esquerda para retirar o lixo, ex: 11000001 ~ 00001000 
    first_byte = first_byte >> 3; // Shift bit pra direita para voltr ao lugar (já sem o lixo): 00001000 ~ 00000001

    sizeTree = first_byte; //atribui o Byte "first_byte" modificado ao USHORT sizeTree
    sizeTree = sizeTree << 8; // Shift bit para a esquerda para deixar as oito primeiro posições livres para o second_byte
    sizeTree |= second_byte; // concatena USHORT com Byte (através do operador "OU")

    // printf("trash = %d sizeTree = %d\n", *trash, sizeTree); // print apenas para teste

    int i;
    for(i = 0; i < sizeTree; i++) // lê a árvore e coloca no array
    {
    	tree_byte = fgetc(file);
    	tree_array[i] = tree_byte;
    }
    return sizeTree; //retorna o tamanho para ser usado na função BuildTree
}

// int is_leaf(NODE huff_tree) {
//     return huff_tree->left == NULL && huff_tree->right == NULL;
// }

void decompress(FILE *compressedFile, Byte *input, NODE root, int sizeTree, int trash, unsigned long long int fileSize)
{
	int i;
	Byte fileByte = 0;
	NODE aux = root;
	printf("\ntrash = %d\n", trash);
	Byte ch;
	char file_out[100];
    int size = strlen(input);
    
    for(i = 0; i < size - 5; i++) {
        file_out[i] = input[i];
    }
    file_out[i] = '\0';

while(fscanf(compressedFile, "%c", &ch) != EOF) {
        fileSize++;
    }
    fseek(compressedFile, 2 + sizeTree, SEEK_SET);
    FILE *decompressedFile = fopen(file_out, "wb");
    while(fileSize > 0) {

        fscanf(compressedFile, "%c", &ch);
        if(fileSize != 1)
        {
            for(i = 7; i >= 0; i --) {  
                if(is_bit_i_set(ch,i)) {
                    aux = aux->right;
                } else {
                    aux = aux->left;
                }
                if(is_leaf(aux)) {

                    fprintf(decompressedFile, "%c", aux->symbol);
                    aux = root;
                }
            }
        } else {
            for(i = 7; i >= trash; i--) {  
                if(is_bit_i_set(ch,i)) {
                    aux = aux->right;
                } else {
                    aux = aux->left;
                } 
                if(is_leaf(aux)) {
                    fprintf(decompressedFile, "%c", aux->symbol);
                    aux = root;
                }
            }
        }
        fileSize --;
    }
     fclose(decompressedFile);
	//////////////////////////////////////////////////////////////////////
	// while(fscanf(compressedFile, "%c", &ch) != EOF) {
	// 	fileSize++;
	// }
	// fseek(compressedFile, 2 + sizeTree, SEEK_SET);
	// while (fileSize > 0)
	// {
	// 	printf("fileSize = %llu\n", fileSize);
	// 	fscanf(compressedFile, "%c", &fileByte);
	// 	if(fileSize == 1)
	// 	{
	// 		puts("hello");
	// 		for(i = 7; i >= trash; i--)
	// 		{
	// 			if(aux -> left == NULL && aux -> right == NULL)	
	// 			{
	// 				fprintf(decompressedFile, "%c", aux->symbol);
	// 				aux = root;
	// 			}
	// 			if(is_bit_i_set_byte(fileByte,i))
	// 			{
	// 				aux = aux -> right;
	// 			}
	// 			else{
	// 				aux = aux -> left;
	// 			}
	// 		}
	// 	}
	// 	else
	// 	{
	// 		for(i = 7; i >= 0; i--)
	// 		{
	// 			if(aux -> left == NULL && aux -> right == NULL)	
	// 			{
	// 				fprintf(decompressedFile, "%c", aux->symbol);
	// 				aux = root;
	// 			}
	// 			if(is_bit_i_set_byte(fileByte,i))
	// 			{
	// 				aux = aux -> right;
	// 			}
	// 			else{
	// 				aux = aux -> left;
	// 			}
	// 		}

	// 	}

	// 	fileSize--;
	// }
	// if(aux == root)printf("ok\n");

}