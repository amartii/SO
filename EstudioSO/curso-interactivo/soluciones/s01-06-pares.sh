#!/bin/sh

if test $# -lt 1
then
	echo "usage: $0 num [num...]" >&2
	exit 1
fi

es_par() {
	resto=$(($1 % 2))
	if test "$resto" -eq 0
	then
		return 0
	fi
	return 1
}

for n in "$@"
do
	if es_par "$n"
	then
		echo "$n es par"
	else
		echo "$n es impar"
	fi
done

exit 0