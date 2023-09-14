#include <stdio.h>
#define DEBUG 0
#define SON_LEFT(i) (2 * i + 1)
#define SON_RIGHT(i) (2 * i + 2)
#define FATHER(i) ((i - 1) / 2)
#define TESTA_HEAPFY 1

typedef struct node Node;

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

Node * getNode() {
	Node * node = (Node *) malloc(sizeof(Node));
	node->value = 1;
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
		
		if (direction == 1) {
			pai->right = root;
		}		
		if (direction == -1) {
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
		
		if (direction == 1) {
			pai->right = root;
		}		
		if (direction == -1) {
			pai->left = root;
		} 
		
	return root;
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


Node * insertOrUpdate (Node * root, Node * pai, Node * node, int d) {
	
	Node * retorno;
	int direction;
	
	if (node->key == root->key) {
		root->value++;
	}
	
	if (node->key > root->key && root->right != NULL) {
		direction = 1;
		retorno = insertOrUpdate(root->right, root, node, direction);
	}
	
	if (node->key < root->key && root->left != NULL) {
		direction = -1;
		retorno = insertOrUpdate(root->left, root, node, direction);
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
		
	if (root->bfactor <= -2 && root->left->bfactor <= -1) { 
		root = rotateRight(root, pai, direction);
	}
	
	if (root->bfactor >= 2 && root->right->bfactor >= 1) { 
		root = rotateLeft(root, pai, direction);
	} 
	
	if (root->left != NULL && root->right != NULL) {
			
		if (root->bfactor >= 2 && root->right->bfactor <= -1) {
			rotateRight(root->right, root, direction); 
			root = rotateLeft(root, pai, direction);
		}
		
		if (root->bfactor <= -2 && root->left->bfactor >= 1) {
			rotateLeft(root->left, root, direction); 
			root = rotateRight(root, pai, direction);
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
	downHeap(vector, m, 0);
	v_size--;
	
}


int main( void ) {
	
	
	
	if(DEBUG) {
		
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
		
		root = insertOrUpdate(root, NULL, nodeToInsert, 0);
		root = insertOrUpdate(root, NULL, nodeToInsert2, 0);
		root = insertOrUpdate(root, NULL, nodeToInsert3, 0);
		root = insertOrUpdate(root, NULL, nodeToInsert4, 0);
		root = insertOrUpdate(root, NULL, nodeToInsert5, 0);
		root = insertOrUpdate(root, NULL, nodeToInsert6, 0);
		root = insertOrUpdate(root, NULL, nodeToInsert7, 0);
		root = insertOrUpdate(root, NULL, nodeToInsert8, 0);
		root = insertOrUpdate(root, NULL, nodeToInsert9, 0);
		root = insertOrUpdate(root, NULL, nodeToInsert10, 0);
		
		printf("||||||||||||||||||||||||||||||");

	printf("\na root %i, valor: %i", root->key == 15, root->key);
		printf("\nbroot %i, valor: %i", root->left->key == 2, root->left->key);
			printf("\ncroot %i, valor: %i", root->left->left->key == -1, root->left->left->key);
				printf("\ndroot %i, valor: %i", root->left->left->left->key == -2, root->left->left->left->key);
				printf("\neroot %i, valor: %i", root->left->left->right->key == 1, root->left->left->right->key);
			printf("\nfroot %i, valor: %i", root->left->right->key == 14, root->left->right->key);
		printf("\ngroot %i, valor: %i", root->right->key == 20, root->right->key);
			printf("\nhroot %i, valor: %i", root->right->left->key == 16, root->right->left->key);
			printf("\niroot %i, valor: %i", root->right->right->key == 22, root->right->right->key);
				printf("\njroot %i, valor: %i", root->right->right->right->key == 23, root->right->right->right->key);
				printf("\nkroot %i, valor: %i", root->right->right->left->key == 21, root->right->right->left->key);
	
	}
	
		
	printf("\n \n |||||||||||||||||||||");
	
	

	if (DEBUG) {
		Node * root2 = getNode();
	root2->key = 67;
	
	Node * _2nodeToInsert = getNode();
	_2nodeToInsert->key = 54;
	
	Node * _2nodeToInsert2 = getNode();
	_2nodeToInsert2->key = 90;
	
	Node * _2nodeToInsert3 = getNode();
	_2nodeToInsert3->key = 29;
	
	Node * _2nodeToInsert4 = getNode();
	_2nodeToInsert4->key = 60;
	
	Node * _2nodeToInsert5 = getNode();
	_2nodeToInsert5->key = 58;
	
	root2 = insertOrUpdate(root2, NULL, _2nodeToInsert, 0);
	root2 = insertOrUpdate(root2, NULL, _2nodeToInsert2, 0);
	root2 = insertOrUpdate(root2, NULL, _2nodeToInsert3, 0);
	root2 = insertOrUpdate(root2, NULL, _2nodeToInsert4, 0);
	root2 = insertOrUpdate(root2, NULL, _2nodeToInsert5, 0);
		printf("\nroot %i, valor: %i", root2->key == 60, root2->key);
		printf("\nroot %i, valor: %i", root2->right->key == 67, root2->right->key);
			printf("\nroot %i, valor: %i", root2->right->right->key == 90, root2->right->right->key);
		printf("\nroot %i, valor: %i", root2->left->key == 54, root2->left->key);
			printf("\nroot %i, valor: %i", root2->left->left->key == 29, root2->left->left->key);
			printf("\nroot %i, valor: %i", root2->left->right->key == 58, root2->left->right->key);


	printf("\n \n |||||||||||||||||||||");
		
	}
	
	if (DEBUG) {
		
		Node * root3 = getNode();
		root3->key = 60;
		
		Node * _3nodeToInsert = getNode();
		_3nodeToInsert->key = 35;
		
		Node * _3nodeToInsert2 = getNode();
		_3nodeToInsert2->key = 83;
		
		Node * _3nodeToInsert3 = getNode();
		_3nodeToInsert3->key = 71;
		
		Node * _3nodeToInsert4 = getNode();
		_3nodeToInsert4->key = 97;
		
		Node * _3nodeToInsert5 = getNode();
		_3nodeToInsert5->key = 65;
		
		root3 = insertOrUpdate(root3, NULL, _3nodeToInsert, 0);
		root3 = insertOrUpdate(root3, NULL, _3nodeToInsert2, 0);
		root3 = insertOrUpdate(root3, NULL, _3nodeToInsert3, 0);
		root3 = insertOrUpdate(root3, NULL, _3nodeToInsert4, 0);
		root3 = insertOrUpdate(root3, NULL, _3nodeToInsert5, 0);
		printf("\nroot %i, valor: %i", root3->key == 71, root3->key);
		printf("\nroot %i, valor: %i", root3->right->key == 83, root3->right->key);
			printf("\nroot %i, valor: %i", root3->right->right->key == 97, root3->right->right->key);
		printf("\nroot %i, valor: %i", root3->left->key == 60, root3->left->key);
			printf("\nroot %i, valor: %i", root3->left->left->key == 35, root3->left->left->key);
			printf("\nroot %i, valor: %i", root3->left->right->key == 65, root3->left->right->key);	
		
	}
	
	Node * root;
	
	if(TESTA_HEAPFY) {
		
		
		root = getNode();
		root->value = 20;
		root->key = 20;	
		
		Node * nodeToInsert = getNode();
		nodeToInsert->key = 15;
		nodeToInsert->value = 15;

		
		Node * nodeToInsert2 = getNode();
		nodeToInsert2->key = 21;
		nodeToInsert2->value = 21;

		
		Node * nodeToInsert3 = getNode();
		nodeToInsert3->key = 14;
		nodeToInsert3->value = 14;

		
		Node * nodeToInsert4 = getNode();
		nodeToInsert4->key = 16;
		nodeToInsert4->value = 16;

		
		Node * nodeToInsert5 = getNode();
		nodeToInsert5->key = 2; 
		nodeToInsert5->value = 2;

		
		Node * nodeToInsert6 = getNode();
		nodeToInsert6->key = 1;
		nodeToInsert6->value = 1;


		root = insertOrUpdate(root, NULL, nodeToInsert, 0);
		root = insertOrUpdate(root, NULL, nodeToInsert2, 0);
		root = insertOrUpdate(root, NULL, nodeToInsert3, 0);
		root = insertOrUpdate(root, NULL, nodeToInsert4, 0);
		root = insertOrUpdate(root, NULL, nodeToInsert5, 0);
		root = insertOrUpdate(root, NULL, nodeToInsert6, 0);
		
		
	}
	
	Node * vector = (Node *) malloc(size * sizeof(Node));
	
	binaryTreeToArray(root, vector);
	
	for (int i = 0; i < v_size; i++) {
		printf("%i ", vector[i].key);
	}
	
	printf("\n");
	
	heapify(vector, v_size);
	
	for (int i = 0; i < v_size; i++) {
		printf("%i ", vector[i].key);
	}
	
	Node * ptr;
	
	getMax(vector, v_size, ptr);
	
	printf("\n %i", ptr->value);
	return 0;
	

}
