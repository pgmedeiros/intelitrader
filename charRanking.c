#include <stdio.h>


typedef struct node Node;

struct node {
	
	Node * right;
	Node * left;
	int key;
	int value;
	int bfactor;
	
};

Node * getNode() {
	Node * node = (Node *) malloc(sizeof(Node));
	node->value = 0;
	node->left = NULL;
	node->right = NULL;
	node->key = NULL;
	node->bfactor = 0; 
}

int insertListaRecursivo(Node * root, Node * node) {
	
	int retorno;
	
	if (node->key == root->key) { // debugar esse if
		root->value++;
		return;
	}
	
	if (node->key > root->key && root->right == NULL) {
		root->right = node;
		root->bfactor += 1;
		return root->bfactor;	
		
	}
	if (node->key < root->key && root->left == NULL) {
		root->left = node;
		root->bfactor += -1;
		return root->bfactor;	
	}
		
	if (node->key > root->key) {
		retorno = insertListaRecursivo(root->right, node);
	}
	
	if (node->key < root->key) {
		retorno = insertListaRecursivo(root->left, node);
	}
	
	root->bfactor += retorno;
	
	return retorno;
	
	
}

int main( void ) {
	
	Node * root = getNode();
	root->value = 1;
	root->key = 10;	
	
	Node * nodeToInsert = getNode();
	nodeToInsert->key = 9;
	
	Node * nodeToInsert2 = getNode();
	nodeToInsert2->key = 20;
	
	Node * nodeToInsert3 = getNode();
	nodeToInsert3->key = 25;
	
	Node * nodeToInsert4 = getNode();
	nodeToInsert4->key = 19;
	
	Node * nodeToInsert5 = getNode();
	nodeToInsert5->key = 2;
	
	Node * nodeToInsert6 = getNode();
	nodeToInsert6->key = 1;
	
	insertListaRecursivo(root, nodeToInsert);
	insertListaRecursivo(root, nodeToInsert2);
	insertListaRecursivo(root, nodeToInsert3);
//	insertListaRecursivo(root, nodeToInsert4);
//	insertListaRecursivo(root, nodeToInsert5);
//	insertListaRecursivo(root, nodeToInsert6);


	printf("menos cinco %i", root->bfactor);

}
