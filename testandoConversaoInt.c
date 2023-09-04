#include <stdio.h>

#define BYTE_SIZE 8
#define BASE64_BLOCK_SIZE 24
#define BASE64_BYTES_NUMBER 3
#define FIRST_BLOCK 0
#define SECOND_BLOCK 1
#define THIRD_BLOCK 2 
#define FOURTH_BLOCK 3

int putInBase64Blocks(int number, int size);

int arrayCharToBase64Complete(int position, int x, int y);

int base64Table[65]= {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
					  'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
					  'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
					  'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
					  'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
					  'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
					  '8', '9', '+',  '/', '='};

int main( void ) {
		
	int c; 
	
	scanf("%i", &c);
	
	char v[3] = {'M', 'a', 'n'};
	
	unsigned mask = 0;
	mask <<= 16;
	
	for(int i = 0; i < 3; i++) {
		mask = convertArrayToBase64(i, mask, v[i]);
	}
			
	putInBase64Blocks(mask, 3);

	return 0;
}

int getBlockByPosition(int base64block, int position) {
	
	unsigned base64cell1 = 0 << 7;		
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
		
	return base64cell1;
}

int convertArrayToBase64(int position, int numberToPut, int number) {
	
	int bitsToMove;
	
	switch (position) {
		
		case FIRST_BLOCK:
			bitsToMove = 16;
			break;
		case SECOND_BLOCK: 
			bitsToMove = 8; 
			break;
		case THIRD_BLOCK: 
			bitsToMove = 0;
	}
	
	number <<= bitsToMove;
	numberToPut = (number | numberToPut);
	
	return numberToPut;
		
}

int putInBase64Blocks(int number, int size) {
		
	unsigned base64block = malloc(BASE64_BYTES_NUMBER);	
	
	char firstBlock;
	char secondBlock;
	char thirdBlock;
	char fourthBlock;
	
	if(size == 2) {
		firstBlock = base64Table[getBlockByPosition(number, FIRST_BLOCK)];
		secondBlock = base64Table[getBlockByPosition(number, SECOND_BLOCK)];
		thirdBlock = base64Table[getBlockByPosition(number, THIRD_BLOCK)];
		fourthBlock = base64Table[64];
	}
	
	if(size == 1) {
		firstBlock = base64Table[getBlockByPosition(number, FIRST_BLOCK)];
		secondBlock = base64Table[getBlockByPosition(number, SECOND_BLOCK)];
		thirdBlock = base64Table[64];
		fourthBlock = base64Table[64];
	}
	
	firstBlock = base64Table[getBlockByPosition(number, FIRST_BLOCK)];
	secondBlock = base64Table[getBlockByPosition(number, SECOND_BLOCK)];
	thirdBlock = base64Table[getBlockByPosition(number, THIRD_BLOCK)];
	fourthBlock = base64Table[getBlockByPosition(number, FOURTH_BLOCK)];
		
	putchar(firstBlock);		
	putchar(secondBlock);
	putchar(thirdBlock);
	putchar(fourthBlock);

			
	return 0;
	
}

