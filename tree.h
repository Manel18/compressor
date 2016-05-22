#ifndef TREE_H
#define TREE_H

#include "reader.h"

/* Esta tree vai conter em cada nodo um bit e sempre que a combinação de nodos
 * de 1 - (n-1) formar um código válido,esse nodo terá também o simbolo
 * corresondente a esse código;
 * Para esse efeito pensei em por -1 na raíz e depois todos os nodos á esquerda
 * são para os códigos que começam em 0, e os da direita os códigos que começam
 * em 1;
 */
typedef struct tree{
	char bit;
	simbolo s;
	struct tree* next;
}*codeTree;

codeTree initTree();
codeTree newNode(char bit);
int symbol(codeTree node);

#endif
