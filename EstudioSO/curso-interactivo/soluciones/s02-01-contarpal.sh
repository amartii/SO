#!/bin/sh

if test $# -ne 2
then
	echo "usage: $0 file word" >&2
	exit 1
fi

if test ! -f "$1"
then
	echo "error: $1 not a regular file" >&2
	exit 1
fi

lineas=$(grep -F -c -- "$2" "$1")
echo "Lineas con '$2': $lineas"

exit 0