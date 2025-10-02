#include <stdio.h>
int
main(){
    char letra = 'A';
    int a =10;
    printf("La var letra contiene: %c\n", letra);
    printf("La var a contiene: %i\n", a);
    printf("La var a inicia en la direccion:%p\n", &a);

    return 0;
}
