#!/bin/sh

# quickly make a chroot using ldd

set -xe

[ "$#" -lt 2 ] && { echo "Usage $0 /path/tool mychroot" ; exit ; }


dirnametool()
{ 
	if [ -e dirnamesh ]
	then 	./dirnamesh $1
	else	dirname $1
	fi
	
}


for i in $(ldd $1)
do case "$i" in
	*/* ) 	mkdir -p ${2}/$(dirnametool $i)
		cp $i ${2}/$(dirnametool $i) 
		;;
	esac
done

mkdir -p ${2}/$(dirnametool $1)
cp $1 ${2}/$(dirnametool $1)
