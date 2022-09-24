#include "binary_trees.h"

int balance_recursion(const binary_tree_t *tree, int count);

/**
 * binary_tree_balance - measures the balance factor of a binary tree
 * @tree: pointer to the root node of the tree to measure the balance factor
 * Return: balance factor
 * If tree is NULL, return 0
 */
int binary_tree_balance(const binary_tree_t *tree)
{
	int right_balance = 0;
	int left_balance = 0;

	if (tree == NULL)
		return (0);

	if (tree->left != NULL)
		left_balance = balance_recursion(tree->left, 1);
	if (tree->right != NULL)
		right_balance = balance_recursion(tree->right, 1);

	return (left_balance - right_balance);
}

/**
 * balance_recursion - aux function for recursion
 * @tree: pointer to tree
 * @count: counter of height
 * Return: height
 */
int balance_recursion(const binary_tree_t *tree, int count)
{
	int count_r = 0;
	int count_l = 0;

	if (tree->left != NULL)
		count_l = balance_recursion(tree->left, count + 1);

	if (tree->right != NULL)
		count_r = balance_recursion(tree->right, count + 1);

	if (tree->left == NULL && tree->right == NULL)
		return (count);

	if (count_r > count_l)
		return (count_r);
	else
		return (count_l);
}
