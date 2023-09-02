#include <stdio.h>

#define BYTE_SIZE 8
#define BASE64_BLOCK_SIZE 24
#define BASE64_BYTES_NUMBER 3

int* decimalToBinary(int decimal);

int putInBase64Blocks(int binary);

int main( void ) {
		
	unsigned c; 
	
	scanf("%u", &c);
	
	printf("%u\n", c);
	
	unsigned x = putInBase64Blocks('A');
	
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

int putInBase64Blocks(int number) {
	
//	000000 000000 000000 000000
//	
//	00000000 00000000 00000000
//	
//	teste com exemplo letra a 
//	
//	 // origem 8 bits
//	 
//	01000001
//	 
//	// pra cá  
//	010000 010000 = = 
//	
//	
//	00000000 00000000 00000000
//	
//	00000000 00000000 01000001
//	
//	
//	00000000 00000000 00000000
//	
//	// andou 16 bits
//	
//	01000001 00000000 00000000
	
	
	unsigned base64block = malloc(BASE64_BYTES_NUMBER);	
	base64block = 0 << 23;
	
	base64block = (number | base64block);
	
	base64block <<= 16;
	
	printf("%i ", base64block);
		
	
	
	
	
	return 0;
	
	
}

