#!/bin/sh

check_args(){
    if [ ${#1} -ne 1 ] 
    then
        echo "usage: ./ej2.sh <caracter>" 1>&2
        exit 1
    fi
}

que_es(){
case $1 in
    a|e|i|o|u|A|E|I|O|U)
        echo "Es una vocal"
        ;;
    [0-9])
        echo "Es un dígito"
        ;;
    [a-zA-Z])
        echo "Es una consonante"
        ;;
    *)
        echo "Es otro carácter"
        ;;
esac
}

check_args "$@"
que_es "$@"
exit 0