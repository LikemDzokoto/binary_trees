#include "binary_trees.h"

bst_t *bst_search(const bst_t *tree, int value);

/**
 * avl_remove - removes a node from an AVL tree
 * @root: pointer to the root node of the tree for removing a node
 * @value: value to remove in the tree
 * the node containing a value equals to value must be removed and freed
 * If the node to be deleted has two children,
 * it must be replaced with its first in-order successor (not predecessor)
 * After deletion of the desired node, the tree must be rebalanced if necessary
 * Return: pointer to the new root node of the tree after removing
 *  the desired value, and after rebalancing
 */
avl_t *avl_remove(avl_t *root, int value)
{
	avl_t *remove_me = NULL;
	avl_t *parent = NULL;
	avl_t *aux = NULL;
	int balance = 0, prev_balance = 0, val;

	remove_me = bst_search(root, value);
	if (remove_me == NULL)
		return (root);
	parent = remove_me->parent;

	if (remove_me->left == NULL && remove_me->right == NULL)
	{
		if (remove_me->parent == NULL)
			root = NULL;
		else if (remove_me == remove_me->parent->left)
			remove_me->parent->left = NULL;
		else if (remove_me == remove_me->parent->right)
			remove_me->parent->right = NULL;
		free(remove_me);
	}
	else if (remove_me->left != NULL && remove_me->right == NULL)
	{
		if (remove_me->parent == NULL)
			root = remove_me->left;
		else if (remove_me == remove_me->parent->left)
			remove_me->parent->left = remove_me->left;
		else if (remove_me == remove_me->parent->right)
			remove_me->parent->right = remove_me->left;
		remove_me->left->parent = remove_me->parent;
		free(remove_me);
	}
	else if (remove_me->left == NULL && remove_me->right != NULL)
	{
		if (remove_me->parent == NULL)
			root = remove_me->right;
		else if (remove_me == remove_me->parent->left)
			remove_me->parent->left = remove_me->right;
		else if (remove_me == remove_me->parent->right)
			remove_me->parent->right = remove_me->right;
		remove_me->right->parent = remove_me->parent;
	}
	else if (remove_me->left != NULL && remove_me->right != NULL)
	{
		aux = remove_me->right;
		while (aux->left != NULL)
			aux = aux->left;
		val = aux->n;

		avl_remove(root, val);
		remove_me->n = val;
	}
	if (parent != NULL)
		aux = parent;
	else
		aux = root;
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
			root = aux;

		aux = aux->parent;
	}

	return (root);
}

/**
 * bst_search - searches for a value in a Binary Search Tree
 * @tree: pointer to the root node of the BST to search
 * @value: value to search in the tree
 * Return: pointer to the node containing a value equals to value
 * If tree is NULL or if nothing is found, return NULL
 */
bst_t *bst_search(const bst_t *tree, int value)
{
	if (tree == NULL)
		return (NULL);

	while (1)
	{
		if (tree->n == value)
			return ((bst_t *)tree);
		if (tree->right != NULL && value > tree->n)
			tree = tree->right;
		else if (tree->left != NULL && value < tree->n)
			tree = tree->left;
		else
			return (NULL);
	}
}
