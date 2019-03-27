#ifndef _HASH_H_
#define _HASH_H_

#define HashSize 256

#include "hufman_tree.h"
#include <stdio.h>

typedef unsigned short USHORT;
typedef unsigned char Byte;

typedef struct table{
	USHORT binary;
	int size;
}TABLE;

typedef struct hash{
	TABLE *table[HashSize];
} HASH;

void BuildHash(NODE root, HASH *hash, USHORT binary, int pos, Byte *trash_size);
TABLE *create_table(USHORT binary, int size);
HASH *create_hash();
HASH *put(HASH *hash, USHORT binary, void *symbol, int i);
void print_hash_binary(HASH *hash, Byte symbol, USHORT binary);
void print_bits_ushort(USHORT b, int go_to_next_line);
int is_bit_i_set(USHORT b, int i);
USHORT set_bit_i(USHORT b, int i);
#endif