#!/bin/sh

if test $# -ne 1
then
	echo "usage: $0 file" >&2
	exit 1
fi

if test ! -f "$1"
then
	echo "error: $1 not a regular file" >&2
	exit 1
fi

tr '[:upper:]' '[:lower:]' < "$1" | tr -cs '[:alnum:]' '\n' | sed '/^$/d' | sort | uniq -c | sort -rn | head -5

exit 0