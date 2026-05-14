# Plan de Estudio de 2 Semanas - Sistemas Operativos

## Estructura del Plan

El plan está dividido en 14 días. Cada día tiene entre 3 y 4 horas de estudio. Se alternan sesiones de teoría dictada, práctica de programación y repaso de preguntas de examen.

---

## SEMANA 1: Fundamentos y Programación en C/Shell

### Dia 1 (Lunes) - Introduccion a C y Compilacion

**Mañana (1.5h): Teoria dictada**
- Escuchar: `apuntes-dictado/01-introduccion-C-y-compilacion.md`
- Temas: Caracteristicas de C, fases de compilacion, tipos de datos, variables

**Tarde (1.5h): Practica**
- Hacer ejercicios del `curso-interactivo/ejercicios-c/01-basicos-c.md`
- Compilar y ejecutar los programas de ejemplo

**Noche (30min): Repaso examen**
- Leer `examenes/preguntas-tema-por-tema.md` seccion 1 (Fundamentos de C y Punteros)

---

### Dia 2 (Martes) - Punteros, Arrays y Memoria Dinamica

**Mañana (1.5h): Teoria dictada**
- Escuchar: `apuntes-dictado/02-punteros-arrays-memoria.md`
- Temas: Punteros, aritmetica de punteros, arrays, malloc, free, strings

**Tarde (1.5h): Practica**
- Hacer ejercicios del `curso-interactivo/ejercicios-c/02-punteros-y-memoria.md`
- Prestar atencion a errores comunes de sizeof

**Noche (30min): Repaso examen**
- Leer `examenes/preguntas-tema-por-tema.md` seccion 2 (Memoria Dinamica)

---

### Dia 3 (Miercoles) - Ficheros y Llamadas al Sistema

**Mañana (1.5h): Teoria dictada**
- Escuchar: `apuntes-dictado/03-ficheros-y-syscalls.md`
- Temas: open, read, write, close, lseek, descriptores de fichero, umask

**Tarde (1.5h): Practica**
- Hacer ejercicios del `curso-interactivo/ejercicios-c/03-ficheros-y-syscalls.md`
- Practicar lectura y escritura de ficheros con llamadas POSIX

**Noche (30min): Repaso examen**
- Leer `examenes/preguntas-tema-por-tema.md` seccion 4 y 5 (Llamadas al Sistema y Ficheros)

---

### Dia 4 (Jueves) - Procesos: fork, exec, wait

**Mañana (1.5h): Teoria dictada**
- Escuchar: `apuntes-dictado/04-procesos-fork-exec.md`
- Temas: fork(), exec(), wait(), arboles de procesos, zombies

**Tarde (1.5h): Practica**
- Hacer ejercicios del `curso-interactivo/ejercicios-c/04-procesos.md`
- Dibujar arboles de procesos para cada ejercicio

**Noche (30min): Repaso examen**
- Leer `examenes/preguntas-tema-por-tema.md` seccion 3 (Procesos y Fork)

---

### Dia 5 (Viernes) - Pipes y Comunicacion entre Procesos

**Mañana (1.5h): Teoria dictada**
- Escuchar: `apuntes-dictado/05-pipes-y-senales.md`
- Temas: pipe(), dup2(), FIFO, señales, SIGPIPE, SIGKILL

**Tarde (1.5h): Practica**
- Hacer ejercicios del `curso-interactivo/ejercicios-c/05-pipes-y-senales.md`
- Practicar redirecciones con dup2 y comunicacion padre-hijo

**Noche (30min): Repaso examen**
- Leer `examenes/preguntas-tema-por-tema.md` seccion 6 y 13 (Pipes y Señales)

---

### Dia 6 (Sabado) - Shell Scripting Basico

**Mañana (1.5h): Teoria dictada**
- Escuchar: `apuntes-dictado/06-shell-scripting-basico.md`
- Temas: Variables, parametros posicionales, shift, if, test, case, bucles

**Tarde (2h): Practica**
- Hacer ejercicios del `curso-interactivo/ejercicios-shell/01-shell-basico.md`
- Escribir scripts desde cero

**Noche (30min): Repaso examen**
- Leer `examenes/preguntas-tema-por-tema.md` seccion 7 (Shell y Variables)

---

### Dia 7 (Domingo) - Shell Scripting Avanzado y Repaso Semana 1

**Mañana (1.5h): Teoria dictada**
- Escuchar: `apuntes-dictado/07-shell-avanzado-y-filtros.md`
- Temas: grep, sed, awk, sort, find, xargs, regex, redirecciones, pipes

**Tarde (2h): Practica**
- Hacer ejercicios del `curso-interactivo/ejercicios-shell/02-shell-avanzado.md`
- Resolver problemas combinando filtros

