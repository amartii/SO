#!/bin/sh

check_args(){
    if test $# -ne 1 
    then
        echo "usage: ./ej2.sh <num1> <num2>" 1>&2
        exit 1
    fi
}

es_numero(){
    echo "$1" | egrep '^-?[0-9]+$' > /dev/null 2>&1
}

lista_pares(){
    suma=0
    for i in $(seq 0 $(($1-1)))
    do
        par=$(($i*2))
        echo "$par"
        suma=$((suma+$par))
    done
    echo "Suma: $suma"
}

check_args "$@"

if ! es_numero "$1"
then
    echo "error: los argumentos deben de ser numeros" 1>&2
    exit 1
fi

lista_pares $1
exit 0