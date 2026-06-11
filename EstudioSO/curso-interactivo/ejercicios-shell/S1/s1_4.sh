#!/bin/sh

if test $# -ne 1
then
    echo "error: usage $0 <dir>" >&2
    exit 1
fi

if test ! -d "$1"
then 
    echo "error: $1 not a dir" >&2
    exit 1
fi

echo ".c: $(find "$1" -type f -name '*.c' |wc -l)"
echo ".h: $(find "$1" -type f -name '*.h'|wc -l)"
echo ".txt: $(find "$1" -type f -name '*.txt'|wc -l)"
echo "otros: $(find "$1" -type f ! -name '*.c' ! -name '*.h' ! -name '*.txt' | wc -l)"
exit 0