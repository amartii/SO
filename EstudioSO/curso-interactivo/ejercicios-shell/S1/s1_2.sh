#!/bin/sh

if test $# -ne 1 
then
    echo "error: usage $0 <dir>" >&2
    exit 1
fi

if test -f $1 
then
    echo "es un fichero regular"
elif test -d $1
then
    echo "es un directorio"

elif  test -L $1
then    
    echo "es un enlace simbólico"
else
    echo "no se que es"
fi

exit 0