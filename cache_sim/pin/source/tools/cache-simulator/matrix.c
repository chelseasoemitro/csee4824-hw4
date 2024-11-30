#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 100

int main(char **argv, char *argc)
{
	int A[ARRAY_SIZE][ARRAY_SIZE];
	int B[ARRAY_SIZE][ARRAY_SIZE];
	int C[ARRAY_SIZE][ARRAY_SIZE];

	for (int i = 0; i < ARRAY_SIZE; i++) {
		for(int j = 0; j < ARRAY_SIZE; j++) {
			A[i][j] = i * 10 + j;
			B[i][j] = i * j;
			C[i][j] = 0;
		}
	}

	for(int i = 0; i < ARRAY_SIZE; i++) {
		for(int j = 0; j < ARRAY_SIZE; j++) {
			for(int k = 0; k < ARRAY_SIZE; k++){
				C[i][j] += A[i][k] * B[k][j]; 
			}
		}
	}

	for(int i = 0; i < ARRAY_SIZE; i++) {
		printf("[ ");
		for(int j = 0; j < ARRAY_SIZE; j++) {
			printf("%d, ", C[i][j]);
		}
		printf("]\n");
	}

	return 0;
}
