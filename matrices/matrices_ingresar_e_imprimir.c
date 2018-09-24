/* Se tienen 4 alumnos con 3 notas
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CANT_NOTAS 3
#define CANT_ALUMNOS 4

main (){
	float mpn[CANT_ALUMNOS][CANT_NOTAS]={0};
	int aux, i, j;

	for (i=0; i < CANT_ALUMNOS; i++){
		for (j=0; j < CANT_NOTAS; j++){
			printf("Ingrese la nota nro %d del alumno %d: ", j, i);
			scanf("%f", &mpn[i][j]);
		}
	}
	
	printf("La matriz resultante: \n");
	printf("Alumno\tNota1\tNota2\tNota3\t\n");
	for (i=0; i < CANT_ALUMNOS; i++){
		printf("%d\t",i);
		for (j=0; j < (CANT_NOTAS); j++){
			printf("%.2f\t", mpn[i][j]);
		}
		printf("\n");
	}
	
}


