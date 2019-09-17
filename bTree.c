#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structs.h"
#include "create.h"
#include "insert.h"
#include "print.h"
#include "search.h"
#include "remove.h"

int console(struct bTree *tree);

int main (int argc, char **argv) {
	size_t t;
	int check;
	if (argc != 3) {
		printf("Parameters entered incorrectly\n");
        printf("syntax : \n\t-t minimum degree\n", argv[0]);
        return 1;
    }
	if(!strcmp(argv[1], "t")) {
		printf("wrong flag\n");
		return 1;
	}
	if (sscanf(argv[2], "%d", &t) != 1)
		printf("wrong parameter\n");
	if (sscanf(argv[2], "%d", &check) != 1)
		printf("wrong parameter\n");
	if (check <=1)
		printf ("t must be greater then 1\n");
	struct bTree *tree = createTree(t);
	for(;;) {
		console(tree);
	}	
	return 0;
}

int console(struct bTree *tree) {
	int value;
	char name[256];
	scanf("%s", name);
	if(!strcmp("insert", name)){
		if (scanf("%d", &value) == 1)
			insert(tree, value);
		else 
			printf ("wrong format of value");
	}
	else if(!strcmp("remove", name)){
		if (scanf("%d", &value) == 1)
			removeFromTree(value, tree);
		else 
			printf ("wrong format of value");
	}
	else if(!strcmp("search", name)){
		if (scanf("%d", &value) == 1)
			search(tree->root, value);
		else 
			printf ("wrong format of value");
	}
	else if(!strcmp("print", name))
		printTree(tree->root, tree->order, 0);
	else if(!strcmp("exit", name)) 
		exit(0);
	else
		printf("Unknown [%s]\n", name);
	return 0;
}
