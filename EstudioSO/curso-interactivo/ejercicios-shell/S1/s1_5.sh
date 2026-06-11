#!/bin/sh

if test $# -ne 2
then
    echo "error: usage $0 <old extension> <new extension>" >&2
    exit 1
fi

for f in *."$1"
do
    nuevo = "${f%.$1}.$2"
    mv "$f" "$nuevo"
    echo "Renombrado: $f -> $nuevo"
done

exit 0