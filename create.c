#include "structs.h"
#include "create.h"
#include "string.h"

struct bTree *createTree (size_t t) {
	struct bTree *tree = (struct bTree*)malloc(sizeof(struct bTree));
	if (tree == 0)
		return 0;
	tree->order = t;
	tree->root = createNode(t);
	if (tree->root == 0) {
		free (tree);
		return 0;
	}
	else return tree;
}

struct node *createNode (size_t t) {
	struct node *nd = (struct node*)malloc(sizeof(struct node));
	if (nd == 0)
		return 0;
	memset (nd, 0, sizeof(*nd));
	nd->children = (struct node*)malloc(sizeof(struct node) * 2 * t);
	if (nd->children == 0) {
		free (nd);
		return 0;
	}
	memset (nd->children, 0, sizeof(*(nd->children)) * 2 * t);
	nd->keys = (int*)malloc(sizeof(int) * (2 * t - 1));
	if (nd->keys == 0) {
		free (nd);
		return 0;
	}
	memset (nd->keys, 0, sizeof(*(nd->keys)));
	nd->leaf = 1;
	nd->keyCount = 0;
	return nd;
}
