#include "writer.h"

#define SIZE_BYTE 8

void write(FILE *out,FILE *in, simbolo* simbs, int size)
{
	int i;
	char simbInBits[SIZE_BYTE];
	char lenInBits[SIZE_BYTE];
	char chr, x;
	buffer buffer;
	buffer.size = buffer.b = 0;

	putc(size, out);

	for(i = 0; i <= size; i++)
	{
		/*Table*/
			/*Write binary code of current symbol*/
			chr = simbs[i]->simb;
			mkCharBits(chr, simbInBits,SIZE_BYTE);
			/*why do this? i thought if i wrote \n to out it would write a new line*/
			/*Maybe not*/
			writeSimbBin(&buffer, simbInBits, out, SIZE_BYTE);
			/*Write the length of shannon-fano code for the current symbol*/
			mkCharBits(simbs[i]->codeLen, lenInBits, SIZE_BYTE);
			writeSimbBin(&buffer, lenInBits, out, SIZE_BYTE); /*yeah, i know, i should rename that func*/
			/*Write shannon-fano code of current symbol*/
			writeSimbBin(&buffer, simbs[i]->code, out, simbs[i]->codeLen);
	}

	/*Now we start writing the content*/
	
	fseek(in, 0, SEEK_SET);

	while((x = getc(in))!=EOF)
	{
		/*This is stupid simbs is a hashtable i should be calling directly simbs[x]->...*/
		i = lookFor(x, simbs, size);
		writeSimbBin(&buffer, simbs[i]->code, out, simbs[i]->codeLen);
	}
}

int lookFor(char x, simbolo *simbs, int n)
{
	int i;
	for(i = 0; i <= n; i++)
		if(simbs[i]->simb == x)
			break;
	return i;
}

void mkCharBits(char chr, char simbInBits[], int n)
{
	int i;
	for(i = n-1; i>=0; i--)
	{
		simbInBits[i] = chr % 2 == 1 ? '1' : '0';
		chr /= 2;
	}
}

void writeSimbBin(buffer *buffer, char simbInBits[], FILE* out, int n)
{
	int i;
	for(i = 0; i < n; i++)
	{

		if(buffer->size == SIZE_BYTE)
		{
			putc(buffer->b, out);
			buffer->size = buffer->b = 0;
		}

		if(simbInBits[i] == '1')
			buffer->b |= 1 << buffer->size;
		else
		{
			/*Places 1 where 0 must go, nots and ands it with buffer*/
			/*Basically what we'll get is a mask with every bit turned on*/
			/*except the bit that we want to turn to 0*/
			/*AND this mask with the buffer keeps everything the same but*/
			/*that bit we wanted to be zero*/
			buffer->b &= ~(1 << buffer->size);
		}
		
		(buffer->size)++;
	}
}
