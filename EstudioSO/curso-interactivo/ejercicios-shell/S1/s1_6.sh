if test $# -ne 1
then 
    echo "error: usage $0 <dir>" >&2
    exit 1
fi 

if test ! -d $1
then 
    echo "error: $1 not a dir" >&2
    exit 1
fi

echo "terminan en .md"
find $1 -type f -name '*.md' -printf '%f\n'

echo "los que no terminen en .txt"
find $1 -type f ! -name '*.txt' -printf '%f\n'
exit 0