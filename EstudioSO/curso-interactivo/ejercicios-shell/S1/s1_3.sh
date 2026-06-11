#!/bin/sh

if test $# -ne 3
then 
    echo "error: usage $0 num op num" >&2
    exit 1
fi

case "$2" in 
    +) 
        resultado=$(($1 + $3))
        ;;
    -)
        resultado=$(($1 - $3))
        ;;
    \*)
        resultado=$(($1 * $3))
        ;;
    /)
        if test "$3" -eq 0
        then
            echo "error:division by zero" >&2
            exit 1
        fi
        resultado=$(($1 / $3))
        ;;
    *)
        echo "error: unkown operator" >&2
        exit 1 
        ;;
esac

echo $resultado
exit 0