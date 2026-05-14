# Ejercicios Interactivos de C - Dia 10: Concurrencia y Sincronizacion

---

## Ejercicio 7.1: Detectar condicion de carrera (EXAMEN)

**Sin compilar**, identifica el problema en este codigo:

```c
void decrementarhastacero(void) {
    if (contador > 0) {
        pthread_mutex_lock(&mutex);
        contador--;
        pthread_mutex_unlock(&mutex);
    }
}
```

**Respuesta:** Hay una condicion de carrera. La comprobacion `if (contador > 0)` ocurre FUERA del mutex. Dos hilos pueden pasar el if simultaneamente y ambos decrementar. El lock solo protege el decremento, no la comprobacion. El codigo correcto es:

```c
void decrementarhastacero(void) {
    pthread_mutex_lock(&mutex);
    if (contador > 0) {
        contador--;
    }
    pthread_mutex_unlock(&mutex);
}
```

---

## Ejercicio 7.2: Incremento concurrente

**Enunciado:** Escribe un programa con dos hilos (pthread) que incrementen un contador compartido 1000000 veces cada uno. Primero sin proteccion (para ver el problema) y luego con mutex.

**Sin mutex esperado:** Resultado menor que 2000000
**Con mutex esperado:** Resultado exactamente 2000000

**Pistas:**
- Incluye pthread.h
- pthread_create(&thread, NULL, func, NULL)
- pthread_join(thread, NULL)
- pthread_mutex_lock/unlock

**Solucion:** Ver `../soluciones/07-02-mutex.c`

---

## Ejercicio 7.3: Detectar carrera en lista (EXAMEN)

**Sin compilar**, identifica el problema:

```c
int eliminarcliente(Cliente *c) {
    if (existe_cliente(c, listaclientes)) {
        pthread_spin_lock(&lk);
        borrar_de_lista(c, listaclientes);
        pthread_spin_unlock(&lk);
        return 0;
    }
    return -1;
}
```

**Respuesta:** Condicion de carrera. `existe_cliente()` se ejecuta sin el spinlock. Entre `existe_cliente()` y `borrar_de_lista()`, otro hilo podria borrar el mismo cliente, causando un doble borrado o acceso a memoria liberada.

---

## Ejercicio 7.4: x++ no es atomico (EXAMEN)

**Explica** por que `x++` no es atomico, y que valor final puede tener x si dos hilos ejecutan `x++` 10 veces cada uno con x inicializado a 0.

**Respuesta:**
x++ se compila a tres instrucciones:
1. Leer x en registro
2. Incrementar registro
3. Escribir registro en x

Si dos hilos intercalan estas instrucciones:
- Hilo A lee x=0, Hilo B lee x=0
- Ambos incrementan a 1
- Ambos escriben 1
- Resultado: x=1 en vez de 2

Valor final posible: minimo 2 (maximo interferencia), maximo 20 (ejecucion secuencial).

---

## Ejercicio 7.5: Spinlock vs Mutex (EXAMEN)

**Pregunta:** Cuando NO debes usar spinlocks?

**Respuesta:** No usar spinlocks cuando la contencion es alta, porque desperdician CPU en espera activa. Con muchos hilos compitiendo, la mayoria estaran haciendo busy-wait consumiendo ciclos sin hacer trabajo util. Mejor usar mutex, que duerme al hilo en vez de esperar activamente.

---

## Ejercicio 7.6: Productor-Consumidor conceptual

**Enunciado:** Escribe pseudocodigo para el problema productor-consumidor con un buffer de tamaño 10. Usa un mutex y dos variables de condicion (notEmpty y notFull).

**Solucion:**
```
Buffer buf[10]
int count = 0
Mutex m
Condition notEmpty, notFull

Productor:
    lock(m)
    while (count == 10)
        wait(notFull, m)
    buf[count] = producir_dato()
    count++
    signal(notEmpty)
    unlock(m)

Consumidor:
    lock(m)
    while (count == 0)
        wait(notEmpty, m)
    count--
    dato = buf[count]
    signal(notFull)
    unlock(m)
    consumir(dato)
```

Nota: usa WHILE, no IF, para la espera. Porque puede haber despertares espurios.

---

## Ejercicio 7.7: Preguntas rapidas tipo examen

**P1:** Spinlock con comprobacion fuera del lock. x puede ser mayor que Maxcont?
```c
pthread_spin_lock_t lk;
void incrementar() {
    if(x < Maxcont) {
        pthread_spin_lock(&lk);
        x++;
        pthread_spin_unlock(&lk);
    }
}
```
**R:** Si, x puede ser mayor que Maxcont. La comprobacion esta fuera del lock.

**P2:** Que es flock()?
**R:** Lock de lectores/escritores para ficheros. LOCK_SH para lectura compartida, LOCK_EX para escritura exclusiva.

**P3:** Diferencia entre mutex y semaforo?
**R:** Mutex es para exclusion mutua (binario). Semaforo es un contador para sincronizacion general (puede ser >1).
