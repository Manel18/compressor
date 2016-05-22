#ifndef CODIFICA_H
#define CODIFICA_H

#include "reader.h"

void swap(simbolo*, int, int);
void ordena(simbolo*, int, int);
void merge(simbolo*, int, int, int);
void shannon(simbolo*,int, int);
float searchHalfs(simbolo*, int, int, float, int*);
void charcat(char*, char, int);

#endif
