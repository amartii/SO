#!/bin/sh

check_args(){
    if test $# -lt 1
    then
        echo "usage: ./ej1.sh <arg> <arg> ... <arg>"
        exit 1
    fi
}

check_args "$@"
for arg in "$@"
do
    echo $arg | egrep '/'
done
exit 0