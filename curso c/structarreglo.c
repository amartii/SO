#include <stdio.h>

struct perro 
{
    char nombre[30];
    int edadMeses;
    char color[10];
    float peso;
}

perros[4];

int 
main(int argc, char **argv){

    for(int i = 0; i < 4;i++){
        printf("Ingresa el nombre del perro:\n");
        scanf("%s", perros[i].nombre);
        printf("Ingresa la edad del Perro (en meses):\n");
        scanf("%i", &perros[i].edadMeses);
        printf("Introduce el color del perro: \n");
        scanf("%s",perros[i].color);
        printf("Introduce el peso del perro (kg):\n");
        scanf("%f", &perros[i].peso);
    }
    
    for (int i = 0; i < 4;i++){
        printf("El perro %s, tiene %i años, pesa %.2f kg y es de color %s\n", perros[i].nombre, perros[i].edadMeses, perros[i].peso, perros[i].color);

    }
    

    return 0;
}