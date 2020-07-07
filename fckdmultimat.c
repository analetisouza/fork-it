#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

clock_t start, end;
double cpu_time_used;

void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 
        ; 
} 

void imprimirMatriz(int** matriz, int ordem)
{
	for(int i = 0; i < ordem; i++)
	{
		for(int j = 0; j < ordem; j++)
		{

			printf("%d ", matriz[i][j]);
		}

		printf("\n");
	}
}

void imprimirVetor(int* vetor, int ordem)
{
	for(int i = 0; i < ordem; i++)
	{
		printf("%d ", vetor[i]);
	}
	printf("\n");
}

int* iniciaVetor(int n)
{
	int* v = malloc(n*sizeof(int));

	for(int i = 0; i < n; i++)
		v[i] = 0;

	return v;
}

int** iniciaMatrizQuadrada(int n)
{
    int** m = malloc(n*sizeof(int*));

    for(int i = 0; i < n; i++)
        m[i] = malloc(n*sizeof(int));

    for(int i = 0; i < n; i++)
    	for(int j = 0; j < n; j++)
   			m[i][j] = 0;

  	return m;
}

int** geraMatrizQuadrada(int n)
{
	int** v = iniciaMatrizQuadrada(n);

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			v[i][j] = rand() % 100;

	return v;
}

int* multiplicaVetor(int* a, int** b, int n)
{
	int* v = iniciaVetor(n);
	int aux;

	for(int i = 0; i < n; i++)
	{
		aux = 0; 
		for(int k = 0; k < n; k++)
			aux += a[k] * b[k][i];
		v[i] = aux;
	}
	return v;
}

void multiplicaMatriz(int** a, int**b, int** m, int n)
{
	for(int i = 0; i < n; i++)
	{
		if(fork() == 0)
		{		
			m[i] = multiplicaVetor(a[i],b,n);
			printf("[%d] ", i);
			//imprimirVetor(m[i],n);
			exit(0);
		}
	}
}

int main(void)
{
	int** mat1;
	int** mat2;
	int** result; 
	int num; 

	scanf("%d", &num);
	printf("\n");

	mat1 = geraMatrizQuadrada(num);
	mat2 = geraMatrizQuadrada(num);
	result = iniciaMatrizQuadrada(num);
	imprimirMatriz(mat1, num);
	printf("\n");
	imprimirMatriz(mat2, num);
	printf("\n");
	start = clock();
	if(fork() == 0)
		multiplicaMatriz(mat1, mat2, result, num);
	end = clock();

	cpu_time_used = ((double) end - start)/ CLOCKS_PER_SEC;

	delay(10000);
	imprimirMatriz(result, num);
	//printf("\n");
	//printf("%lf seconds\n", cpu_time_used);

	return 0; 
}