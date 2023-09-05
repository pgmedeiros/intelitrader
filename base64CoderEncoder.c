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

unsigned concatBase64Digits(unsigned * v, unsigned * binary);

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
	int arrayParaTest[4] = {'V', '0', 's', '='};
	int asciiCharArraySize;
	
	scanf("%i", &c);
	
	asciiCharArraySize = 3;
		
	base64Binary = AsciiToBase64(asciiCharArray);
	
	translateBinaryArrayToCharArrayInBase64(base64CharArray, base64Binary, asciiCharArraySize);
	
	for(int i = 0; i < 4; i++) {
		putchar(base64CharArray[i]);
	}
	// decode(arrayParaTest);
	
	return 0;
}

int AsciiToBase64(int asciiCharArray[]) {
	
	unsigned result;
			
	for (int i = 0; i < BASE64_BYTES_NUMBER; i++) {
		
		int bitsToMove;
	
		defineBitsToMove(&bitsToMove, i, BYTE_SIZE);
		
		moveBitsForLeft(&asciiCharArray[i], bitsToMove);
		
		getBitsByOrComparisonWithMask(&result, asciiCharArray[i], result);		
	}
	
	return result;
		
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

int getCharInSomePositionFromBase64Binary(int base64CharArrayInOneBinary, int position) {
	
	unsigned base64CharBinary;	
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

void decode(int v[]) {
	
	unsigned binary;
	concatBase64Digits(v, &binary);
	getAsciiValues(&binary);

}

unsigned concatBase64Digits(unsigned * v, unsigned * binary) {
	
	for (int i = 0; i < 4; i++) {
				
		int x = pseudoHash(v[i]);
		
		if ( i == 0 ) {
			x <<= 18;
		}
		
		if ( i == 1) {
			x <<= 12;
		}
		
		if ( i == 2) {
			x <<= 6;
		}
		
		
		*binary = *binary | x;
		
	}
	
}

void getAsciiValues(unsigned * binary) {
	
	for (int i = 0; i < 3; i++) {
			
			int x = 255; 
			
			int final;
			
			if ( i == 0) {
				x <<= 16; 
			}
			
			if ( i == 1) {
				x <<= 8; 
			}
			
			final = (x & *binary);
			
			if ( i == 0) {
				final >>= 16; 	
			}
			
			if ( i == 1) {
				final >>= 8; 	
			}
			
			putchar(final);
		}	
}

int pseudoHash(int number) {
	
	if (number == 61) {
		return 0;
	}
	if (number >= 65 && number <= 90) {
		return number - 65;
	}
	
	if (number >= 97 && number <= 122) {
		return number - 71;
	}
	
	if (number >= 48 && number <= 57) {
		return number + 4;
	}
	
	if (number == 43) {
		return 62;		
	}
	
	if (number == 47) {
		return 63;
	}
}

