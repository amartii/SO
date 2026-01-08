#!/bin/sh

check_args(){
    if test $# -ne 2 
    then
        echo "usage: ./ej2.sh <num1> <num2>" 1>&2
        exit 1
    fi
}

es_numero(){
    echo "$1" | egrep '^-[0-9]+$' > /dev/null 2>&1
}

check_args "$@"

if ! es_numero "$1" || ! es_numero "$2"
then
    echo "error: los argumentos deben de ser numeros" 1>&2
    exit 1
fi

a=$1
b=$2
suma=$((a + b))
resta=$((a - b))
multi=$((a * b))
div=$((a / b))
mod=$((a % b))

echo "La suma: $suma"
echo "La resta: $resta"
echo "La multiplicación: $multi"
echo "La divsiion: $div"
echo "El modulo: $mod"

exit 0