**Noche (1h): Repaso general**
- Repasar preguntas erradas de la semana
- Volver a hacer los ejercicios que costaron mas

---

## SEMANA 2: Teoria Avanzada y Preparacion de Examen

### Dia 8 (Lunes) - Gestion de Memoria y Memoria Virtual

**Mañana (1.5h): Teoria dictada**
- Escuchar: `apuntes-dictado/08-memoria-virtual-paginacion.md`
- Temas: Fragmentacion, paginacion, TLB, copy-on-write, swap

**Tarde (1.5h): Practica**
- Hacer ejercicios del `curso-interactivo/ejercicios-c/06-memoria-avanzada.md`
- Ejercicios de calculo de direcciones y TLB

**Noche (30min): Repaso examen**
- Leer `examenes/preguntas-tema-por-tema.md` seccion 8 (Memoria Virtual)

---

### Dia 9 (Martes) - Sistemas de Ficheros y Discos

**Mañana (1.5h): Teoria dictada**
- Escuchar: `apuntes-dictado/09-sistemas-ficheros-discos.md`
- Temas: i-nodos, FAT, VFS, FUSE, MBR, GPT, LVM, algoritmos de disco

**Tarde (1h): Practica**
- Ejercicios conceptuales de i-nodos y enlaces duros
- Repasar estructura de directorios Unix

**Noche (30min): Repaso examen**
- Leer `examenes/preguntas-tema-por-tema.md` seccion 12 (Sistemas de Ficheros)

---

### Dia 10 (Miercoles) - Planificacion y Concurrencia

**Mañana (1.5h): Teoria dictada**
- Escuchar: `apuntes-dictado/10-planificacion-concurrencia.md`
- Temas: FCFS, SJF, Round-Robin, condiciones de carrera, mutex, semaforos, monitores

**Tarde (1.5h): Practica**
- Hacer ejercicios del `curso-interactivo/ejercicios-c/07-concurrencia.md`
- Identificar condiciones de carrera en codigo

**Noche (30min): Repaso examen**
- Leer `examenes/preguntas-tema-por-tema.md` seccion 9 y 10 (Planificacion y Concurrencia)

---

### Dia 11 (Jueves) - ELF, Enlazado y Depuracion

**Mañana (1.5h): Teoria dictada**
- Escuchar: `apuntes-dictado/11-elf-enlazado-depuracion.md`
- Temas: Ficheros ELF, .text/.data/.bss, GOT/PLT, lazy binding, RELRO, GDB, Valgrind

**Tarde (1.5h): Practica**
- Depurar programas con GDB
- Detectar leaks con Valgrind

**Noche (30min): Repaso examen**
- Leer `examenes/preguntas-tema-por-tema.md` seccion 11 (ELF)

---

### Dia 12 (Viernes) - Simulacro de Examen 1

**Mañana (2h): Simulacro**
- Hacer `examenes/simulacro-1.md` sin mirar respuestas
- Tiempo: 90 minutos como en examen real

**Tarde (1.5h): Correccion y repaso**
- Corregir con las soluciones
- Repasar temas donde hubo fallos
- Volver a los apuntes dictados de esos temas

---

### Dia 13 (Sabado) - Simulacro de Examen 2 + Repaso Practico

**Mañana (2h): Simulacro**
- Hacer `examenes/simulacro-2.md` sin mirar respuestas

**Tarde (2h): Practica intensiva**
- Volver a hacer ejercicios de C mas dificiles (pipes, fork, ficheros)
- Volver a hacer ejercicios de shell mas dificiles (photocol, catlen)

---

### Dia 14 (Domingo) - Repaso Final

**Mañana (1.5h): Repaso rapido**
- Escuchar: `apuntes-dictado/12-repaso-final-express.md` (resumen de todo)
- Revisar flashcards de valores de retorno

**Tarde (1.5h): Ultimas dudas**
- Repasar preguntas que mas costaron
- Releer errores comunes del `examenes/errores-comunes.md`
- Descansar y confiar en la preparacion

---

## Distribucion de Tiempo Total

| Actividad | Horas |
|-----------|-------|
| Teoria dictada | 16.5h |
| Practica programacion | 19h |
| Repaso examenes | 7h |
| Simulacros | 4h |
| **TOTAL** | **46.5h** |

## Archivos del Curso

```
EstudioSO/
  plan/
    00-PLAN-DE-ESTUDIO-2-SEMANAS.md    (este archivo)
  apuntes-dictado/
    01 a 12: apuntes narrativos para escuchar
  curso-interactivo/
    ejercicios-c/: ejercicios practicos de C
    ejercicios-shell/: ejercicios practicos de shell
    soluciones/: soluciones de todos los ejercicios
  examenes/
    preguntas-tema-por-tema.md
    simulacro-1.md
    simulacro-2.md
    errores-comunes.md
```
