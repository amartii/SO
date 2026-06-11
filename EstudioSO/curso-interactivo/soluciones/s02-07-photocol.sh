#!/bin/sh

usage() {
	echo "usage: $0 dest src [src...]" >&2
	exit 1
}

if test $# -lt 2
then
	usage
fi

dest="$1"
shift

if test ! -d "$dest"
then
	mkdir -p "$dest" || exit 1
fi

tmpmap=$(mktemp) || exit 1

for src in "$@"
do
	if test ! -d "$src"
	then
		echo "error: $src not a directory" >&2
		rm -f "$tmpmap"
		exit 1
	fi

	find "$src" -type f \( -iname '*.jpg' -o -iname '*.jpeg' -o -iname '*.png' \) | while IFS= read -r file
	do
		base=$(basename "$file")
		norm=$(printf '%s' "$base" | tr '[:upper:]' '[:lower:]' | tr ' ' '-' | sed 's/\.jpeg$/.jpg/')
		target="$dest/$norm"
		printf '%s\t%s\n' "$file" "$target" >> "$tmpmap"
	done
done

if test -n "$(cut -f2 "$tmpmap" | sort | uniq -d)"
then
	rm -f "$tmpmap"
	echo "error: collision detected" >&2
	exit 1
fi

tab=$(printf '\t')
collision=0
while IFS="$tab" read -r file target
do
	if test -e "$target"
	then
		collision=1
		break
	fi
done < "$tmpmap"

if test "$collision" -ne 0
then
	rm -f "$tmpmap"
	echo "error: collision detected" >&2
	exit 1
fi

while IFS="$tab" read -r file target
do
	cp "$file" "$target" || {
		rm -f "$tmpmap"
		exit 1
	}
done < "$tmpmap"

rm -f "$tmpmap"
exit 0