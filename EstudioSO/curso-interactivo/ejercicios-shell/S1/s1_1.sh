#!/bin/sh

if test $# -lt 1 
then 
    echo "error: usage $0 <palabra1> <palabra 2>..."
    exit 1
fi

for arg in "$@"
do
    echo "Hola $arg"
done

exit 0
