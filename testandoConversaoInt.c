#include <stdio.h>


int main( void ) {
	
	// então consigo pegar o inteiro do ascii
	
	int c; 
	
	scanf("%c", &c);
	
	printf("%i\n", c);
	
	intToBinary(c);
	
	return 0;
}

void intToBinary(int number) {
	
	char* colecaoDeChar = malloc(8 * sizeof(char));
	int counter = 7;
	
	while((number / 2) != 0) {
		colecaoDeChar[counter] = number % 2;
		number = number/2;
		counter--;
	}
	
	colecaoDeChar[counter] = number % 2;

	colecaoDeChar[0] = 0;
	
	int x;
	for (x=0; x < 8; x++) {
		printf("%i", colecaoDeChar[x]);
	}
}
