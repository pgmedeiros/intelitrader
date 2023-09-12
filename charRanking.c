#include <stdio.h>


typedef struct node Node;

struct node {
	
	Node * right;
	Node * left;
	int key;
	int value;
	int bfactor;
	int height;
	
};

Node * getNode() {
	Node * node = (Node *) malloc(sizeof(Node));
	node->value = 0;
	node->left = NULL;
	node->right = NULL;
	node->key = NULL;
	node->bfactor = 0; 
	node->height = 0;
}

int calculateHeight(Node * node) {
	
	if (node->right == NULL && node->left == NULL) {
		return 0;
	}
	
	if (node->right != NULL && node->left == NULL) {
		return node->right + 1;
	}
	
	if (node->right == NULL && node->left != NULL) {
		return node->left + 1;
	}
	
	if (node->right != NULL && node->left != NULL) {
		if (node->right->height > node->left->height) {
			return node->right->height + 1;
		} else {
			return node->left->height + 1;
		}
 	}
	
}

int calculateBFactor(Node * node) {
	return node->right->height - node->left->height;
}


Node * inserir (Node * root, Node * pai, Node * node, int d) {
	
	Node * retorno;
	int direction;
	
	if (node->key > root->key && root->right != NULL) {
		direction = 1;
		retorno = inserir(root->right, root, node, direction);
	}
	
	if (node->key < root->key && root->left != NULL) {
		direction = -1;
		retorno = inserir(root->left, root, node, direction);
	}
	
	if (node->key > root->key && root->right == NULL) {
		root->right = node;
		if (root->left == NULL) {
			root->height += 1;
		}
	}
	
	if (node->key < root->key && root->left == NULL) {
		root->left = node;
		if (root->right == NULL) {
			root->height += 1;
		}
	}
	
	if (root->left != NULL && root->right != NULL) {
		
		if ((root->right->height) > (root->left->height)) {
			root->height = (root->right->height) + 1;
		} else {
			root->height = (root->left->height) + 1;
		}
		
	}
	
	if (root->left != NULL && root->right != NULL) {
		root->bfactor = (root->right->height) - (root->left->height);
	}
		
	if (root->bfactor <= -2) { // girar para a direita;
		
		
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
		
		if (direction == 1) {
			pai->right = root;
		}		
		if (direction == -1) {
			pai->left = root;
		} 
		
	}
	
	
	return root;
	
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
	
	root = inserir(root, NULL, nodeToInsert, 0);
	root = inserir(root, NULL, nodeToInsert2, 0);
	root = inserir(root, NULL, nodeToInsert3, 0);
	root = inserir(root, NULL, nodeToInsert4, 0);
	root = inserir(root, NULL, nodeToInsert5, 0);

	printf("menos cinco %i", root->key);
	

}
