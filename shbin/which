#!/bin/sh

which()
{ 
	IFS=":"
	for i in $PATH
	do 	if stat ${i}/${1} >/dev/null 2>&1 
		then 	command -v ${i}/${1} >/dev/null 2>&1 && echo ${i}/${1} 
			exit
		fi
	done
}

which $@
