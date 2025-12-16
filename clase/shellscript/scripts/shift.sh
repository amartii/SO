#!/bin/sh
echo arg1 es: $1
echo todos args: $*
shift
echo arg1 después shift: $1
echo todo args despues shift: $*
exit 0

#shift desplaza los argumentos hacia la izquierda descartando el primero