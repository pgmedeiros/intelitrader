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

void decode();
void encode();

int putInBase64Blocks(int number, int size);

int arrayCharToBase64Complete(int position, int x, int y);

void concatBase64Digits(unsigned * v, unsigned * binary);

void encode();

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

int const MASK_INT_POSITIVE = 4294967295;
int const MASK_EMPTY = 0;

int main( void ) {
		
	
	encode();
	printf("\n");
	decode();
	
	return 0;
}

void encode() {
	
	int base64CharArray[4] = { base64Table[64] };
	int asciiCharArraySize = 3;
	int asciiCharArray[3] = {'M', 'a', 'n'};
	int binary; 
	
	createSingleBinary(asciiCharArray, BYTE_SIZE, &binary);
	
	separateBitsToSomeSize(base64CharArray, binary, asciiCharArraySize, BASE64_WORD_SIZE);
	
	convertToBase64Value(base64CharArray);
	
	write(base64CharArray);	

}

void decode() {
	
	int arrayParaTest[4] = {'S', 'm', '9', 'z'};
	unsigned binary;
	
	concatBase64Digits(arrayParaTest, &binary);

	getAsciiValues(&binary);

}


void write(unsigned * v) {
	for(int i = 0; i < 4; i++) {
		putchar(v[i]);
	}
}

void convertToBase64Value(int * array) {
	for (int i = 0; i < 4; i++) {
		array[i] = base64Table[array[i]];
	}
}

void createSingleBinary(int asciiCharArray[], int size, int * baseBinary) {
	
	unsigned result = MASK_EMPTY;
			
	for (int i = 0; i < BASE64_BYTES_NUMBER; i++) {
		
		int bitsToMove;
	
		defineBitsToMove(&bitsToMove, i, size);
		
		moveBitsForLeft(&asciiCharArray[i], bitsToMove);
		
		getBitsByOrComparisonWithMask(baseBinary, asciiCharArray[i], *baseBinary);		
	}
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

void getBitsByOrComparisonWithMask(int * result, int binary, int mask) {
	* result = ( binary | mask );
}

int getBitsFromSpecificPosition(int binary, int position, int wordSize) {
	
	unsigned base64CharBinary;	
	int bitsToMove;
	unsigned base64mask = COMPLETE_BASE64; 
	
	defineBitsToMove(&bitsToMove, position, wordSize);

	moveBitsForLeft(&base64mask, bitsToMove);	

	getBitsByAndComparisonWithMask(&base64CharBinary, binary, base64mask);
	
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

void separateBitsToSomeSize(int array[], int binary, int arraySize, int wordSize) { // tornar essa funçao genérica
			
	for (int i = 0; i < arraySize + 1; i++) {
		array[i] = getBitsFromSpecificPosition(binary, i, wordSize);
	}
	
}

void concatBase64Digits(unsigned * charArray, unsigned * binary) {
	
	int bitsToMove;
	
	for (int i = 0; i < 4; i++) {
				
		int caracter = pseudoHash(charArray[i]);
		
		defineBitsToMove(&bitsToMove, i, BASE64_WORD_SIZE);
		
		caracter <<= bitsToMove;
				
		*binary = *binary | caracter;
		
	}
	
}

void getAsciiValues(unsigned * binary) {
	
	int bitsToMove;
	
	for (int i = 0; i < 3; i++) {
			
			defineBitsToMove(&bitsToMove, i, BYTE_SIZE);
																		
			int final = (MASK_INT_POSITIVE & *binary);
			
			moveBitsForRight(&final, bitsToMove);
			
			putchar(final);
		}	
}

int pseudoHash(int number) {
	
	if (number == 43) {
		return 62;		
	}
	
	if (number == 47) {
		return 63;
	}
	
	if (number >= 48 && number <= 57) {
		return number + 4;
	}
	
	if (number == 61) {
		return 0;
	}
	if (number >= 65 && number <= 90) {
		return number - 65;
	}
	
	if (number >= 97 && number <= 122) {
		return number - 71;
	}
	
}

