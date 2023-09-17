#include <stdio.h>
#include <stdlib.h>

#define BYTE_SIZE 8
#define BASE64_BLOCK_SIZE 24
#define INT_BLOCK_SIZE 32
#define BASE64_BYTES_NUMBER 3
#define BASE64_WORD_SIZE 6
#define FIRST_BLOCK 0
#define SECOND_BLOCK 1
#define THIRD_BLOCK 2 
#define FOURTH_BLOCK 3
#define VALUE_BEYOND_ASCII 999

void encode(FILE * toWrite, char c[], int var);
void decode(FILE * toWrite, char c[], int var);
void createSingleBinary(int asciiCharArray[], int size, int * baseBinary, int numberOfWords);
void separateBitsToSomeSize(int array[], int binary, int arraySize, int wordSize, int mask);
void convertToBase64Value(int * array);
int  getBitsFromSpecificPosition(int binary, int position, int wordSize, int mask);
void getValueInBase64(int * v);
void defineBitsToMove(int * bitsToMove, int position, int wordSize);
int  asciiToBase64Index(int number);
void base64IndexToValue(int * array);
void write(FILE * toWrite, unsigned * v, int size);
void convertArrayToBase64Index(int * v);
int  base64ValueToIndex(int number);
void getFilesPath(char * toReadPath, char * toWritePath);
void openFiles(char * toReadPath, char * toWritePath, FILE ** toRead, FILE ** toWrite);
int defineWordSize(char c);
void readAndWrite(FILE * toWrite, FILE * toRead, char * readed, char option);
void getOption(char * option);
void fillArray(int var, int * array, char * c, int size);

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
int const BASE64_EMPTY_VALUE = 61;

int main() {
		
	
	FILE *toRead;
	FILE *toWrite;
	
	char readed[10000];	
	char toWritePath[60];
	char toReadPath[60];
	char option;
	
	getOption(&option);
	
	getFilesPath(toReadPath, toWritePath);
	
	openFiles(toReadPath, toWritePath, &toRead, &toWrite);
	
	readAndWrite(toWrite, toRead, readed, option);
	
	fclose(toWrite);
	fclose(toRead);
	
	return 0;
}

void fillArray(int var, int * array, char * c, int size) {
	int y;
	for(int i = 0; i < size; i++) {
		y = i + (var  * size);
		array[i] = c[y];
	}
}

void encode(FILE * toWrite, char * c, int var) {
	
	int base64CharArray[4] = { base64Table[64] };
	int asciiCharArraySize = 3;
	int binary = 0; 
	int array[3];
	
	fillArray(var, array, c, BASE64_BYTES_NUMBER);
	
	createSingleBinary(array, BYTE_SIZE, &binary, BASE64_BYTES_NUMBER);
	
	separateBitsToSomeSize(base64CharArray, binary, asciiCharArraySize, BASE64_WORD_SIZE, COMPLETE_BASE64);
	
	base64IndexToValue(base64CharArray);
	
	write(toWrite, base64CharArray, 4);	

}

void decode(FILE * toWrite, char * c, int var) {
	
	int arrayAscii[3];
	unsigned binary = 0;
	int bitsToMove;	
	int array[4];
		
	fillArray(var, array, c, 4);
	
	convertArrayToBase64Index(array);

	createSingleBinary(array, BASE64_WORD_SIZE, &binary, 4);	
	
	separateBitsToSomeSize(arrayAscii, binary, ASCII_ARRAY_SIZE, BYTE_SIZE, COMPLETE_ASCII);

	write(toWrite, arrayAscii, 3);

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

void write(FILE * toWrite, unsigned * v, int size) {
	for(int i = 0; i < size; i++) {
		if (v[i] == 0) {
			continue;
		}
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

void convertArrayToBase64Index(int * v) {
	for (int i = 0; i < 4; i++) {
		v[i] = base64ValueToIndex(v[i]);
	}
}

int base64ValueToIndex(int number) {

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

void base64IndexToValue(int * array) {
	
	for (int i = 3; i >= 0; i--) {
		
		if (i == 3 && array[i] == 0) {
			array[i] = BASE64_EMPTY_VALUE;
		} else if ( i < 3 && array[i + 1] == BASE64_EMPTY_VALUE && array[i] == 0) {
			array[i] = BASE64_EMPTY_VALUE;	
		} else {
			array[i] = base64Table[array[i]];
		}
	}
}

void getFilesPath(char * toReadPath, char * toWritePath) {
	
	printf("Caminho do arquivo fonte:\n");
	scanf("%s", toReadPath);
	
	printf("Caminho do arquivo destino:\n");
	scanf("%s", toWritePath);
}

void openFiles(char * toReadPath, char * toWritePath, FILE ** toRead, FILE ** toWrite) {
	
	*toRead = fopen(toReadPath, "r");
	*toWrite = fopen(toWritePath, "w");
	
	
	if (*toRead == NULL || *toWrite == NULL) {
		printf("Erro ao tentar ler um dos arquivos");
		exit(1);
	}
}

int defineWordSize(char c) {
	if (c == 'c') {
		return 3;
	} else {
		return 4;
	}
}

void readAndWrite(FILE * toWrite, FILE * toRead, char * readed, char option) {
	
	char readedChar;
	
	readed[0] = fgetc(toRead);
	int counter = 1;
	char test;
	
	int var = 0;
	
	int wordSize = defineWordSize(option);
	
	while(!feof(toRead)) {
		
		for(int i = 0; i < wordSize; i ++) {
			
			test = fgetc(toRead);
			
			if (test != EOF) {
				readed[counter] = test;
			}
			counter++;	
			
		}
		
		if (option == 'c') {
			encode(toWrite, readed, var);
		} else {
			decode(toWrite, readed, var);
		}
		
		
		var++;			
	}
	
}

void getOption(char * option) {
	printf("Codificar ou Decodificar? Escolha 'c' ou 'd'\n");
	scanf("%c", option);
	
	if (!(*option == 'c' || *option == 'd')) {
		printf("opcao escolhida nao pode ser aceita.");
		exit(1);
	}
}
