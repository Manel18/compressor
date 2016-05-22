#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "reader.h"

int readFile(FILE*f,simbolo simbs[],int *inf, int *sup)
{
/*	FILE *f;*/
	int s;
	int	sRead = 0;

	*sup = *inf = 0;
/*	f = fopen(file,"r");*/
	
	if(f == NULL)
	{
		printf("Error opening file!\n");
		return 0;
	}

	while((s =(int) fgetc(f))!=EOF)
	{
		if(*inf == 0)
			*inf = s;
		else if(s < *inf)
			*inf = s;


		printf("New Symbol added\n");
		if(!simbs[s])
		{
			simbs[s] = (simbolo)malloc(sizeof(SIMBOLO));
			simbs[s]->simb = s;
			simbs[s]->total = 1;
			simbs[s]->codeLen = 0;
		}
		else
			simbs[s]->total += 1;

		if(s > *sup)
			*sup = s;

		sRead++;
	}
	return sRead;
}

void freq(simbolo simbs[], int inf, int sup, int totalSimb)
{
	int i;
	for(i = inf; i <= sup; i++)
	{
		if(simbs[i])
			simbs[i]->freq = (float)(simbs[i]->total) / (float)totalSimb;
	}
}

void printStatus(simbolo simbs[], int inf, int sup)
{
	int i;
	for(i = inf; i <= sup; i++)
	{
		if(simbs[i])
		{
			if(simbs[i]->simb == '\n')
				printf("New Line Symbol, %0.3f freq\n", simbs[i]->freq);
			else
				printf("%d Symbol - %c, %d times, %0.3f freq\n",i, simbs[i]->simb, simbs[i]->total, simbs[i]->freq);
		}
	}
}

float information(simbolo simb)
{
	return (float)((log10((1/(simb->freq))))/log10(2));
}

float entropia(simbolo simbs[], int inf, int sup)
{
	float total = 0;
	int i;
	for(i = inf; i <= sup; i++)
	{
		if(simbs[i])
			total += information(simbs[i])*(simbs[i]->freq);
	}
	return total;
}

float max(int n)
{
	return (float)(log10(n)/log10(2));
}

int shift(simbolo simbs[], int inf, int sup)
{
	int i;
	int N;
	for(i = inf; i <= sup; i++)
		N = shiftAux(simbs, i);

	return N;
}

int shiftAux(simbolo simbs[], int i)
{
	while(i>0 && !simbs[i-1])
	{
		simbs[i-1] = simbs[i];
		simbs[i] = NULL;
		i--;
	}
	return i;
}
