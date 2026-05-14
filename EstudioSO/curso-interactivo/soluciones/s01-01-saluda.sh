#!/bin/sh

if test $# -lt 1
then
	echo "usage: $0 nombre [nombres...]" >&2
	exit 1
fi

for name in "$@"
do
	echo "Hola $name"
done

exit 0
