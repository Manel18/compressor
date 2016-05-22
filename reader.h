#ifndef READER_H
#define READER_H

#include <stdio.h>

#define symb char
#define SYMBS 256

typedef struct simb{
	symb simb;
	int total;
	float freq;
	symb code[256];
	int codeLen;
}SIMBOLO, *simbolo;

int readFile(FILE*,simbolo*,int*,int*);
void freq(simbolo*, int, int, int);
void printStatus(simbolo*,int, int);
float entropia(simbolo*, int, int);
float max(int);
float information(simbolo);
int shift(simbolo*, int, int);
int shiftAux(simbolo*, int);

#endif

