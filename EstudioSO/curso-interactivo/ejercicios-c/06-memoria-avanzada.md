# Ejercicios Interactivos de C - Dia 8: Memoria Virtual y Paginacion

Estos ejercicios son mas conceptuales. Algunos requieren pensar y responder, otros son de programacion.

---

## Ejercicio 6.1: Calculo de direcciones

**Enunciado:** En un sistema con paginas de 4KB (4096 bytes) y direcciones virtuales de 32 bits:
1. Cuantos bits son para el desplazamiento?
2. Cuantos bits son para el numero de pagina?
3. Si la direccion virtual es 0x00003A7F, cual es el numero de pagina y el desplazamiento?

**Respuesta:**
1. 12 bits (2^12 = 4096)
2. 20 bits (32 - 12)
3. 0x00003A7F -> pagina = 0x3 (bits 31-12), desplazamiento = 0xA7F (bits 11-0)

---

## Ejercicio 6.2: Paginacion bajo demanda

**Enunciado (tipo examen):** Dado este programa, cuantos marcos de pagina se usan para datos globales? Paginas de 4KB.

```c
char a[512 * 4 * 1024];  // 2MB array global
int main() {
    a[0] = 'a';
    return 0;
}
```

**Respuesta:** Solo 1 marco de pagina. Con paginacion bajo demanda y overcommit, solo se asigna un marco cuando realmente se accede a una pagina. Solo se accede a a[0], que esta en la primera pagina del array. El resto nunca se toca.

---

## Ejercicio 6.3: TLB y rendimiento

**Pregunta:** Si un acceso a memoria tarda 100ns y la TLB tiene un hit rate del 95%, cuanto tarda de media un acceso a memoria con traduccion?
- TLB hit: 100ns (traduccion en cache, practicamente gratis)
- TLB miss: 200ns (primero consultar tabla de paginas en memoria, luego acceder al dato)

**Respuesta:** 0.95 * 100 + 0.05 * 200 = 95 + 10 = 105ns de media.

---

## Ejercicio 6.4: Copy-on-write con fork

**Pregunta conceptual:** Un proceso tiene 100 paginas en memoria. Hace fork(). Cuantos marcos fisicos se usan inmediatamente despues del fork? Asume copy-on-write.

**Respuesta:** Siguen siendo 100 marcos (no 200). Con copy-on-write, padre e hijo comparten los mismos marcos. Solo cuando uno de los dos escribe en una pagina, se crea una copia privada de esa pagina. Si nadie escribe, no se gasta memoria extra.

---

## Ejercicio 6.5: Programa para medir paginas

**Enunciado:** Escribe un programa en C que reserve un array grande con malloc y acceda a posiciones separadas por el tamaño de pagina (4096 bytes). Mide cuantos marcos usa el proceso antes y despues leyendo /proc/self/statm.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_memory() {
    FILE *f = fopen("/proc/self/statm", "r");
    long size, resident;
    if (f) {
        fscanf(f, "%ld %ld", &size, &resident);
        printf("Paginas residentes: %ld\n", resident);
        fclose(f);
    }
}

int main() {
    int pages = 1000;
    int pagesize = 4096;
    
    printf("Antes de malloc:\n");
    print_memory();
    
    char *arr = malloc(pages * pagesize);
    printf("Despues de malloc (sin tocar):\n");
    print_memory();
    
    for (int i = 0; i < pages; i++) {
        arr[i * pagesize] = 'x';
    }
    printf("Despues de tocar %d paginas:\n", pages);
    print_memory();
    
    free(arr);
    return 0;
}
```

Compila y ejecuta para ver como las paginas residentes aumentan solo cuando tocas la memoria.

---

## Ejercicio 6.6: Preguntas tipo examen

**Pregunta 1:** La TLB es...
- a) Cache de datos
- b) Cache de instrucciones
- c) Cache de traducciones virtual a fisica
- d) Cache de traducciones fisica a virtual

**Respuesta:** c

**Pregunta 2:** La memoria virtual permite...
- a) Que el planificador use Round Robin
- b) Proteger la memoria de los distintos procesos
- c) Comprimir la memoria
- d) Es inutil hoy en dia

**Respuesta:** b

**Pregunta 3:** mlock() sirve para...
- a) Evitar condiciones de carrera
- b) Evitar que la memoria vaya a swap
- c) Bloquear un fichero
- d) Crear un log de avisos

**Respuesta:** b
