#ifndef WRITER_H
#define WRITER_H

#include "reader.h"
#include <stdio.h>

typedef struct buffer{
	int size;
	char b;
}buffer;

void write(FILE*, FILE*, simbolo*,int);
void writeSimbBin(buffer*, char*, FILE*,int);
void mkCharBits(char, char*, int);
int lookFor(char,simbolo*, int);

#endif
