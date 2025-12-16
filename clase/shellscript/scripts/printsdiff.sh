#!/bin/sh
echo 'con $@'
for i in $@
do
    echo "<$i>"
done

echo 'con "$@"'
for i in "$@"
do
    echo "<$i>"
done

echo 'con $*'
for i in $*
do
    echo "<$i>"
done

echo 'con "$*"'
for i in "$*"
do
    echo "<$i>"
done

exit 0