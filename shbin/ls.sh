#!/bin/sh


# A simple implementation of ls in POSIX compatible shell

array1()
{

	printf "%s" "$1"
}


echo $@
exit

WORKD="."

STARS="/*"

CYCLE="0"

LINED=""

for i in ${WORKD}/$STARS
do	#printf "%s\t" "$i"
	LINED="$LINED $i"
done




