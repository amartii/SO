#!/bin/sh

usage() {
	echo "usage: $0 dir" >&2
	exit 1
}

if test $# -ne 1
then
	usage
fi

if test ! -d "$1"
then
	echo "error: $1 not a directory" >&2
	usage
fi

dir="$1"

# Borrar outputs anteriores
rm -f "$dir"/*.output 2>/dev/null

# Procesar ficheros txt
(cd "$dir" && ls *.txt 2>/dev/null | sort) | while read fichero
do
	longitud=$(printf "%s\n" "$fichero" | wc -c)
	longitud=$((longitud - 1))
	output="$dir/$longitud.output"
	cat "$dir/$fichero" >> "$output"
done

exit 0
