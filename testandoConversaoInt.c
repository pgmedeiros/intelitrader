#include <stdio.h>

#define BYTE_SIZE 8
#define BASE64_BLOCK_SIZE 24
#define BASE64_BYTES_NUMBER 3
#define FIRST_BLOCK 0
#define SECOND_BLOCK 1
#define THIRD_BLOCK 2 
#define FOURTH_BLOCK 3

int putInBase64Blocks(int number);

int arrayCharToBase64Complete(int position, int x, int y);

int main( void ) {
		
	int c; 
	
	scanf("%i", &c);
	
	char v[3] = {'A', 'B', 'C'};
	
	unsigned mask = 0;
	mask <<= 16;
			
	int retorno = arrayCharToBase64Complete(FIRST_BLOCK, mask, 65);
	int retorno2 = arrayCharToBase64Complete(SECOND_BLOCK, retorno, 66);
	int retorno3 = arrayCharToBase64Complete(THIRD_BLOCK, retorno2, 67);
	
	putInBase64Blocks(retorno3);


	printf("retorno %i ", retorno);
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

int arrayCharToBase64Complete(int position, int numberToPut, int number) {
	
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

int putInBase64Blocks(int number) {
		
	unsigned base64block = malloc(BASE64_BYTES_NUMBER);	
	
	int firstBlock = getBlockByPosition(number, FIRST_BLOCK);
	int secondBlock = getBlockByPosition(number, SECOND_BLOCK);
	int thirdBlock = getBlockByPosition(number, THIRD_BLOCK);
	int fourthBlock = getBlockByPosition(number, FOURTH_BLOCK);
	
			
	return 0;
	
}

