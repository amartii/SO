#!/bin/sh

if test $# -ne 3
then
	echo "usage: $0 file old new" >&2
	exit 1
fi

if test ! -f "$1"
then
	echo "error: $1 not a regular file" >&2
	exit 1
fi

sed "s/$2/$3/g" "$1"

exit 0