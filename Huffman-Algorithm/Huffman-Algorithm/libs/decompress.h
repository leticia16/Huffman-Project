#ifndef _DECOMPRESS_H_
#define _DECOMPRESS_H_

#include <stdio.h>
#include "hufman_tree.h"
#include "hash.h"

typedef struct hash HASH;
typedef unsigned char Byte;
typedef unsigned short USHORT;

void decompress(FILE *compressedFile, Byte *input, NODE root, int sizeTree, int trash, unsigned long long int fileSize);
int read_Header(FILE *file, Byte *tree_array, Byte *trash);
NODE buildTree(NODE root, Byte *tree, int *index, int treeSize);
NODE building_tree(NODE huff_tree, FILE *compress_archive);

#endif