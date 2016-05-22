#include <stdio.h>
#include "reader.h"
#include "codifica.h"
#include <math.h>
#include "writer.h"

	/*read(ficheiro), retorna qualquer coisa*/
	/*ordena o array com simbolos*/
	/*fazer os calculos necessários, entropia and shit*/
	/*shannon-fano*/
	/*write*/

int main(int argc, char** argv)
{
	FILE *in, *out;
	int i,j,k;
	int total;
	int inf, sup;
	int N;
	float soma = 0;
	simbolo simbs[SYMBS];

	/*Initializing every element as NULL*/
	for(i = 0; i < SYMBS; i++)
		simbs[i] = NULL;
	
	in = fopen("teste.txt","r"); /*depois meter isto a ir buscar o ficheiro passado como argumento*/

	/*Reading file and returning number of symbols*/
	total = readFile(in,simbs, &inf, &sup);
    
	/*Shifting every symbol to the left to avoid cycling through a lot of free NULL elements*/
	/*Returns new index of the last element*/
	N = shift(simbs, inf, sup);	
	printf("N: %d\n", N);

	/*Computes the probabilaty of every symbol*/
	freq(simbs, 0, N, total);
	
	/*Teste para verificar se a soma das frequencias e de facto 1*/
	soma = 0;
	for(k = 0; k <= N; k++)
		soma+=simbs[k]->freq;
	
	printf("Total after shift: %0.3f\n", soma);

	/*Prints Status of table before sort -- just to check*/
	printStatus(simbs, 0, N);
	printf("Limite máximo de entropia: %0.2f\n", max(30));
	printf("Entropia: %0.2f\n", entropia(simbs,0,N));

	/*Sorts the array (insertion sort for now, i ran into some problems with merge sort, will look into that later)*/
	ordena(simbs,0,N);

	/*Prints status of table after sort -- just to check*/
	printStatus(simbs,0,N);

	soma = 0.0f;
	for(i =0; i <= N; i++)
		soma+=simbs[i]->freq;
	printf("Sum after ordering= %.3f\n", soma);

	shannon(simbs, 0, N);

	/*Prints the shannon-fano codes for every symbol -- just to check*/
/*	for(i = 0; i <= N; i++)
	{
		int len = simbs[i]->codeLen;
		
		printf("%c: ", simbs[i]->simb);

		for(k = 0; k <= len; k++)
		{
			printf("%c",simbs[i]->code[k]);
		}
		printf("\n");
	}
*/	
	out = fopen("compressed", "wb");/*passar como argumento depois*/
	write(out, in, simbs, N);	
	
	fclose(in);
	fclose(out);
	return 0;
}
