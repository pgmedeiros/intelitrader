#include <stdio.h>
#include <stdlib.h>

#define SON_LEFT(i) (2 * i + 1)
#define SON_RIGHT(i) (2 * i + 2)
#define RIGHT 1
#define LEFT -1

typedef struct node Node;

Node * getNode();
int calculateHeight(Node * node);
int calculateBFactor(Node * root);
Node * rotateLeft(Node * root, Node * pai, int direction);
Node * rotateRight(Node * root, Node * pai, int direction);
Node * insertOrUpdate (Node * root, Node * pai, Node * node, int direction);

void binaryTreeToArray(Node * root, Node * vector);

void downHeap(Node * vector, int size, int i);
void heapify(Node * vector, int m);
void getMax(Node * vector, int m, Node * ptrNode);

void getFilesPath(char * toReadFile, char * toWriteFile);
void openFiles(char * toReadFile, char * toWriteFile, FILE ** toRead, FILE ** toWrite);
void read(FILE * toRead, Node ** root);
void write(Node * elements, FILE * toWrite);

struct node {
	
	Node * right;
	Node * left;
	int key;
	int value;
	int bfactor;
	int height;
	
};

int size = 1;
int v_size = 0;

int main( void ) {

	Node * root = NULL;
	char toReadFile[100];
	char toWriteFile[100];
	FILE * toRead;
	FILE * toWrite;
		
	getFilesPath(toReadFile, toWriteFile);
		
	openFiles(toReadFile, toWriteFile, &toRead, &toWrite);

	read(toRead, &root);
	
	Node * vector = (Node *) malloc(size * sizeof(Node));
	
	binaryTreeToArray(root, vector);

	heapify(vector, v_size);

	write(vector, toWrite);
	
	fclose(toWrite);
	fclose(toRead);

	return 0;
	
}


Node * getNode() {
	Node * node = (Node *) malloc(sizeof(Node));
	node->value = 1;
	node->left = NULL;
	node->right = NULL;
	node->key = -1;
	node->bfactor = 0; 
	node->height = 0;
}

int calculateHeight(Node * node) {
	
	if (node->right == NULL && node->left == NULL) {
		return 0;
	}
	
	if (node->right != NULL && node->left == NULL) {
		return node->right->height + 1;
	}
	
	if (node->right == NULL && node->left != NULL) {
		return node->left->height + 1;
	}
	
	if (node->right != NULL && node->left != NULL) {
		if (node->right->height > node->left->height) {
			return node->right->height + 1;
		} else {
			return node->left->height + 1;
		}
 	}
	
}

int calculateBFactor(Node * root) {
	
	if (root->right == NULL) {
		root->bfactor = -(root->left->height + 1);
	} else if (root->left == NULL) {
		root->bfactor = root->right->height + 1;
	} else {
		root->bfactor = (root->right->height) - (root->left->height);
	}
	
	return root->bfactor;
}

Node * rotateLeft(Node * root, Node * pai, int direction) {
	
	Node * aux = NULL; 
	Node * rightLeft = NULL;
	
	aux = root; 
		
	if (root->right->left != NULL) {
		rightLeft = root->right->left;
	}
		
	root = root->right;
	
	aux->right = rightLeft;
		
	root->left = aux;
	
	root->left->height = calculateHeight(root->left);
	
	root->height = calculateHeight(root);	
	root->bfactor = calculateBFactor(root);
	
		
	if (pai == NULL) {
		return root;
	}
	
	if (direction == RIGHT) {
		pai->right = root;
	}		
	if (direction == LEFT) {
		pai->left = root;
	} 
		
	return root;
}

Node * rotateRight(Node * root, Node * pai, int direction) {
	Node * aux = NULL; 
	Node * rootLeftRight = NULL;
	
	aux = root;
	
	if (root->left->right != NULL) {
		rootLeftRight = root->left->right;
	}
	
	root = root->left;
	aux->left = rootLeftRight;
	root->right = aux;
	
	root->right->height = calculateHeight(root->right);
	root->height = calculateHeight(root);
	root->bfactor = calculateBFactor(root);
	
	if (pai == NULL) {
		return root;
	}
	
	if (direction == RIGHT) {
		pai->right = root;
	}
			
	if (direction == LEFT) {
		pai->left = root;
	} 
		
	return root;
}

