#include "binary_trees.h"

bst_t *bst_insert(bst_t **tree, int value);
/**
 * avl_insert - inserts a value in an AVL Tree
 * @tree: double pointer to the root node of the AVL tree
 * @value: the value to store in the node to be inserted
 * Return:  pointer to the created node, or NULL on failure
 * If the address stored in tree is NULL,
 * the created node must become the root node.
 * The resulting tree after insertion, must be a balanced AVL Tree
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *aux = NULL;
	avl_t *new = NULL;
	int balance = 0;
	int prev_balance = 0;

	new = bst_insert(tree, value);
	aux = new;
	while (aux != NULL)
	{
		prev_balance = balance;
		balance = binary_tree_balance(aux);
		if (balance > 1)
		{
			if (prev_balance < 0)
				binary_tree_rotate_left(aux->left);
			aux = binary_tree_rotate_right(aux);
		}
		else if (balance < -1)
		{
			if (prev_balance > 0)
				binary_tree_rotate_right(aux->right);
			aux = binary_tree_rotate_left(aux);
		}
		if (aux->parent == NULL)
			*tree = aux;

		aux = aux->parent;
	}

	return (new);
}

/**
 * bst_insert - Inserts a value in a Binary Search Tree
 * @tree: double pointer to the root node of the BST to insert the value
 * @value: Value to store in the node to be inserted
 * Return: pointer to the created node, or NULL on failure
 * if tree is NULL, the created node must become the root node.
 * If the value is already present in the tree is ignored
 */
bst_t *bst_insert(bst_t **tree, int value)
{
	bst_t *aux = NULL;

	if (tree == NULL)
		return (NULL);

	if (*tree == NULL)
	{
		*tree = binary_tree_node(NULL, value);
		return (*tree);
	}

	aux = *tree;
	while (1)
	{
		if (aux->n == value)
			return (NULL);
		if (value > aux->n)
		{
			if (aux->right != NULL)
				aux = aux->right;
			else
			{
				aux->right = binary_tree_node(aux, value);
				return (aux->right);
			}
		}
		else
		{
			if (aux->left != NULL)
				aux = aux->left;
			else
			{
				aux->left = binary_tree_node(aux, value);
				return (aux->left);
			}
		}
	}
}
