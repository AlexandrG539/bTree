#include <stdlib.h>
#include "structs.h"
#include "create.h"
#include "insert.h"
#include "print.h"
#include <stdio.h>
#include "search.h"
#include "remove.h"

int main () {
	struct bTree *tree = createTree(3);
	insert(tree, 1); 
    insert(tree, 3); 
    insert(tree, 7); 
    insert(tree, 10); 
    insert(tree, 11); 
    insert(tree, 13); 
    insert(tree, 14); 
    insert(tree, 15); 
    insert(tree, 18); 
    insert(tree, 16); 
    insert(tree, 19); 
    insert(tree, 24); 
    insert(tree, 25); 
    insert(tree, 26); 
    insert(tree, 21); 
    insert(tree, 4); 
    insert(tree, 5); 
    insert(tree, 20); 
    insert(tree, 22); 
    insert(tree, 2); 
    insert(tree, 17); 
    insert(tree, 12); 
    insert(tree, 6);
	printTree(tree->root, tree->order, 0);
	if (search(tree->root, 6) == 0) {
		printf("test failed\n");
		return 1;
	}
	removeFromTree(6, tree);
	if (search(tree->root, 6) != 0) {
		printf("test failed\n");
		return 1;
	}
	printf("test passed\n");
	return 0;
}
