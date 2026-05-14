# Tema 8: Memoria Virtual y Paginacion

Este tema es mas teorico que los anteriores, pero aparece con frecuencia en el examen. Cubre como el sistema operativo gestiona la memoria y como aísla a los procesos entre si.

## Fragmentacion de memoria

La fragmentacion de memoria es un problema que ocurre cuando la memoria se divide en bloques no contiguos. Hay dos tipos. La fragmentacion externa ocurre cuando hay suficiente memoria libre total para una solicitud, pero esta dividida en trozos separados que no son contiguos, y ningun trozo individual es lo bastante grande. La fragmentacion interna ocurre cuando se asigna un bloque de memoria mas grande de lo necesario, y el espacio sobrante dentro del bloque se desperdicia.

Hay tres metodos para gestionar particiones de memoria variable: first fit, que usa el primer hueco que sirve; best fit, que usa el hueco mas pequeño que sirve; y worst fit, que usa el hueco mas grande. Cada metodo tiene ventajas y desventajas.

## Segmentacion

La segmentacion divide el espacio de memoria en segmentos logicos de tamaño variable: codigo, datos, pila, heap, etcetera. Cada segmento tiene un rango de direcciones virtuales. La ventaja es que es facil de entender, pero genera fragmentacion externa.

## Paginacion

La paginacion es la solucion a la fragmentacion externa. La idea es dividir la memoria tanto virtual como fisica en bloques de tamaño fijo. Los bloques de memoria virtual se llaman paginas, y los bloques de memoria fisica se llaman marcos de pagina. Tipicamente, una pagina tiene cuatro kilobytes.

Cuando un proceso accede a una direccion virtual, el hardware de la unidad de gestion de memoria, llamada MMU, traduce la direccion virtual a una direccion fisica consultando la tabla de paginas del proceso. La tabla de paginas mapea numeros de pagina virtual a numeros de marco fisico.

Una direccion virtual se divide en dos partes: el numero de pagina y el desplazamiento dentro de la pagina. El numero de pagina se usa como indice en la tabla de paginas para encontrar el marco fisico. El desplazamiento se mantiene igual. La direccion fisica es el numero de marco concatenado con el desplazamiento.

Esto es pregunta de examen. Si tienes una direccion virtual de treinta y dos bits y paginas de cuatro kilobytes, que son dos elevado a doce bytes, los doce bits menos significativos son el desplazamiento y los veinte bits restantes son el numero de pagina.

## La TLB

La TLB, que significa Translation Lookaside Buffer, es una memoria cache dentro de la MMU que almacena traducciones recientes de pagina virtual a marco fisico. Sin la TLB, cada acceso a memoria requeriria consultar la tabla de paginas en memoria, lo que duplicaria el tiempo de acceso. Con la TLB, la mayoria de traducciones se resuelven en la cache, que es mucho mas rapida.

Pregunta de examen segura: la TLB es una memoria cache que acelera la traduccion de direcciones virtuales a fisicas. No almacena datos ni instrucciones, solo traducciones.

## Tabla de paginas multinivel

Como la tabla de paginas puede ser muy grande, se organiza en multiples niveles para ahorrar memoria. En vez de tener una tabla plana con una entrada por cada pagina posible, se usa una jerarquia de tablas. Solo se crean las subtablas necesarias para las paginas que realmente usa el proceso.

La traduccion multinivel funciona asi: los bits de la direccion virtual se dividen en varios indices. El primer indice apunta a una entrada en la tabla de primer nivel, que contiene la direccion de una tabla de segundo nivel. El segundo indice apunta a una entrada en la tabla de segundo nivel, y asi hasta llegar al marco fisico.

## Paginacion bajo demanda y overcommit

Con paginacion bajo demanda, el sistema operativo no asigna marcos fisicos hasta que el proceso realmente accede a una pagina. Si un proceso reserva un array de dos megabytes pero solo accede a la primera posicion, solo se asigna un marco de pagina.

Esto se combina con el overcommit de memoria. El sistema operativo puede prometer mas memoria virtual de la que realmente existe como memoria fisica. Mientras los procesos no usen toda la memoria prometida al mismo tiempo, todo funciona.

Pregunta tipica de examen: tienes un array global de dos megabytes, pero solo escribes en la primera posicion. La pregunta es cuantos marcos de pagina usa el proceso para sus datos globales. La respuesta es uno, porque con paginacion bajo demanda solo se asigna el marco de la pagina a la que accedes.

## Copy-on-write

Copy-on-write es una optimizacion que el kernel usa con fork. Cuando haces fork, el hijo comparte las mismas paginas de memoria que el padre. Las paginas se marcan como de solo lectura. Solo cuando uno de los dos intenta escribir en una pagina, se crea una copia privada de esa pagina. Esto hace que fork sea mucho mas eficiente, porque no necesita copiar toda la memoria del proceso inmediatamente.

## Swap

El swap es un espacio en disco que el sistema operativo usa como extension de la memoria RAM. Cuando la RAM se llena, el kernel puede mover paginas poco usadas a swap para liberar marcos para otras paginas. Cuando un proceso accede a una pagina que esta en swap, se genera un fallo de pagina y el kernel la trae de vuelta a RAM.

La llamada mlock permite que un proceso bloquee paginas en RAM para que no sean enviadas a swap. Esto es util para aplicaciones de tiempo real o que manejan datos sensibles que no deben ir a disco.

Pregunta de examen: mlock permite evitar que la memoria de un proceso vaya a swap. No tiene nada que ver con cerrojos o sincronizacion.

## Proteccion de memoria

Una de las funciones mas importantes de la memoria virtual es la proteccion. Cada proceso tiene su propio espacio de direcciones virtuales, completamente aislado de los demas. Un proceso no puede acceder a la memoria de otro proceso. La MMU verifica los permisos en cada acceso a memoria y genera una excepcion si el proceso intenta algo no permitido.

Las paginas pueden tener permisos de lectura, escritura y ejecucion. Las paginas de codigo son tipicamente de lectura y ejecucion pero no de escritura. Las paginas de datos son de lectura y escritura pero no de ejecucion. Esto proporciona proteccion contra ataques de inyeccion de codigo.

Pregunta de examen: la memoria virtual permite proteger la memoria de los distintos procesos. Cada proceso tiene su espacio de direcciones, y la MMU impide accesos no autorizados.

## Algoritmos de reemplazo de paginas

Cuando la RAM esta llena y se necesita un marco libre, el kernel debe elegir que pagina expulsar. Los algoritmos principales son: optimo, que expulsa la pagina que tardara mas en usarse, pero es impracticable porque requiere conocer el futuro; FIFO, que expulsa la mas antigua; y LRU, que expulsa la menos recientemente usada, que es la aproximacion mas comun al optimo.

LRU se implementa tipicamente con un bit de referencia que el hardware pone a uno cada vez que se accede a la pagina. El kernel periodicamente comprueba y limpia estos bits para estimar que paginas son mas o menos usadas.
