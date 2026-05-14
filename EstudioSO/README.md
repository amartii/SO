# Curso de Estudio: Sistemas Operativos (2 semanas)

## Como usar estos materiales

### Apuntes para escuchar (dictado)
Los archivos en `apuntes-dictado/` estan escritos en prosa continua, ideales para que una app de texto-a-voz te los dicte. Escuchalos con auriculares mientras caminas, en el transporte, etc.

### Ejercicios interactivos
Los archivos en `curso-interactivo/` contienen ejercicios practicos. Intenta resolverlos antes de mirar las soluciones.

### Preparacion de examen
Los archivos en `examenes/` contienen preguntas reales organizadas por tema, dos simulacros completos, y una lista de errores comunes.

### Plan de estudio
Sigue el plan dia a dia en `plan/00-PLAN-DE-ESTUDIO-2-SEMANAS.md`.

## Estructura de archivos

```
EstudioSO/
  README.md                         <- Este archivo
  plan/
    00-PLAN-DE-ESTUDIO-2-SEMANAS.md <- Plan dia a dia
  apuntes-dictado/
    01-introduccion-C-y-compilacion.md
    02-punteros-arrays-memoria.md
    03-ficheros-y-syscalls.md
    04-procesos-fork-exec.md
    05-pipes-y-senales.md
    06-shell-scripting-basico.md
    07-shell-avanzado-y-filtros.md
    08-memoria-virtual-paginacion.md
    09-sistemas-ficheros-discos.md
    10-planificacion-concurrencia.md
    11-elf-enlazado-depuracion.md
    12-repaso-final-express.md
  curso-interactivo/
    ejercicios-c/
      01-basicos-c.md
      02-punteros-y-memoria.md
      03-ficheros-y-syscalls.md
      04-procesos.md
      05-pipes-y-senales.md
      06-memoria-avanzada.md
      07-concurrencia.md
    ejercicios-shell/
      01-shell-basico.md
      02-shell-avanzado.md
    soluciones/
      (soluciones .c y .sh de todos los ejercicios)
  examenes/
    preguntas-tema-por-tema.md
    simulacro-1.md
    simulacro-2.md
    errores-comunes.md
```

## Compilar los ejercicios de C

```bash
gcc -g -c -Wall -Wshadow -Wvla fichero.c
gcc -g -o fichero fichero.o
```

Para ejercicios con threads (mutex):
```bash
gcc -g -Wall -o programa programa.c -lpthread
```

## Ejecutar scripts de shell

```bash
chmod +x script.sh
./script.sh argumentos
```
