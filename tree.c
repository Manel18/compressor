#include "tree.h"

codeTree initTree()
{
	newTree = malloc(sizeof(struct tree));
	newTree->bit = -1;
	newTree->next = NULL;
	return newTree;
}

codeTree newNode(char bit)
{
	node = malloc(sizeof(struct tree));
	node->bit = bit;
	node->next = NULL;
	return node;
}

int symbol(codeTree node)
{
	return if(node->s) ? 1 : 0;
}
