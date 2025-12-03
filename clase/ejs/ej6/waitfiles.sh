#!/bin/sh

if test $# -lt 1
then
	echo usage: waitfiles.sh file [files...] >&2
	exit 1
fi

for f in "$@"
do
	if test ! -f "$f"
	then
		echo error: $f is not a regular file >&2
		exit 1
	fi
done

queda_algo(){
	for f in "$@"
	do 
		if test -f "$f"
		then 
			return 0
		fi
	done
	return 1
}

#polling cada segundo
while queda_algo "$@"
do 
	sleep 1
done
echo done

exit 0
	
