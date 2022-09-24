#include "binary_trees.h"

/**
 * binary_tree_insert_right - inserts a node as the right of another node
 * @parent: pointer to the node to insert the right-child in
 * @value: value to put in the new node
 * Return: pointer to created node
 */
binary_tree_t *binary_tree_insert_right(binary_tree_t *parent, int value)
{
	binary_tree_t *temp;

	if (parent == NULL)
		return (NULL);

	temp = malloc(sizeof(binary_tree_t));
	if (temp == NULL)
		return (NULL);

	temp->n = value;
	temp->left = NULL;
	temp->parent = parent;
	temp->right = NULL;

	if (parent->right != NULL)
	{
		temp->right = parent->right;
		parent->right->parent = temp;
	}
	parent->right = temp;

	return (temp);
}
