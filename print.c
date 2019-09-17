#include "structs.h"
#include "print.h"
#include <stdio.h>

int printTree (struct node *root, size_t t, int level) {
	if (root == 0) 
		return 0;
	for (int i = 0; i <= root-> keyCount; i++) {
        if (root->leaf == 0) {
			printf ("(");
			printTree(&(root->children[i]), t, level+1);
            printf (")");
        }
        if (i < root->keyCount) 
            printf (" %d ", root->keys[i]);
    }
    if (level == 0)
        printf ("\n");
	return 1;
}
