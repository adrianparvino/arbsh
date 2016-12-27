#!/bin/sh

basenamesh()
{
	# record $1 into a mutable variable
	BASENAME="$1" 
	# remove trailing /s
	HOLD=""
	while [ "$BASENAME" != "$HOLD" ]
	do	HOLD="$BASENAME"
		BASENAME="${BASENAME%/}"
		COUNT=$((COUNT + 1))
	done
	# remove the directory names
	BASENAME="${BASENAME##*/}"
	# return the string to stdout
	printf -- "%s\n" "${BASENAME}" 
}

basenamesh $1
