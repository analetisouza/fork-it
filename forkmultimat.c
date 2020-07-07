#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

clock_t start, end;
double cpu_time_used;

void imprimirMatriz(int** matriz, int ordem)
{
	for(int i = 0; i < ordem; i++){
		for(int j = 0; j < ordem; j++){

			printf("%d ", matriz[i][j]);
		}

		printf("\n");
	}
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

int** multiplicaMatriz(int** a, int**b, int n)
{
	int** v = iniciaMatrizQuadrada(n);
	int aux;

	if(fork() == 0)
	{
		for(int i = n/2; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				aux = 0; 
				for(int k = 0; k < n; k++)
					aux += a[i][k] * b[k][j];
				v[i][j] = aux;
			}
		}
	}
	else
	{
		for(int i = 0; i < n/2; i++)
		{
			for(int j = 0; j < n; j++)
			{
				aux = 0; 
				for(int k = 0; k < n; k++)
					aux += a[i][k] * b[k][j];
				v[i][j] = aux;
			}
		}
	}
	return v;
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
	start = clock();
	result = multiplicaMatriz(mat1, mat2, num);
	end = clock();

	cpu_time_used = ((double) end - start)/ CLOCKS_PER_SEC;

	//imprimirMatriz(mat1, num);
	//printf("\n");
	//imprimirMatriz(mat2, num);
	//printf("\n");
	//imprimirMatriz(result, num);
	printf("\n");
	printf("%lf seconds\n", cpu_time_used);

	return 0; 
}