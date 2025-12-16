#!/bin/sh
echo tengo una lista de $# args: $*
echo imprimo la lista
for i in $*
do
    echo param: $i
done
exit 0