#include "structs.h"
#include <stdio.h>
#include "remove.h"

int findKey (int value, struct node *nd) {
	int ans = 0;
	while (ans < nd->keyCount && nd->keys[ans] < value)
		ans = ans + 1;
	return ans;
}

int removeFromTree(int value, struct bTree *tree) { 
    if (tree->root == 0) { 
        printf ("Tree doesn't exist\n"); 
        return 1; 
    } 
    removeFromNode(value, tree->root, tree->order);
    if (tree->root->keyCount == 0) { 
        struct node *tmp = tree->root; 
        if (tree->root->leaf == 1) 
           tree->root = NULL; 
        else
            tree->root = &(tree->root->children[0]); 
        free (tmp); 
    } 
    return 0; 
} 

int removeFromNode (int value, struct node *nd, size_t t) {
	int i = findKey(value, nd);
	if (i < nd->keyCount && nd->keys[i] == value) { 
        if (nd->leaf == 1) 
            removeFromLeaf(i, nd, t); 
        else
            removeFromNonLeaf(i, nd, t); 
    }
	else {
        if (nd->leaf == 1) { 
            printf ("the key is missing in the tree\n"); 
            return 0; 
        } 
        int flag;
		if (i == nd->keyCount)
			flag = 1;
		else flag = 0;
        if (nd->children[i].keyCount < t) 
            fill(i, nd, t); 
        if (flag && i > nd->keyCount) 
            removeFromNode(value, &(nd->children[i-1]), t);  
        else
            removeFromNode(value, &(nd->children[i]), t);
	}
}

int removeFromLeaf (int i, struct node *nd, size_t t) { 
    for (int j = i + 1; j < nd->keyCount; j++) 
        nd->keys[j-1] = nd->keys[j]; 
    nd->keyCount = nd->keyCount - 1; 
    return 0; 
} 

int removeFromNonLeaf(int i, struct node *nd, size_t t) { 
    int k = nd->keys[i]; 
    if (nd->children[i].keyCount >= t) { 
        int pred = getPred(i, nd);
        nd->keys[i] = pred; 
		removeFromNode(pred, &(nd->children[i]), t);
    } 
    else if  (nd->children[i+1].keyCount >= t) { 
        int succ = getSucc(i, nd); 
        nd->keys[i] = succ;
		removeFromNode(succ, &(nd->children[i+1]), t);
    }  
    else { 
        merge(i, nd, t); 
        removeFromNode(k, &(nd->children[i]), t); 
    } 
    return 0; 
} 

int getPred(int i, struct node *nd) { 
    struct node *cur= &(nd->children[i]); 
    while (cur->leaf != 1) 
        cur = &(cur->children[cur->keyCount]);  
    return cur->keys[cur->keyCount-1]; 
} 

int getSucc(int i, struct node *nd) { 
    struct node *cur = &(nd->children[i+1]); 
    while (cur->leaf != 1) 
        cur = &(cur->children[0]);
    return cur->keys[0]; 
} 

int fill(int i, struct node *nd, size_t t) { 
    if (i != 0 && nd->children[i-1].keyCount >= t) 
        borrowFromPrev(i, nd);
    else if (i != nd->keyCount && nd->children[i+1].keyCount >= t) 
        borrowFromNext(i, nd); 
    else { 
        if (i != nd->keyCount) 
            merge(i, nd, t); 
        else
            merge(i-1, nd, t); 
    } 
    return 0; 
} 

int borrowFromPrev(int i, struct node *nd) { 
    struct node *child = &(nd->children[i]);  
    struct node *sibling = &(nd->children[i-1]); 
    for (int i = child->keyCount - 1; i >= 0; i--) 
        child->keys[i+1] = child->keys[i]; 
    if (child->leaf == 0) { 
        for(int i = child->keyCount; i >= 0; i--) 
			child->children[i+1] = child->children[i];
    } 
    child->keys[0] = nd->keys[i-1]; 
    if(child->leaf == 0) 
        child->children[0] = sibling->children[sibling->keyCount]; 
    nd->keys[i-1] = sibling->keys[sibling->keyCount-1]; 
    child->keyCount = child->keyCount + 1; 
    sibling->keyCount = sibling->keyCount - 1; 
    return 0; 
} 

int borrowFromNext(int i, struct node *nd) { 
    struct node *child = &(nd->children[i]); 
    struct node *sibling = &(nd->children[i+1]); 
    child->keys[(child->keyCount)] = nd->keys[i]; 
    if (child->leaf == 0) 
        child->children[(child->keyCount)+1] = sibling->children[0];  
    nd->keys[i] = sibling->keys[0]; 
    for (int j = 1; j < sibling->keyCount; j++) 
        sibling->keys[j-1] = sibling->keys[j]; 
    if (sibling->leaf == 0) { 
        for(int j = 1; j <= sibling->keyCount; j++) 
            sibling->children[j-1] = sibling->children[j]; 
    } 
    child->keyCount = child->keyCount + 1; 
    sibling->keyCount = sibling->keyCount - 1; 
    return 0; 
} 

int merge(int i, struct node *nd, size_t t) { 
    struct node *child = &(nd->children[i]); 
    struct node *sibling = &(nd->children[i+1]); 
    child->keys[t-1] = nd->keys[i];
    for (int j = 0; j < sibling->keyCount; j++) 
        child->keys[j+t] = sibling->keys[j];
    if (child->leaf == 0) { 
        for(int j = 0; j <= sibling->keyCount; j++) 
            child->children[j+t] = sibling->children[j]; 
    } 
    for (int j = i + 1; j < nd->keyCount; j++) 
        nd->keys[j-1] = nd->keys[j]; 
	child->keyCount = child->keyCount + sibling->keyCount + 1; 
    for (int j = i + 2; j <= nd->keyCount; j++) 
        nd->children[j-1] = nd->children[j];
    nd->keyCount = nd->keyCount - 1;  
    return 0; 
} 

