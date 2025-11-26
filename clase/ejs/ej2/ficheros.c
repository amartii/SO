#include <stdlib.h>
#include <stdio.h>

// <  >

int 
main(int argc, char **argv){
    FILE *f;
    int buffer[5];
    int i, v;
    size_t r;

    //Escribir numeros en el fichero binario
    f = fopen("a.txt", "wb");//wb-> write binary
    if (f == NULL){
        return EXIT_FAILURE;
    }
    for(i=0; i < 5;i++){
        buffer[i] = i *10; //blucle de llenado, llenamos el buffer con 10, 20, 30, 40, 50
    }
    fwrite(buffer, sizeof(int), 5, f);
    fclose(f);

    //leemos binario
    printf("Lectura de binario:\n");
    f = fopen ("a.txt", "rb"); //rb -> read binary
    if (f == NULL){
        return EXIT_FAILURE;
    }
    r = fread(buffer, sizeof(int), 5, f);
    printf("Elementos leidos: %zu\n", r);
    for(i = 0; i < 5; i++){
        printf("Buffer[%i]: %i\n", i, buffer[i]);
    }
    fclose(f);

    //Escritura de texto
    f = fopen("b.txt", "w"); //w-> write normal
    if (f == NULL){
        return EXIT_FAILURE;
    }
    for (i = 0; i < 5; i++){
        fprintf(f, "%d\n", (int)i*100);
    }
    fclose(f);

    //Lectura de texto
    printf("Lectura de texto:\n");
    f = fopen("b.txt", "r");
    if (f == NULL){
        return EXIT_FAILURE;
    }
    
    i = 1;
    while (fscanf(f, "%i", &v) == 1){
        printf("Elemento %i: %i\n",i, v);
        i++;
    }
    printf ("Elementos leidos: %i\n", i -1);

    fclose(f);
    return 0;
}