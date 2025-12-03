#!/bin/sh

if test $# -lt 1
then
	echo usage: waitfiles.sh file [files...] >&2
	exit 1
fi

//comprobar esto: que no funciona
if test "$@" -f
then
	echo error: is not a regular file >&2
	exit 1
fi

echo hace cosas

exit 0
	
