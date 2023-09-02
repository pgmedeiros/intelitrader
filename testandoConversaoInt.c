#include <stdio.h>

#define BYTE_SIZE 8
#define BASE64_BLOCK_SIZE 24
#define BASE64_BYTES_NUMBER 3

int* decimalToBinary(int decimal);

int * putInBase64Blocks(int binary);

int main( void ) {
		
	unsigned c; 
	
	scanf("%u", &c);
	
	printf("%u\n", c);
	
	int * f = decimalToBinary(c);	
	
	int * texto = putInBase64Blocks(f);
	
	for (int x = 0; x < 23; x++) {
		printf("%i ", texto[x]);
	}
	
	return 0;
}

int* decimalToBinary(int decimal) {
	
	int* binary = malloc(BYTE_SIZE * sizeof(int));
	int counter = BYTE_SIZE - 1;
	
	do {
		binary[counter--] = decimal % 2;
		decimal = decimal / 2;
	}
	while(decimal != 0);
	
	for (int x = 0; x <= counter; x++) {
		binary[x] = 0;
	}
	
	return binary;
}

int* putInBase64Blocks(int binary) {
	
	unsigned base64block = malloc(BASE64_BYTES_NUMBER);
	base64block = 1 << BASE64_BLOCK_SIZE - 1;
	
	char texto[24];
	
	for (int i = 1; i <= BASE64_BLOCK_SIZE; i++) {
		texto[i - 1] = (binary & base64block ? '1' : '0');
		binary = binary << 1; 
	}
	
	return texto;
	
}

