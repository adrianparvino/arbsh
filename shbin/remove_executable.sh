#!/bin/sh

for i in * */* */*/* */*/*/*
do	if [ -d "$i" ]
	then echo "a dir"
	else chmod -x "$i"
	fi
done

