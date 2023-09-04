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
	
	int v[3] = {'M', 'a', 'n'};
	int y[4];
	
	y[0] = base64Table[64];
	y[1] = base64Table[64];
	y[2] = base64Table[64];
	y[3] = base64Table[64];

		
	unsigned base64Array = convertArrayToBase64(v);
	
	createSixBitsArray(y, base64Array, 3);
	
	for(int x = 0; x < 4; x++) {
		putchar(y[x]);
	}
	
	return 0;
}

int convertArrayToBase64(int array[]) {
	
	unsigned numberToPut = 0;
	numberToPut <<= 16;
	
	for (int i = 0; i < BASE64_BYTES_NUMBER; i++) {
		
		int bitsToMove;
	
		switch (i) {
			
			case FIRST_BLOCK:
				bitsToMove = 16;
				break;
			case SECOND_BLOCK: 
				bitsToMove = 8; 
				break;
			case THIRD_BLOCK: 
				bitsToMove = 0;
		}
	
		array[i] <<= bitsToMove;
		numberToPut = (array[i] | numberToPut);
	}
	
	return numberToPut;
		
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

void createSixBitsArray(int array[], int number, int size) {
			
	for (int i = 0; i < size + 1; i++) {
		array[i] = base64Table[getBlockByPosition(number, i)];
	}
	
}

