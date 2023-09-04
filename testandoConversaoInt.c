#include <stdio.h>

#define BYTE_SIZE 8
#define BASE64_BLOCK_SIZE 24
#define INT_BLOCK_SIZE 32
#define BASE64_BYTES_NUMBER 3
#define BASE64_WORD_SIZE 6
#define FIRST_BLOCK 0
#define SECOND_BLOCK 1
#define THIRD_BLOCK 2 
#define FOURTH_BLOCK 3

int putInBase64Blocks(int number, int size);

int arrayCharToBase64Complete(int position, int x, int y);

void prepareArray(int v[]);

void defineBitsToMove(int * bitsToMove, int position, int size);

int base64Table[65]= {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
					  'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
					  'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
					  'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
					  'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
					  'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
					  '8', '9', '+',  '/', '='};

int const COMPLETE_BASE64 = 63;

int main( void ) {
		
	int c; 
	unsigned base64Binary;

	int asciiCharArray[3] = {'M', 'a', 'n'};
	int base64CharArray[4] = { base64Table[64] };
	int asciiCharArraySize;
	
	scanf("%i", &c);
	
	asciiCharArraySize = 3;
		
	base64Binary = AsciiToBase64(asciiCharArray);
	
	translateBinaryArrayToCharArrayInBase64(base64CharArray, base64Binary, asciiCharArraySize);
	
	for(int i = 0; i < 4; i++) {
		putchar(base64CharArray[i]);
	}
	
	return 0;
}

int AsciiToBase64(int asciiCharArray[]) {
	
	unsigned numberToPut = 0;
	numberToPut <<= 16;
	
	for (int i = 0; i < BASE64_BYTES_NUMBER; i++) {
		
		int bitsToMove;
	
		defineBitsToMove(&bitsToMove, i, BYTE_SIZE);
		
		asciiCharArray[i] <<= bitsToMove;
		numberToPut = (asciiCharArray[i] | numberToPut);
	}
	
	return numberToPut;
		
}

void moveBitsForLeft(int * number, int bitsToMove) {
	*number <<= bitsToMove;
}

void moveBitsForRight(int * number, int bitsToMove) {
	*number >>= bitsToMove;
}

void getBitsByAndComparisonWithMask(int * variableToPutResult, int binary, int mask) {
	* variableToPutResult = ( binary & mask );
}

int getCharInSomePositionFromBase64Binary(int base64CharArrayInOneBinary, int position) {
	
	unsigned base64CharBinary = 0 << 7;	
	int bitsToMove;
	unsigned base64mask = COMPLETE_BASE64; 
	
	defineBitsToMove(&bitsToMove, position, BASE64_WORD_SIZE);

	moveBitsForLeft(&base64mask, bitsToMove);	

	getBitsByAndComparisonWithMask(&base64CharBinary, base64CharArrayInOneBinary, base64mask);
	
	moveBitsForRight(&base64CharBinary, bitsToMove);
	
	return base64CharBinary;
}

void defineBitsToMove(int * bitsToMove, int position, int wordSize) {
	
	switch (position) {
		
		case FIRST_BLOCK:
			*bitsToMove = BASE64_BLOCK_SIZE - (wordSize);
			break;
		case SECOND_BLOCK: 
			*bitsToMove = BASE64_BLOCK_SIZE - (wordSize * 2); 
			break;
		case THIRD_BLOCK: 
			*bitsToMove = BASE64_BLOCK_SIZE - (wordSize * 3);
			break;
		case FOURTH_BLOCK:		
			*bitsToMove = BASE64_BLOCK_SIZE - (wordSize * 4);

	}
}

void translateBinaryArrayToCharArrayInBase64(int base64CharArray[], int base64Binary, int asciiCharArraySize) {
			
	for (int i = 0; i < asciiCharArraySize + 1; i++) {
		base64CharArray[i] = base64Table[getCharInSomePositionFromBase64Binary(base64Binary, i)];
	}
	
}

