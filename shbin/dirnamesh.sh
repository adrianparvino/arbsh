#!/bin/sh

dirnamesh()
{
	# record $1 into a mutable variable
	DIRNAME="$1" 
	# remove trailing /s
	HOLD=""
	while [ "$DIRNAME" != "$HOLD" ]
	do	HOLD="$DIRNAME"
		DIRNAME="${DIRNAME%/}"
		COUNT=$((COUNT + 1))
	done
	# remove the remaining name
	DIRNAME="${DIRNAME%/*}"
	# return the string to stdout
	printf -- "%s\n" "${DIRNAME}" 
}

dirnamesh $1
