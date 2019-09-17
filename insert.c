#include "structs.h"
#include "create.h"
#include "insert.h"

int insert (struct bTree *tree, int value) {
	size_t t = tree->order;
	struct node *current = tree->root;
	if (tree->root == NULL) {
		struct node *newRoot = createNode (t);
		tree->root = newRoot;
		tree->root->keys[0] = value;
		tree->root->keyCount = 1;
		return 0;
	}
	if ((current->keyCount) == (2 * t - 1)) {
		struct node *s = createNode (t);
		if (s == 0)
			return 1;
		tree->root = s;
		s->leaf = 0;
		s->children[0] = *current;
		splitting (s, &(s->children[0]), 0, t);
		insertNonFull(s, value, t);
	}
	else insertNonFull(current, value, t);
	return 0;
}
int splitting (struct node *x, struct node *y, int i, size_t t) {
	struct node *z = createNode(t);
	z->leaf = y->leaf;
	z->keyCount = t - 1;
	for (int j = 0; j <= t - 2; j++) {
		z->keys[j] = y->keys[j+t];
		y->keys[j+t] = 0;
	}
	if (y->leaf == 0) {
		for (int j = 0; j <= t - 1; j++) {
			z->children[j] = y->children[j+t];
		}
	}
	y->keyCount = t - 1;
	for (int j = x->keyCount; j >= i + 1; j--) {
		x->children[j+1] = x->children[j];
	}
	x->children[i+1] = *z;
	for (int j = x->keyCount; j >= i - 1; j--) {
		x->keys[j+1] = x->keys[j];
	
	}
	x->keys[i] = y->keys[t-1];
	y->keys[t-1] = 0;
	x->keyCount = x->keyCount + 1;
	return 0;
}

int insertNonFull (struct node *current, int value,  size_t t) {
	size_t i = current->keyCount;
	if (current->leaf != 0) {
		while ((i >= 1) && (value < current->keys[i-1])) {
			current->keys[i] = current->keys[i-1];
			i = i - 1;
		}
		current->keys[i] = value;
		current->keyCount = current->keyCount + 1;
		return 0;
	}
	else {
		while ((i >= 1) && (value < current->keys[i-1])) {
			i = i - 1;
		}
		if (current->children[i].keyCount == (2 * t - 1)) {
			splitting(current, &(current->children[i]), i, t);
			if (value > current->keys[i])
				i = i + 1;
		}
		insertNonFull(&(current->children[i]), value, t);
	}
}