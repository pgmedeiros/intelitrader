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
	
	if (node->key == root->key) {
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
	
	if (root->bfactor >= 2) {
		printf("%i maior que dois", root->key);
	}
		
	return retorno;
}

int inserir(Node ** root, Node * node) {
	
	int retorno = insertListaRecursivo(*root, node);
	
	if ((**root).bfactor <= -2) {
		
		Node * aux = NULL; 
		Node * leftRight = NULL;
		
		aux = *root;
		
		if ((**root).left->right != NULL) {
			leftRight = (**root).left->right;
		}
		
		*root = (**root).left;
		
		(**root).right = aux;
		
		(**root).right->left = leftRight;
		
	}
	
}


int main( void ) {
	
	Node * root = getNode();
	root->value = 1;
	root->key = 20;	
	
	Node * nodeToInsert = getNode();
	nodeToInsert->key = 15;
	
	Node * nodeToInsert2 = getNode();
	nodeToInsert2->key = 21;
	
	Node * nodeToInsert3 = getNode();
	nodeToInsert3->key = 14;
	
	Node * nodeToInsert4 = getNode();
	nodeToInsert4->key = 16;
	
	Node * nodeToInsert5 = getNode();
	nodeToInsert5->key = 2;
	
	inserir(&root, nodeToInsert);
	inserir(&root, nodeToInsert2);
	inserir(&root, nodeToInsert3);
	inserir(&root, nodeToInsert4);
	inserir(&root, nodeToInsert5);

	printf("menos cinco %i", root->key);
	

}
