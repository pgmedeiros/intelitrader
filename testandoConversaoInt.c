#include <stdio.h>

#define BYTE_SIZE 8
#define BASE64_BLOCK_SIZE 24
#define BASE64_BYTES_NUMBER 3
#define FIRST_BLOCK 0
#define SECOND_BLOCK 1
#define THIRD_BLOCK 2 
#define FOURTH_BLOCK 3

int* decimalToBinary(int decimal);

int putInBase64Blocks(int binary);

int main( void ) {
		
	int c; 
	
	scanf("%i", &c);
		
	putInBase64Blocks('C');

	
	return 0;
}

int getBlockByPosition(int base64block, int position) {
	
	unsigned long base64cell1 = 0 << 7;		
	unsigned base64block1 = 0 << 7;
	
	int bitsToMove;
	
	switch (position) {
		
		case FIRST_BLOCK:
			bitsToMove = 18;
			break;
		case SECOND_BLOCK: 
			bitsToMove = 12; 
			break;
		case THIRD_BLOCK: 
			bitsToMove = 6;
			break;
		case FOURTH_BLOCK:		
			bitsToMove = 0;

	}
	
	unsigned mask = 63; 
						
	mask = mask << bitsToMove;

	base64cell1 = (base64block & mask);
	
	base64cell1 >>= bitsToMove;
		
	printf("%i bloco 1\n", base64cell1);
	return base64cell1;
}

int putInBase64Blocks(int number) {
		
	unsigned base64block = malloc(BASE64_BYTES_NUMBER);	
	base64block = 0 << 23;
	
	base64block = (number | base64block);
	
	printf("%i aqui \n",base64block );
	
	base64block <<= 16;
	
	int firstBlock = getBlockByPosition(base64block, FIRST_BLOCK);
	int secondBlock = getBlockByPosition(base64block, SECOND_BLOCK);

			
	return 0;
	
}

