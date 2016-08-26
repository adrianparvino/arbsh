#!/bin/sh 

stdinout()
{
	while IFS='' read -r i
	do	printf '%s\n' "$i"
	done
}

dog()
{ 
	[ "$#" = 0 ] && stdinout 
	
	while [ "$#" -gt 0 ]
	do	stdinout < "$1"
		shift
	done

}

dog $@




