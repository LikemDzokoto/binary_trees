#include "binary_trees.h"

/**
 * binary_tree_insert_left - inserts a node as the left of another node
 * @parent: pointer to the node to insert the left-child in
 * @value: value to put in the new node
 * Return: pointer to created node
 */
binary_tree_t *binary_tree_insert_left(binary_tree_t *parent, int value)
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

	if (parent->left != NULL)
	{
		temp->left = parent->left;
		parent->left->parent = temp;
		parent->left = temp;
	}
	parent->left = temp;

	return (temp);
}
