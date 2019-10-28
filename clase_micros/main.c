#include <hidef.h> /* para la macro de EnableInterrupts */
#include "derivative.h" /* incluye declaraciones de perifericos */
#include "azm_kit.h" /* declaraciones propias del kit de desarrollo provisto en la clase */ 
#include <stdio.h>

void main(void) {
	int a=0;
	unsigned char buffer[20]={0};
	int n;
	
	Init_S08JM(); // inicializamos los periféricos del kit
	Delay_mseg(500); //esperamos que se inicialice para limpiar la pantalla
	ClearDisplay4(); //limpiamos la pantalla
	while(1) {
		n = Read_Switch(S2);
		n = Read_Preset(PRESET_R17);
		n = Read_Sensor();
		n = Line_Lcd4("  HAGO ELECTRONICA  ",2);
		(void)Led_On(ROJO);
		Led_Off(ROJO);
		
		n = sprintf(buffer,"Valor de a:%9d",a);
		n = Line_Lcd4(buffer,1);
		
		Delay_mseg(500); //Retardo medio segundo
		a++;
		if (a>9)
			a=0;
		
	}
	
	/* Tenemos que asegurarnos que el programa nunca salga del main */
}
