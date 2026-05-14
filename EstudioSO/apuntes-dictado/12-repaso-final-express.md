# Tema 12: Repaso Final Express - Todo lo que Debes Recordar

Este es un repaso rapido de los conceptos clave de toda la asignatura. Ideal para el ultimo dia antes del examen.

## Valores de retorno que debes memorizar

Fork devuelve cero en el hijo, el PID del hijo en el padre, y menos uno si hay error. Read devuelve el numero de bytes leidos, cero para fin de fichero, y menos uno para error. Write devuelve el numero de bytes escritos y menos uno para error. Open devuelve un descriptor mayor o igual a cero, o menos uno para error. Exec no retorna si tiene exito, y devuelve menos uno si falla. Wait devuelve el PID del hijo que termino, o menos uno si no hay hijos.

## Trampas clasicas del examen

Primera trampa: sizeof de un puntero devuelve el tamaño del puntero, no del bloque al que apunta. En sesenta y cuatro bits, son ocho bytes. Esto se pregunta constantemente.

Segunda trampa: los fork se duplican exponencialmente. Cada fork dobla el numero de procesos. N forks consecutivos crean dos elevado a N procesos.

Tercera trampa: el buffering de printf. Si usas printf sin salto de linea y luego fork, el contenido del buffer se duplica y puede imprimirse dos veces. Usa fflush antes del fork.

Cuarta trampa: exec no retorna. Si escribes codigo despues de exec, solo se ejecuta si exec falla.

Quinta trampa: las variables de shell no se heredan a los hijos. Solo las de entorno con export.

Sexta trampa: la comprobacion fuera del lock. Si compruebas una condicion antes de adquirir el mutex y luego actuas, tienes una condicion de carrera. La comprobacion debe estar dentro del lock.

Septima trampa: un write grande en un pipe sin lector simultaneo causa deadlock. El pipe se llena y write se bloquea esperando que alguien lea, pero el read viene despues del write y nunca se ejecuta.

Octava trampa: leer de un pipe vacio sin escritores devuelve cero, que es fin de fichero. Escribir en un pipe sin lectores envia SIGPIPE.

Novena trampa: SIGKILL y SIGSTOP no pueden ser capturadas ni ignoradas. SIGKILL es la forma garantizada de matar un proceso.

Decima trampa: con paginacion bajo demanda y overcommit, solo se asignan marcos de pagina cuando realmente accedes a ellos. Un array enorme que solo usas en una posicion solo consume un marco.

## Resumen de conceptos por tema

Compilacion: preprocesado, compilacion a objeto, enlazado. Usa menos Wall siempre.

Tipos de datos: char un byte, int cuatro bytes, puntero ocho bytes en sesenta y cuatro bits.

Punteros: ampersand toma la direccion, asterisco accede al valor. La aritmetica depende del tipo apuntado.

Memoria dinamica: malloc reserva, free libera. Siempre comprobar NULL. Emparejar cada malloc con un free.

Descriptores: stdin es cero, stdout es uno, stderr es dos. Dup2 redirige descriptores.

Fork: crea proceso hijo duplicando al padre. Devuelve cero en hijo, PID en padre.

Exec: reemplaza el programa del proceso. No crea proceso nuevo.

Wait: espera a que un hijo termine. Evita zombies.

Pipes: unidireccionales, buffer limitado. fd sub cero lectura, fd sub uno escritura.

Señales: SIGINT es Control C, SIGKILL no se puede capturar, SIGPIPE cuando escribes en pipe sin lector.

Shell: las variables no se heredan sin export. getenv recibe nombre sin dolar.

Memoria virtual: paginas y marcos, TLB acelera traduccion, copy on write con fork.

i-nodos: metadatos del fichero. El fichero se borra cuando st nlink llega a cero.

FAT: lista enlazada con tabla. Las entradas de directorio tienen los nombres.

Concurrencia: x mas mas no es atomico. Mutex duerme, spinlock hace espera activa. No usar spinlocks con alta contencion.

ELF: punto text es codigo, punto data es datos inicializados, punto bss es datos sin inicializar. Lazy binding resuelve en primera llamada.

Planificacion: Round Robin con cuanto grande es FCFS. Cuanto pequeño mas afectado por cambios de contexto lentos. Renice va de menos veinte a diecinueve.

## Errores comunes que el examen detecta

Retornar puntero a variable local: la variable se destruye al salir de la funcion.

Olvidar cerrar descriptores de pipe en el proceso que no los usa: el pipe no funciona correctamente.

Comprobar la condicion fuera del cerrojo: condicion de carrera.

Usar getenv con dolar delante del nombre: incorrecto.

Confundir TLB con cache de datos: la TLB solo cachea traducciones de direcciones.

Confundir mlock con mutex: mlock evita swap, no sincroniza procesos.

Confundir flock con spinlock: flock es para bloqueo de ficheros.

## Estrategia de examen

Lee cada pregunta dos veces. En las preguntas de codigo, traza la ejecucion paso a paso. Dibuja arboles de procesos para los ejercicios de fork. Identifica si hay condiciones de carrera mirando que esta dentro y fuera del lock. Recuerda que sizeof de puntero no es sizeof del bloque. Y no olvides que read puede devolver menos bytes de los pedidos sin que sea error.

Si dudas entre dos opciones, piensa cual es la trampa que el profesor quiere que caigas. Normalmente la opcion obvia es incorrecta y la correcta requiere pensar un paso mas.

Buena suerte en el examen.
