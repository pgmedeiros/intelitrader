#include <stdio.h>

#define BYTE_SIZE 8
#define BASE64_BLOCK_SIZE 24
#define BASE64_BYTES_NUMBER 3

int* decimalToBinary(int decimal);

int putInBase64Blocks(int binary);

int main( void ) {
		
	int c; 
	
	scanf("%i", &c);
		
	putInBase64Blocks('C');

	
	return 0;
}

int getFirstBlock(int base64block, int position) {
	
	unsigned long base64cell1 = 0 << 7;		
	unsigned base64block1 = 0 << 7;
	
	int bitsParaEsquerda;
	
	switch (position) {
		
		case 1:
			bitsParaEsquerda = 18;
			break;
		case 2: 
			bitsParaEsquerda = 12; 
			break;
		case 3: 
			bitsParaEsquerda = 6;
			break;
		case 4:		
			bitsParaEsquerda = 0;

	}
			
	
	unsigned mask = 63; 
						
	mask = mask << bitsParaEsquerda;

	base64cell1 = (base64block & mask);
	
	base64cell1 >>= bitsParaEsquerda;
		
	printf("%i bloco 1\n", base64cell1);
	return base64cell1;
}

int putInBase64Blocks(int number) {
		
	unsigned base64block = malloc(BASE64_BYTES_NUMBER);	
	base64block = 0 << 23;
	
	base64block = (number | base64block);
	
	printf("%i aqui \n",base64block );
	
	base64block <<= 16;
	
	int firstBlock = getFirstBlock(base64block, 1);
	int secondBlock = getFirstBlock(base64block, 2);

			
	return 0;
	
}

