#include<stdio.h>
#include<stdlib.h>

typedef struct bstnode
{
	int key;
	struct bstnode *left, *right;
}bstnode;

bstnode *newNode(int item)
{
	bstnode *temp = malloc(sizeof(bstnode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

void inorder(bstnode *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d ", root->key);
		inorder(root->right);
	}
}

bstnode* insert(bstnode* node, int key)
{ 
	if (node == NULL) return newNode(key); 
	if (key < node->key)
		node->left  = insert(node->left, key);
	else
		node->right = insert(node->right, key); 
	return node;
}

bstnode * minValueNode(bstnode* node)
{
	bstnode* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

bstnode* deleteNode(bstnode* root, int key)
{
	if (root == NULL)
		return root;
	if (key < root->key)
		root->left = deleteNode(root->left, key);
  
	else if (key > root->key)
		root->right = deleteNode(root->right, key);

	else
	{
		if (root->left == NULL)
		{
			bstnode *temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			bstnode *temp = root->left;
			free(root);
			return temp;
		}
		bstnode* temp = minValueNode(root->right);
		root->key = temp->key;
		root->right = deleteNode(root->right, temp->key);
	}
	return root;
}

// Driver Program to test above functions
int main()
{ 
	return 0;
}
