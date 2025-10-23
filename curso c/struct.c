#include <stdio.h>

struct perro 
{
    char nombre[30];
    int edadMeses;
    char color[10];
    float peso;
}

perro1={"Collie", 12, "Blanco", 15};

int 
main(int argc, char **argv){

    printf("El nombre del perro es %s, tiene %i años, pesa %.2f kg y es de color %s\n", perro1.nombre, perro1.edadMeses, perro1.peso, perro1.color);

    return 0;
}