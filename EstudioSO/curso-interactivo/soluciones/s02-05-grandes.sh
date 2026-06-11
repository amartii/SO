#!/bin/sh

if test $# -ne 2
then
	echo "usage: $0 dir min_kb" >&2
	exit 1
fi

if test ! -d "$1"
then
	echo "error: $1 not a directory" >&2
	exit 1
fi

dir="$1"
minkb="$2"

tab=$(printf '\t')

find "$dir" -type f -size +"${minkb}k" -exec du -k {} + | sort -n | while IFS="$tab" read -r size path
do
	echo "${size}K $path"
done

exit 0