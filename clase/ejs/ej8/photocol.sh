#!/bin/sh

usage(){
    echo usage: ./photocol.sh [collection_dir] [photo_dir] ... >&2
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

num_args "$@"
entrada_correcta "$@"
prep_collection "$1"

exit 0
