#include <stdio.h>
#include <stdlib.h>

struct {
    char color[10];
    int encendido;
    int brillo;
} led;

void main(void){
    printf("Ingrese un color del led: ");
    scanf("%s", led.color);
    printf("Ingrese si está encendido (1) o apagado (0) el led %s: ", led.color);
    scanf("%d", &led.encendido);
    printf("Ingrese el brillo del led %s (1 a 100): ", led.color);
    scanf("%d", &led.brillo);

    printf("El led de color %s esta ", led.color);
    if (led.encendido){
        printf("encendido y con brillo del %d %%", led.brillo);
    }else{
        printf("apagado");
    }
    printf("\n");

    system("pause");

}
