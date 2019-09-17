#include <stdlib.h>

struct bTree {
	struct node *root;
	size_t order;
};

struct node {
	size_t keyCount;
	int *keys;
	struct node *children;
	size_t leaf;
};