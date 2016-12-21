#!/bin/sh

# A hack to quickly make a chroot using ldd

[ "$#" -lt 2 ] && { echo "Usage $0 /path/tool mychroot" ; exit ; } 

for i in $(ldd $1)
do case "$i" in
	*/* ) 	mkdir -p ${2}/$(dirname $i)
		cp $i ${2}/$(dirname $i) 
		;;
	esac
done

mkdir -p ${2}/$(dirname $1)
cp $1 ${2}/$(dirname $1)
