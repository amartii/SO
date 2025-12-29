#!/bin/sh

usage(){
    echo usage: ./photocol.sh [collection] [photo directory] ... [photo directory] >&2
    exit 1
}

num_args(){
    if test $# -lt 2
    then
        usage
    fi
}

comprobar_dir(){
    if test ! -d "$1"
    then
        echo "error: '$1' is not a directory" >&2
        usage
        exit 1
    fi
}

entrada_correcta(){
    collection="$1"
    shift          # ahora "$@" son solo los dirs de fotos

    for dir in "$@"
    do 
        comprobar_dir "$dir"
    done
}

prep_collection(){
    col="$1"

    if test -d "$col"
    then
        rm -rf "$col"/* 2>/dev/null
        rm -rf "$col"/.* 2>/dev/null
    else
        mkdir -p "$col" || exit 1
    fi
}

descomponer_ruta(){
    ext=".${ruta_formatos##*.}"
    sin_ext=${ruta_formatos%.*}
    dir_path=${sin_ext%/*}
    dir_name=${dir_path##*/}
    file_name=${sin_ext##*/}
    dir_name=$(printf "%s\n" "$dir_name"  | tr ' ' '-')
    file_name=$(printf "%s\n" "$file_name" | tr ' ' '-')
}

componer_ruta(){
    ruta_final="${dir_name}_${file_name}${ext}"
}

formato(){
    ruta="$1"
    ruta_minusculas=$(printf "%s\n" "$ruta" | tr 'A-Z' 'a-z')
    ruta_formatos=$(printf "%s\n" "$ruta_minusculas" | sed 's/\.jpeg$/\.jpg/')
    descomponer_ruta
    componer_ruta
    printf "%s\n" "$ruta_final"
}

detectar_colision(){
    nombre="$1"
    if test -e "$collection/$nombre"
    then
        echo "error: collision on '$nombre'" >&2
        rm -rf "$collection"/* 2>/dev/null
        rm -rf "$collection"/.* 2>/dev/null
        exit 1
    fi
}

num_args "$@"
entrada_correcta "$@"

collection="$1"
shift               # dirs de fotos quedan en "$@"

prep_collection "$collection"

#listamos las fotos
echo lista de fotos:
find "$@" \( -iname "*.png" -o -iname "*.tiff" -o -iname "*.jpg" -o -iname "*.jpeg" \) -print

meta="$collection/metadata.txt"
: > "$meta"
size_total=0

find "$@" \( -iname "*.png" -o -iname "*.tiff" -o -iname "*.jpg" -o -iname "*.jpeg" \) -print |
while read ruta
do 
    nombre_final=$(formato "$ruta") || continue
    detectar_colision "$nombre_final"
    cp -- "$ruta" "$collection/$nombre_final" || exit 1

    size=$(wc -c < "$collection/$nombre_final")
    size_total=$((size_total + size))

    echo "$nombre_final $size" >> "$meta"
done

# ordenar por tamaño numérico
sort -n -k2 "$meta" > "$meta.sorted"
mv "$meta.sorted" "$meta"

# añadir TOTAL al final
echo "TOTAL: $size_total bytes" >> "$meta"

echo -------
echo metadata.txt:
echo  
cat $meta


exit 0


