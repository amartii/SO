#!/bin/sh

if test $# -ne 2
then
	echo "usage: $0 oldext newext" >&2
	exit 1
fi

for f in *."$1"
do
	if test -e "$f"
	then
		nuevo="${f%.$1}.$2"
		mv "$f" "$nuevo"
		echo "Renombrado: $f -> $nuevo"
	fi
done

exit 0