Node * insertOrUpdate (Node * root, Node * pai, Node * node, int direction) {
	
	Node * retorno;
	
	if (node->key == root->key) {
		root->value++;
	}
	
	if (node->key > root->key && root->right != NULL) {
		retorno = insertOrUpdate(root->right, root, node, RIGHT);
	}
	
	if (node->key < root->key && root->left != NULL) {
		retorno = insertOrUpdate(root->left, root, node, LEFT);
	}
	
	if (node->key > root->key && root->right == NULL) {
		root->right = node;
		if (root->left == NULL) {
			root->height += 1;
		}
		size++;
	}
	
	if (node->key < root->key && root->left == NULL) {
		root->left = node;
		if (root->right == NULL) {
			root->height += 1;
		}
		size++;
	}
	
	if (root->left != NULL || root->right != NULL) {
		root->height = calculateHeight(root);
		root->bfactor = calculateBFactor(root);
	}
	
	if (root->left != NULL) {
		
		if (root->bfactor <= -2 && root->left->bfactor <= -1) { 
			root = rotateRight(root, pai, direction);
		}
		if (root->bfactor <= -2 && root->left->bfactor >= 1) {
			rotateLeft(root->left, root, LEFT); 
			root = rotateRight(root, pai, direction);
		}
	}
	
	if (root->right != NULL) {
		
		if (root->right != NULL && root->bfactor >= 2 && root->right->bfactor >= 1) { 
			root = rotateLeft(root, pai, direction);
		} 
		
		if (root->right != NULL && root->bfactor >= 2 && root->right->bfactor <= -1) {
			rotateRight(root->right, root, RIGHT); 
			root = rotateLeft(root, pai, direction);
		}	
		
	}
		
	return root;
}

void binaryTreeToArray(Node * root, Node * vector) {
		
	if (root->left != NULL) {
		binaryTreeToArray(root->left, vector);
	}
	
	vector[v_size] = *root;
	v_size++;
	
	if (root->right != NULL) {
		binaryTreeToArray(root->right, vector);
	}
	
	return;
}


void downHeap(Node * vector, int size, int i) {
	
	Node aux;
	
	while ((vector[SON_RIGHT(i)].value > vector[i].value || vector[SON_LEFT(i)].value > vector[i].value)
			&& (SON_RIGHT(i) <= size && SON_LEFT(i) <= size)) {
				
		if (vector[SON_RIGHT(i)].value > vector[i].value && vector[SON_RIGHT(i)].value >= vector[SON_LEFT(i)].value) {
			aux = vector[i];
			vector[i] = vector[SON_RIGHT(i)];
			vector[SON_RIGHT(i)] = aux;
			
			i = SON_RIGHT(i);
			
		} else if (vector[SON_LEFT(i)].value > vector[i].value && vector[SON_LEFT(i)].value > vector[SON_RIGHT(i)].value) {
			aux = vector[i];
			vector[i] = vector[SON_LEFT(i)];
			vector[SON_LEFT(i)] = aux;
			i = SON_LEFT(i);
		} 
		
	}
}

void heapify(Node * vector, int m) {
	for (int i = m/2; i>=0; i--) {
		downHeap(vector, m, i);
	}
}

void getMax(Node * vector, int m, Node * ptrNode) {
	
	*ptrNode = vector[0];
	vector[0] = vector[m - 1];
	downHeap(vector, m - 1, 0);
	v_size--;
	
}

void getFilesPath(char * toReadFile, char * toWriteFile) {
	printf("Escreva o caminho do arquivo para ser lido: ");
	scanf("%s", toReadFile);
	
	printf("Escreva o caminho do arquivo para ser escrito: ");
	scanf("%s", toWriteFile);
}

void openFiles(char * toReadFile, char * toWriteFile, FILE ** toRead, FILE ** toWrite) {
	
	*toRead = fopen(toReadFile, "r");
	
	*toWrite = fopen(toWriteFile, "w");
	
	if (*toRead == NULL || *toWrite == NULL) {
		printf("Erro ao abrir o(s) arquivo(s)");
		exit(1);
	}
}

void read(FILE * toRead, Node ** root) {
	
	int c = fgetc(toRead);
	
	if (c == -1) {
		printf("Nao foi possível ler o arquivo.");
		exit(1);
	}
	
	while (!feof(toRead)) {
		
		if (*root == NULL) {
			*root = getNode();
			(*root)->key = c;
			c = fgetc(toRead);
			continue;
		}
		
		Node * node = getNode();
		node->key = c;
		
		*root = insertOrUpdate(*root, NULL, node, 0);
		
		c = fgetc(toRead);
		
	}
}

void write(Node * elements, FILE * toWrite) {
	
	Node * ptr = (Node *) malloc(sizeof(Node));
	int differentChar = v_size;
	
	for (int i = 0; i < differentChar; i++) {	
		getMax(elements, v_size, ptr);
		fprintf(toWrite,"caractere: %c repeticoes: %i\n", ptr->key, ptr->value);
	}
	
}

