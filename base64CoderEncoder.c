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

void encode();
void decode();
void createSingleBinary(int asciiCharArray[], int size, int * baseBinary, int numberOfWords);
void separateBitsToSomeSize(int array[], int binary, int arraySize, int wordSize, int mask);
void convertToBase64Value(int * array);
int getBitsFromSpecificPosition(int binary, int position, int wordSize, int mask);
void getValueInBase64(int * v);
void defineBitsToMove(int * bitsToMove, int position, int wordSize);
int pseudoHash(int number);

int base64Table[65]= {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
					  'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
					  'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
					  'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
					  'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
					  'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
					  '8', '9', '+',  '/', '='};

int const COMPLETE_BASE64 = 63;
int const COMPLETE_ASCII = 255;
int const MASK_INT_POSITIVE = 4294967295;
int const MASK_EMPTY = 0;
int const ASCII_ARRAY_SIZE = 3;

int main( ) {
		
	
	FILE *toRead;
	FILE *toWrite;
	char readed[3];
	int counter = 0;
	
	if((toRead = fopen("toread", "r")) == NULL) {
		printf("Não foi possivel abrir o arquivo de leitura");
	}
	
	if((toWrite = fopen("towrite", "w")) == NULL) {
		printf("Não foi possivel abrir o arquivo de escrita");
	}
	
	
	while(!feof(toRead)) {
		
		while(counter != 3) {
			fscanf(toRead, "%c", &readed[counter]);
			counter++;
	
		}
		
		printf("%c", readed[counter]);
		
		counter = 0;
	}
	
			encode(toWrite, readed);

	
	return 0;
}

void encode(FILE * toWrite, char c[]) {
	
	int base64CharArray[4] = { base64Table[64] };
	int asciiCharArraySize = 3;
	int binary = 0; 
	int array[3];
	
	for(int i = 0; i < 3; i++) {
		array[i] = c[i];
	}
	
	
	createSingleBinary(array, BYTE_SIZE, &binary, 3);
	
	separateBitsToSomeSize(base64CharArray, binary, asciiCharArraySize, BASE64_WORD_SIZE, COMPLETE_BASE64);
	
	convertToBase64Value(base64CharArray);
	
	write(toWrite, base64CharArray);	

}

void decode() {
	
	int arrayParaTest[4] = {'S', 'm', '9', 'z'};
	int arrayAscii[3];
	unsigned binary = 0;
	int bitsToMove;
	
	getValueInBase64(arrayParaTest);

	createSingleBinary(arrayParaTest, BASE64_WORD_SIZE, &binary, 4);	
	
	separateBitsToSomeSize(arrayAscii, binary, ASCII_ARRAY_SIZE, BYTE_SIZE, COMPLETE_ASCII);

	write(arrayAscii);

}

void createSingleBinary(int x[], int size, int * baseBinary, int numberOfWords) {
				
	for (int i = 0; i < numberOfWords; i++) {
		
		int bitsToMove;
	
		defineBitsToMove(&bitsToMove, i, size);
		
		x[i] <<= bitsToMove;
		
		*baseBinary =  *baseBinary | x[i];		
	}
}

void separateBitsToSomeSize(int array[], int binary, int arraySize, int wordSize, int mask) {
			
	for (int i = 0; i < arraySize + 1; i++) {
		array[i] = getBitsFromSpecificPosition(binary, i, wordSize, mask);
	}
	
}

int getBitsFromSpecificPosition(int binary, int position, int wordSize, int mask) {
	
	int bitsToMove;	
	defineBitsToMove(&bitsToMove, position, wordSize);
	
	mask <<= bitsToMove;
	
	binary = binary & mask;
	
	binary >>= bitsToMove;
	
	return binary;
}

void convertToBase64Value(int * array) {
	for (int i = 0; i < 4; i++) {
		array[i] = base64Table[array[i]];
	}
}

void getValueInBase64(int * v) {
	for (int i = 0; i < 4; i++) {
		v[i] = pseudoHash(v[i]);
	}
}


void write(FILE * toWrite, unsigned * v) {
	for(int i = 0; i < 4; i++) {
		fprintf(toWrite, "%c", v[i]);
	}
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

