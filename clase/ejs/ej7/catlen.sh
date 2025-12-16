#!/bin/sh
usage(){
    echo usage: ./catlen.sh dir >&2
    exit 1
}

borrar_outputs(){
    rm -f "$1"/*.output 2>/dev/null
}

listar_txt(){
    (cd "$1" && ls *.txt 2>/dev/null | sort)
}

concatenar_txt(){
    listar_txt "$1" | while read fichero
    do 
        longitud=$(printf "%s\n" "$fichero" |wc -c)
        longitud=$((longitud-1))
        output="$longitud.output"
        cat "$fichero" >> "$output"
    done
}

if test $# -ne 1
then 
   usage
fi

if test ! -d "$1"
then
    echo error: $1 not a directory >&2
    usage
    
fi
borrar_outputs "$1"
concatenar_txt "$1"

exit 0