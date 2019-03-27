#include <stdio.h>
#include <stdlib.h>

typedef unsigned char Byte;

int is_bit_i_set(Byte b, int i){
	Byte mask = i << i;
	return mask & b;
}

Byte set_bit_i(Byte b, int i){
	Byte mask = 1 << i;
	return mask | b;
}

Byte clear_byte(){
	return 0 << 8;
}

void print_bits(Byte b, int goToNextLine){
	int i;
	for(i = 0; i < 8; i++){
		if (is_bit_i_set(b, i)){
			printf("1");
		}else{
			printf("0");
		}
	}
	if (goToNextLine){
		printf("\n");
	}
}


void print_bytes(Byte *b, int size){
	int i;
	for(i = 0; i < size; i++){
		print_bits(b[i], 0);
		printf(" ");
	}
	printf("\n");
}

int main(){
	Byte n;
	n = clear_byte();
	n = set_bit_i(n, 5);
	n = set_bit_i(n, 1);
	print_bits(n, 1);
	print_bytes(&n, 1);
	return 0;
}
