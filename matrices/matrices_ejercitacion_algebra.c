#include <stdio.h>

#define ELEMENTOS_VECTOR 10
#define FILAS_MATRIZ 2
#define COLUMNAS_MATRIZ 2

int main(){
	int i, j, k;
	
	int vector[ELEMENTOS_VECTOR] = {1,2,3,4,5,6,7,8,9,10};
	int vector_traspuesto[ELEMENTOS_VECTOR][1] = {0};
	
	// 1a transponer un vector
	for (i = 0; i < ELEMENTOS_VECTOR; i++){
		vector_traspuesto[i][0] = vector[i];
	}
	
	printf("\nVector sin transponer: \n");
	for (i = 0; i < ELEMENTOS_VECTOR; i++){
		printf("%d ", vector[i]);
	}
	printf("\n");
	
	printf("\nVector traspuesto: \n");
	for (i = 0; i < ELEMENTOS_VECTOR; i++){
		for (j = 0; j < 1; j++){
			printf("%d ", vector_traspuesto[i][j]);
		}
		printf("\n");
	}
	
	// 1b transponer una matriz
	int matriz[FILAS_MATRIZ][COLUMNAS_MATRIZ] = {{1,2},{3,4}};
	int matriz_transpuesta[FILAS_MATRIZ][COLUMNAS_MATRIZ] = {0};
	
	for (i = 0; i < FILAS_MATRIZ; i++){
		for (j = 0; j < COLUMNAS_MATRIZ; j++){
			matriz_transpuesta[i][j] = matriz[j][i];
		}
	}
	
	printf("\nMatriz sin transponer: \n");
	for (i = 0; i < FILAS_MATRIZ; i++){
		for (j = 0; j < COLUMNAS_MATRIZ; j++){
			printf("%d ", matriz[i][j]);
		}
		printf("\n");
	}
	
	printf("\nMatriz traspuesta: \n");
	for (i = 0; i < FILAS_MATRIZ; i++){
		for (j = 0; j < COLUMNAS_MATRIZ; j++){
			printf("%d ", matriz_transpuesta[i][j]);
		}
		printf("\n");
	}
	
	
	//2a hallar el determinante de una matriz de 2x2
	int determinante;
	determinante = matriz[0][0]*matriz[1][1]-matriz[1][0]*matriz[0][1];
	
	printf("\nMatriz: \n");
	for (i = 0; i < FILAS_MATRIZ; i++){
		for (j = 0; j < COLUMNAS_MATRIZ; j++){
			printf("%d ", matriz[i][j]);
		}
		printf("\n");
	}
	printf("cuyo determinante es: %d\n", determinante);
	
	//opcional: hallar determinante de la matriz transpuesta
	determinante = matriz_transpuesta[0][0]*matriz_transpuesta[1][1]-matriz_transpuesta[1][0]*matriz_transpuesta[0][1];
	printf("siendo: %d, el determinante de su traspuesta\n", determinante);
	//Importante: se puede verificar que ambos valores siempre coincidiran
	
	
	//2b hallar el determinante de una matriz de 3x3
	int matriz33[3][3] = {{4,2,1},{3,7,0},{0,2,0}};
	/*
	Filas/Columnas en Matriz de 3x3:
		00 01 02
		10 11 12
		20 21 22
	determinante: 00*(11*22-21*12) - 01*(10*22-20*12) + 02*(10*21-20*11)
	*/
	
	determinante = matriz33[0][0]*(matriz33[1][1]*matriz33[2][2]-matriz33[2][1]*matriz33[1][2]);
	determinante += (-1)*matriz33[0][1]*(matriz33[1][0]*matriz33[2][2]-matriz33[2][0]*matriz33[1][2]);
	determinante += matriz33[0][2]*(matriz33[1][0]*matriz33[2][1]-matriz33[2][0]*matriz33[1][1]);

	printf("\nMatriz: \n");
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			printf("%d ", matriz33[i][j]);
		}
		printf("\n");
	}
	printf("cuyo determinante es: %d\n", determinante);
	
	//3a aplicar regla de cramer para resolver el siguiente sistema de ecuaciones:
	/*
		-2x + y = 1
		-3x + 4y = 24
	*/
	
	int matriz_3a[2][2]={{-2,1},{-3,4}};
	int determinante_total;
	
	//se halla determinante para aplicar regla de cramer:
	determinante_total = matriz_3a[0][0]*matriz_3a[1][1]-matriz_3a[1][0]*matriz_3a[0][1];

	//se aplica regla de cramer:	
	int matriz_x[2][2]={{1,1},{24,4}};
	int determinante_x;
	int x;
	determinante_x = matriz_x[0][0]*matriz_x[1][1]-matriz_x[1][0]*matriz_x[0][1];
	x = determinante_x/determinante_total;
	
	int matriz_y[2][2]={{-2,1},{-3,24}};
	int determinante_y;
	int y;
	determinante_y = matriz_y[0][0]*matriz_y[1][1]-matriz_y[1][0]*matriz_y[0][1];
	y = determinante_y/determinante_total;
	
	printf("\nLa solucion es (x, y) = (%d, %d)\n", x, y);
	

	return 0;
}
