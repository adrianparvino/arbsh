#!/bin/sh

# Implementation of a whitespace padded array in POSIX sh

arrayd()
{
	INDICE="$1"
	if [ $# -gt 1 ]
	then	shift
	fi
	printf "%s" $( eval printf '$'$INDICE) 
}

STRING="$@"

arrayd $STRING


