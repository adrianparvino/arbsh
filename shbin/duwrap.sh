#!/bin/sh 

duprint()
{ 
	if [ "$#" -gt 1 ]
	then	printf "%s" $( eval printf '$'$(( $# - 1 )))
	fi
}

duwrap()
{
	duprint $(du -s $@ 2>/dev/null)
}

duwrap "$@"


