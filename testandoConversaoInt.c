#include <stdio.h>

#define BYTE_SIZE 8

int* decimalToBinary(int decimal);

int main( void ) {
	
	// então consigo pegar o inteiro do ascii
	
	int c; 
	
	scanf("%c", &c);
	
	printf("%i\n", c);
	
	int * f = decimalToBinary(c);
	
	for (int x = 0; x < BYTE_SIZE; x ++) {
		printf("%i",f[x]);
	}
	
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
