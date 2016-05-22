#include <stdio.h>
#include "codifica.h"
#include <string.h>
#include <math.h>
void swap(simbolo simbs[], int i, int j)
{
	simbolo temp = simbs[i];
	simbs[i] = simbs[j];
	simbs[j] = temp;
}

void ordena(simbolo simbs[], int inf, int sup)
{
	/*insertion sort*/
	int i, j;
	simbolo key;
	for(j = inf+1; j <= sup; j++)
	{
		key = simbs[j];
		i = j-1;
		while(i>=inf && simbs[i]->freq < key->freq)
		{
			simbs[i+1] = simbs[i];
			i--;
		}
		simbs[i+1] = key;
	}
}

/*
void ordena(simbolo simbs[], int inf, int sup)
{
	int meio;
	printf("sorting...\n");
	if(inf < sup)
	{
		meio = (sup + inf)/2;
		ordena(simbs, inf, meio);
		ordena(simbs, meio+1, sup);
		merge(simbs, inf, meio, sup);
	}
}

void merge(simbolo* simbs, int inf, int meio, int sup)
{
	int i,j,k;
	simbolo L[256], R[256];
	int n1 = meio-inf;
	int n2 = sup-meio;
	for(i = 0; i <= n1; i++) L[i] = simbs[inf+i];
	for(j = 0; j <= n2; j++) R[j] = simbs[meio+j+1];
	L[n1+1] = NULL; R[n2+1]=NULL;
	i = 0; j = 0;
	for(k = inf; k<=sup; k++)
	{
		if(L[i] && R[j])
		{
			if(L[i]->freq > R[j]->freq)
			{
				simbs[k]=L[i]; i++;
			}
			else
			{
				simbs[k]=R[j]; j++;
			}
		}
		else if(!L[i] && R[j])
		{
			simbs[k] = R[j]; j++;
		}
		else if(L[i] && !R[j])
		{
			simbs[k] = L[i]; i++;
		}
		else
			return;

	}
	
}
*/
void shannon(simbolo* simbs, int inf, int sup)
{
	int i, sep;
	float half = 0.0f, counter = 0.0f;
	
	if(inf == sup)
		return;

	if(sup-inf == 1)
	{
		charcat(simbs[inf]->code,'0', simbs[inf]->codeLen);
		++(simbs[inf]->codeLen);
		charcat(simbs[sup]->code,'1', simbs[sup]->codeLen);
		++(simbs[sup]->codeLen);
	}
	else
	{

		for(i = inf;i <= sup;i++)
			half+=simbs[i]->freq;

		half *= 0.5f;
		sep = -1;

		for(i = inf; i <= sup; i++)
		{
			if(counter < half)
			{
				counter += simbs[i]->freq;
				charcat(simbs[i]->code,'0', simbs[i]->codeLen);
				++(simbs[i]->codeLen);
			}
			else
			{
				if(sep < 0)	sep = i;
				charcat(simbs[i]->code,'1', simbs[i]->codeLen);
				++(simbs[i]->codeLen);
			}
			
		}

		if(sep < 0)
			sep = inf + 1;

		shannon(simbs, inf, sep-1);
		shannon(simbs, sep, sup);
	}	
}

void charcat(char code[], char c, int n)
{
	if(n+1 == 256)
		printf("Code length exceeded!");
	else
		code[n+1] = c;
}

float searchHalfs(simbolo* simbs, int inf, int sup, float soma, int* k)
{
	float teoHalf = soma/2;
	int i,j;
	float fstHalfA = 0.0, fstHalfB, sndHalfA, difA, sndHalfB, difB;
	float iSum = 0.0;
	
	
	for(i=inf;i<=sup && fstHalfA<teoHalf; i++)
	{
		printf("%0.3f+%0.3f", fstHalfA,simbs[i]->freq);
		fstHalfA += simbs[i]->freq;
		printf("=%0.3f\n",fstHalfA);
	}

	printf("\n");
	
	sndHalfA = soma-fstHalfA;
	difA = fabs(fstHalfA-sndHalfA);

	if(i > inf)
	{

		fstHalfB = fstHalfA-simbs[i-1]->freq;
		printf("1st half= %.3f\n", fstHalfB);
		sndHalfB = soma - fstHalfB;
		printf("2st half= %.3f\n", sndHalfB);
		difB = fabs(fstHalfB - sndHalfB);
		
		if(difB < difA)
		{
			*k = i-1;
			return fstHalfB;
		}
	}

	*k = i;
	return fstHalfA;
}
