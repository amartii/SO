#!/bin/sh
echo hola >> /tmp/bola.txt
echo adios >> /tmp/idios.txt
echo que tal >> /tmp/cetal.txt
echo que tal >> /tmp/atal.txt
echo que tal >> /tmp/atal.txt

cat /tmp/*.txt | sort | uniq > /tmp/todos.txt  

cat /tmp/todos.txt

rm /tmp/bola.txt
rm /tmp/idios.txt
rm /tmp/cetal.txt
rm /tmp/atal.txt
rm /tmp/todos.txt
exit 0