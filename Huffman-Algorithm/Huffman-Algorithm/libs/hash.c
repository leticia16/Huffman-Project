#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "hufman_tree.h"

#define HashSize 257

typedef unsigned short USHORT;

void BuildHash(NODE huffNode, HASH *hash, USHORT binary, int pos, Byte *trash_size){
	if (huffNode == NULL){
		return;
	}
	if (huffNode->left == NULL && huffNode->right == NULL){
		*trash_size += (huffNode->frequency * pos);
		hash = put(hash, binary, (Byte)huffNode->symbol, pos);
		// print_hash_binary(hash, huffNode->symbol, binary);
	}
	binary <<= 1;
	BuildHash(huffNode->left, hash, binary, pos + 1, trash_size);
	binary++;
	BuildHash(huffNode->right, hash, binary, pos + 1, trash_size);
}

TABLE *create_table(USHORT binary, int size)
{
	TABLE *new_hash = (TABLE*) malloc(sizeof(TABLE));
	new_hash -> binary = binary;
	new_hash -> size = size;	
	return new_hash;
}

HASH *create_hash()
{
	int i;
	HASH *new_hash = (HASH*) malloc(sizeof(HASH));
	for(i = 0; i < HashSize; i++)
	{
		new_hash -> table[i] = NULL;
	}
	return new_hash;	
}

HASH *put(HASH *hash, USHORT binary, void *symbol, int i)
{
	TABLE *item = create_table(binary, i);
	hash -> table[(Byte)symbol] = item;
	return hash;
}

USHORT set_bit_i(USHORT b, int i){
	USHORT mask = 1 << i;
	return mask | b;
}

int is_bit_i_set(USHORT b, int i){
	USHORT mask = 1 << i;
	return mask & b;
}

void print_bits_ushort(USHORT b, int go_to_next_line){
	int i;
	for(i = 15; i >= 0; i--){
		// printf("%d", is_bit_i_set(b, i) ? 1 : 0);
        // if(is_bit_i_set(b,i)){
        //     printf("%d", 1);
        // }else{
        //     printf("%d", 0);
        // }
	}
	if (go_to_next_line){
		printf("\n");
	}
}

void print_hash_binary(HASH *hash, Byte symbol, USHORT binary)
{
	// print_hash_binary(hash, root->symbol, binary); chamada da função
	puts("---------------------------------");
	print_bits_ushort(binary, 1);
	printf("hash -> table[%d] -> binary = %d\n",symbol, hash -> table[symbol] -> binary);
	printf("hash -> table[%d] -> size = %d\n",symbol,hash -> table[symbol] -> size);
	puts("---------------------------------");
}