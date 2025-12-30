#!/bin/sh

usage() {
	echo "usage: ./photocol.sh [collection] [photo directory] ... [photo directory]" >&2
	exit 1
}

check_num_args() {
	if test $# -lt 2
	then
		usage
	fi
}

check_dir() {
	if test ! -d "$1"
	then
		echo "error: '$1' is not a directory" >&2
		usage
	fi
}

check_input() {
	collection="$1"
	shift

	for dir in "$@"
	do
		check_dir "$dir"
	done
}

prepare_collection() {
	col="$1"

	if test -d "$col"
	then
		rm -rf "$col"/* 2>/dev/null
	else
		mkdir -p "$col" || exit 1
	fi
}

split_path() {
	ext=".${ruta_formatos##*.}"
	sin_ext=${ruta_formatos%.*}
	dir_path=${sin_ext%/*}
	dir_name=${dir_path##*/}
	file_name=${sin_ext##*/}

	dir_name=$(printf "%s\n" "$dir_name" | tr ' ' '-')
	file_name=$(printf "%s\n" "$file_name" | tr ' ' '-')
}

join_path() {
	ruta_final="${dir_name}_${file_name}${ext}"
}

formato() {
	ruta="$1"

	ruta_minusculas=$(printf "%s\n" "$ruta" | tr 'A-Z' 'a-z')
	ruta_formatos=$(printf "%s\n" "$ruta_minusculas" | sed 's/\.jpeg$/\.jpg/')

	split_path
	join_path

	printf "%s\n" "$ruta_final"
}

detect_collision() {
	name="$1"

	if test -e "$collection/$name"
	then
		echo "error: collision on '$name'" >&2
		rm -rf "$collection"/* 2>/dev/null
		exit 1
	fi
}

fill_metadata() {
	tmp_fotos=$(mktemp) || exit 1

	find "$@" \
		\( -iname "*.png" -o -iname "*.tiff" -o -iname "*.jpg" -o -iname "*.jpeg" \) \
		-print > "$tmp_fotos"

	while IFS= read -r ruta
	do
		nombre_final=$(formato "$ruta") || continue
		detect_collision "$nombre_final"

		cp -- "$ruta" "$collection/$nombre_final" || exit 1

		size=$(wc -c < "$collection/$nombre_final")
		size_total=$((size_total + size))

		echo "$nombre_final	$size" >> "$meta"
	done < "$tmp_fotos"

	rm -f "$tmp_fotos"
}

sort_metadata() {
	sort -n -k2 "$meta" > "$meta.sorted" || exit 1
	mv "$meta.sorted" "$meta"
}

check_num_args "$@"
check_input "$@"

collection="$1"
shift

prepare_collection "$collection"

meta="$collection/metadata.txt"
: > "$meta"

size_total=0

fill_metadata "$@"
sort_metadata

echo "TOTAL: $size_total bytes" >> "$meta"

exit 0