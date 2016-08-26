#!/bin/sh


COUNT="0"

while IFS= read -r i 
do 	
	if [ "$COUNT" = "$1" ]
	then	break
	fi
	printf "%s\n" "$i"
	COUNT="$((COUNT + 1))"
done

