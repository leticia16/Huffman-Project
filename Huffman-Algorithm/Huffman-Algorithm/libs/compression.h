#ifndef _COMPRESSION_H_
#define _COMPRESSION_H_

#include <stdio.h>
#include "hufman_tree.h"
#include "hash.h"
#include "priority_queue.h"

typedef struct hash HASH;
typedef unsigned char Byte;
typedef unsigned short USHORT;

int is_bit_i_set_byte(Byte b, int i);

Byte set_bit_i_byte(Byte b, int i);

int is_leaf(NODE node);

void get_size_tree(NODE node, int *size, Byte *treeString);

void write_header(FILE *compressedFile, int trash, USHORT sizeTree, Byte *treeString);

NODE build_tree(P_QUEUE *huff_p_queue);

void compress(FILE *compressedFile, FILE *inputFile, HASH *hash, Byte trashSize);

#endif