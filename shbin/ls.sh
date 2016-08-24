#!/bin/sh


# A simple implementation of ls in POSIX compatible shell

WORKD="."

STARS="/*"

CYCLE="0"

LINED=""

for i in ${WORKD}/$STARS
do	printf "%s\t" "$i"
	
	if [ "$(( $CYCLE % 2))" = "0" ]
	then printf "\n"
	fi
	CYCLE=$(($CYCLE + 1))
done
