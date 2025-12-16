#!/bin/sh
ls -l | while read line
do 
    echo una linea: $line
done
exit 0