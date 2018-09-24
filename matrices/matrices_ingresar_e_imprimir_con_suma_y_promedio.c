/* Se tienen 4 alumnos con 3 notas
	en la 4ta columna de la matriz mpn se tendrá la suma de sus notas y
	en la 5ta columna el promedio
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CANT_NOTAS 3
#define CANT_ALUMNOS 4

main (){
	float mpn[CANT_ALUMNOS][CANT_NOTAS+2]={0};
	int aux, i, j;

	for (i=0; i < CANT_ALUMNOS; i++){
		for (j=0; j < CANT_NOTAS; j++){
			printf("Ingrese la nota nro %d del alumno %d: ", j, i);
			scanf("%f", &mpn[i][j]);
		}
	}
	
	for (i=0; i < CANT_ALUMNOS; i++){
		for (j=0; j < CANT_NOTAS; j++){
			mpn[i][CANT_NOTAS] = mpn[i][j] + mpn[i][CANT_NOTAS]; //acumulo la suma de las notas del mismo alumno y acumulo en la columna destinada para tal fin
			
			// tener en cuenta que el mpn[i][CANT_NOTAS] equivale a la fila correspondiente al alumno y la posición en la columna de la suma:
			// 			Pos 0	Pos 1	Pos 2	Pos 3	Pos 4
			// Alumno	Nota1	Nota2	Nota3	Suma	Promedio
			// 1		0.00	0.00	0.00	0.00	0.00
			// 2 ...
			// y así..
		}
		mpn[i][CANT_NOTAS+1] = mpn[i][CANT_NOTAS] / CANT_NOTAS;
	}
	
	printf("La matriz resultante: \n");
	printf("Alumno\tNota1\tNota2\tNota3\tSuma\tPromedio\n");
	for (i=0; i < CANT_ALUMNOS; i++){
		printf("%d\t",i);
		for (j=0; j < (CANT_NOTAS+2); j++){
			printf("%.2f\t", mpn[i][j]);
		}
		printf("\n");
	}

	system("pause");
	
}


