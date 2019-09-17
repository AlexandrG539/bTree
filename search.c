#include "structs.h"
#include <stdio.h>
#include <stdio.h>

int search(struct node *nd, int value) {
	int i = 0;
	while ((i <= nd->keyCount - 1) && (value > nd->keys[i]))
		i = i + 1;
	if ((i <= nd->keyCount - 1) && (value == nd->keys[i])) {
		printf("value %d was founded\n", value);
		return 1;
	}
	if (nd->leaf) {
		printf("value %d wasn't founded\n", value);
		return 0;
	}
	else return search(&(nd->children[i]), value);
}