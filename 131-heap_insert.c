#include "binary_trees.h"

/**
 * heap_insert -  inserts a value into a Max Binary Heap
 * @root: double pointer to the root node of the Heap
 * @value: value store in the node to be inserted
 * Return: pointer to the inserted node, or NULL on failure
 * If the address stored in root is NULL,
 * the created node must become the root node.
 * Max Heap ordering
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *aux = NULL, *new = NULL;
	int balance = 0, aux_value = 0;

	if (root == NULL)
		return (NULL);
	if (*root == NULL)
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}
	aux = *root;
	while (aux->left && aux->right)
	{
		balance = binary_tree_balance(aux);
		if ((balance > 0 && binary_tree_is_perfect(aux->left) == 1) ||
			(binary_tree_is_perfect(aux->right) == 0))
			aux = aux->right;
		else
			aux = aux->left;
	}
	if (aux->left == NULL)
	{
		new = binary_tree_node(aux, value);
		aux->left = new;
	}
	else
	{
		new = binary_tree_node(aux, value);
		aux->right = new;
	}
	while (new->parent != NULL && new->n > new->parent->n)
	{
		aux_value = new->parent->n;
		new->parent->n = new->n;
		new->n = aux_value;
		new = new->parent;
	}
	return (new);
}

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

size_t height_recursion(const binary_tree_t *tree, size_t count);
size_t leaves_recursion(const binary_tree_t *tree, size_t count);

/**
 * binary_tree_is_perfect - checks if a binary tree is perfect
 * A perfect binary tree is one that all internal nodes have two children
 * and all leaves are at same level
 * @tree: pointer to the root node of the tree to check
 * Return: 1 if perfect, 0 otherwise
 * If tree is NULL, your function must return 0
 */
int binary_tree_is_perfect(const binary_tree_t *tree)
{
	size_t height = 0;
	size_t leaves = 0;
	size_t expected_leaves = 1;
	size_t count;

	if (tree == NULL)
		return (0);

	height = height_recursion(tree, 0);
	leaves = leaves_recursion(tree, 0);

	for (count = 0; count < height; count++)
		expected_leaves = expected_leaves * 2;

	if (expected_leaves == leaves)
		return (1);

	return (0);
}

/**
 * leaves_recursion - aux function for recursion
 * @tree: pointer to the root node of the tree to count the number of leaves
 * @count: Counter of leaves
 * Return: Number of leaves
 */
size_t leaves_recursion(const binary_tree_t *tree, size_t count)
{
	if (tree->left != NULL)
		count = leaves_recursion(tree->left, count);

	if (tree->right != NULL)
		count = leaves_recursion(tree->right, count);

	if (tree->right == NULL && tree->left == NULL)
		return (count + 1);

	return (count);
}

/**
 * height_recursion - aux function for recursion
 * @tree: pointer to tree
 * @count: counter of height
 * Return: height
 */
size_t height_recursion(const binary_tree_t *tree, size_t count)
{
	size_t count_r = 0;
	size_t count_l = 0;

	if (tree->left != NULL)
		count_l = height_recursion(tree->left, count + 1);

	if (tree->right != NULL)
		count_r = height_recursion(tree->right, count + 1);

	if (tree->left == NULL && tree->right == NULL)
		return (count);

	if (count_r > count_l)
		return (count_r);
	else
		return (count_l);
}
