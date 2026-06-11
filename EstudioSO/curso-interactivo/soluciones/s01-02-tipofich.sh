#!/bin/sh

if test $# -ne 1
then
	echo "usage: $0 path" >&2
	exit 1
fi

if test -L "$1"
then
	echo "$1 es un enlace simbolico"
elif test -f "$1"
then
	echo "$1 es un fichero regular"
elif test -d "$1"
then
	echo "$1 es un directorio"
else
	echo "$1 no existe"
fi

exit 0