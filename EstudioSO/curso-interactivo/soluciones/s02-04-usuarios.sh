#!/bin/sh

awk -F: '{ print $1 ":" $7 }' /etc/passwd

exit 0