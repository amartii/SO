#!/bin/sh

if test $# -ne 1
then
	echo "usage: $0 dir" >&2
	exit 1
fi

if test ! -d "$1"
then
	echo "error: $1 not a directory" >&2
	exit 1
fi

find "$1" -type f | awk '
function ext(path, base, parts, n) {
	base = path
	sub(/^.*\//, "", base)
	if (base ~ /^\./) {
		return "otros"
	}
	n = split(base, parts, ".")
	if (n < 2) {
		return "otros"
	}
	if (parts[n] == "txt" || parts[n] == "c" || parts[n] == "h") {
		return "." parts[n]
	}
	return "otros"
}
{
	contador[ext($0)]++
}
END {
	printf ".c: %d\n", contador[".c"] + 0
	printf ".h: %d\n", contador[".h"] + 0
	printf ".txt: %d\n", contador[".txt"] + 0
	printf "otros: %d\n", contador["otros"] + 0
}'

exit 0