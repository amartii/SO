#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int size;

struct dog{
    char name[20];
    char *p_name;
}perro[2];

int 
main(int argc, char **argv){
    
    for (int i = 0; i < 2; i++){
        printf("Introduzca el nombre del perro:\n");
        //gets(perro[i].name); no es seguro, ya qu eno limita los caracteres 
        //scanf("%s", perro[i].name);
        fgets(perro[i].name, 20, stdin); //controla los espacios, a diferencia de scanf que considera los espacios como final de linea
        size = strlen(perro[i].name);// Obtiene la longitud del nombre
        printf("%i\n", size);
        perro[i].p_name = malloc((size)*sizeof(char));// Reserva memoria justa para el nombre (podemos truncarla haciendo size-20)
        if (perro[i].p_name == NULL){
            printf("Error al asignar memoria\n");
        }else{
            strcpy(perro[i].p_name, perro[i].name);
        }
    }

    for (int i = 0; i < 2; i++){
        printf("El nombre del perro es: %s\n", perro[i].p_name);
        //printf("%s\n",perro -> p_name); lo mismo que lo de arriba
    }
    //liberamos memoria correctamente
    for (int i = 0; i < 2; i++){
        free(perro[i].p_name);
        perro[i].p_name = NULL; //le asignamos a NULL si no lo vamos a usar para evitar errores (BUENA PRÁCTICA)
    }

    return 0;
}