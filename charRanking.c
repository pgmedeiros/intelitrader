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
	
	if (root->left != NULL || root->right != NULL) {
		
		if (root->left == NULL && root->right != NULL) {
			root->height = root->right->height + 1;
		}
		
		if (root->left != NULL && root->right == NULL) {
			root->height = root->left->height + 1;
		}
		
		if (root->left != NULL && root->right != NULL) {
			if ((root->right->height) > (root->left->height)) {
				root->height = (root->right->height) + 1;
			} else {
			root->height = (root->left->height) + 1;
			}
		}
		
		
	}
		
	if (root->left != NULL || root->right != NULL) {
		
		if (root->right == NULL) {
			root->bfactor = -(root->left->height + 1);
		} else if (root->left == NULL) {
			root->bfactor = root->right->height + 1;
		} else {
			root->bfactor = (root->right->height) - (root->left->height);
		}
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
	
	if (root->bfactor >= 2) { // girar pra esquerda
		
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
	
	Node * nodeToInsert6 = getNode();
	nodeToInsert6->key = 1;
	
	Node * nodeToInsert7 = getNode();
	nodeToInsert7->key = -1;
	
	Node * nodeToInsert8 = getNode();
	nodeToInsert8->key = -2;
	
	Node * nodeToInsert9 = getNode();
	nodeToInsert9->key = 22;
	
	Node * nodeToInsert10 = getNode();
	nodeToInsert10->key = 23;
	
	root = inserir(root, NULL, nodeToInsert, 0);
	root = inserir(root, NULL, nodeToInsert2, 0);
	root = inserir(root, NULL, nodeToInsert3, 0);
	root = inserir(root, NULL, nodeToInsert4, 0);
	root = inserir(root, NULL, nodeToInsert5, 0);
	root = inserir(root, NULL, nodeToInsert6, 0);
	root = inserir(root, NULL, nodeToInsert7, 0);
	root = inserir(root, NULL, nodeToInsert8, 0);
	root = inserir(root, NULL, nodeToInsert9, 0);
	root = inserir(root, NULL, nodeToInsert10, 0);	


	printf("\nroot       %i", root->key == 15);
		printf("\nroot left  %i", root->left->key == 2);
			printf("\nroot left left  %i", root->left->left->key == -1);
				printf("\nroot left left left %i", root->left->left->left->key == -2);
				printf("\nroot left left right %i", root->left->left->right->key == 1);
			printf("\nroot left right  %i", root->left->right->key == 14);
		printf("\nroot right %i", root->right->key == 20);
			printf("\nroot right left %i", root->right->left->key == 16);
			printf("\nroot right right %i", root->right->right->key == 22);
				printf("\nroot right right right %i", root->right->right->right->key == 23);
				printf("\nroot right right left %i", root->right->right->left->key == 21);

		

	

}
