#include <stdio.h>

struct owner
{
    char ownerName[30];
};

struct perro 
{
    char nombre[30];
    int edadMeses;
    char color[10];
    float peso;
    struct owner ownerDog;
}perros[2];

int 
main(int argc, char **argv){

    for(int i = 0; i < 2;i++){
        printf("Ingresa el nombre del dueño del perro:\n");
        scanf("%s", perros[i].ownerDog.ownerName);
        printf("Ingresa el nombre del perro:\n");
        scanf("%s", perros[i].nombre);
        printf("Ingresa la edad del Perro (en meses):\n");
        scanf("%i", &perros[i].edadMeses);
        printf("Introduce el color del perro: \n");
        scanf("%s",perros[i].color);
        printf("Introduce el peso del perro (kg):\n");
        scanf("%f", &perros[i].peso);
    }
    
    for (int i = 0; i < 2;i++){
        printf("El dueño se llama %s\n",perros[i].ownerDog.ownerName);
        printf("El perro %s, tiene %i años, pesa %.2f kg y es de color %s\n", perros[i].nombre, perros[i].edadMeses, perros[i].peso, perros[i].color);

    }
    

    return 0;
}