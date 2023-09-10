#include <stdio.h>


typedef struct node Node;

struct node {
	
	Node * right;
	Node * left;
	int key;
	int value;
	
};

Node * getNode() {
	Node * node = (Node *) malloc(sizeof(Node));
	node->value = 0;
	node->left = NULL;
	node->right = NULL;
	node->key = NULL;
}

void insert(Node * root, Node * node) {
	
	Node * current = root;
	Node * father;
	
	while(current != NULL) {
		
		if (node->key == current->key){
			break;
		}else if (node->key > current->key) {
			father = current;
			current = current->right;
		} else {
			father = current;
			current = current->left;
		}
	}
	
	if(current != NULL) {
		current->value++;
		return;
	}
		
	if (current == NULL && node->key > father->key) {
		father->right = node;
		return;
	}
	if (current == NULL && node->key < father->key) {
		father->left = node;
		return;
	}
}

int main( void ) {
	
	Node * root = getNode();
	root->value = 1;
	root->key = 10;	
	
	Node * nodeToInsert = getNode();
	nodeToInsert->key = 10;
	
	Node * nodeToInsert2 = getNode();
	nodeToInsert2->key = 20;
	
	insert(root, nodeToInsert);
	insert(root, nodeToInsert2);

	printf("o proximo valor sera zero %i", root->right->value);
	
	
	

}
