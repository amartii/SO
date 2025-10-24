#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    char *nombre;
    struct nodo *sig; //unir otro elemento a la lista
}Libro;
//nodo en c es una estructura que se crea con memoria dinámica

Libro *listaLibro(void){
    Libro *Lista = NULL;
    return Lista;
}

Libro *agregarLibro(Libro *Lista, char *nombre){
    Libro *nuevoLibro, *aux;
    nuevoLibro = (Libro*)malloc(sizeof(Libro));
    nuevoLibro-> nombre = nombre; 
    nuevoLibro -> sig = NULL;
    if (Lista == NULL){
        Lista = nuevoLibro;
    }else{//agregamos más elementos
        aux = Lista;
        while(aux->sig !=NULL){
            aux = aux -> sig;
        }
        aux ->sig = nuevoLibro;
    }
    return Lista;
}
int 
main(int argc, char **argv){

    Libro *Lista = listaLibro();
    Lista = agregarLibro(Lista, "SO libro");
    Lista = agregarLibro(Lista, "Dragones libro");
    printf("Puntero a dir memoria: %p\n", Lista);
    printf("Lista de libros:\n");
    while(Lista !=NULL){
        printf("-%s\n", Lista->nombre);
        Lista = Lista->sig;
    }
    return 0;
}


//El valor (nil) no es un error: simplemente indica que tu puntero no apunta a ninguna 
//dirección válida de memoria, ya que lo has inicializado como NULL a propósito