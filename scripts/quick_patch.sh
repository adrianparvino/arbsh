#!/bin/sh

if [ $# != 3 ]
then	printf -- "%s\n" "'file.c' 'message here' 'patchtitle'"
	exit
fi

git add $1
git commit -m $2
git format-patch -1 --stdout > ~/${3}.patch
cat ~/${3}.patch | curl -F 'sprunge=<-' http://sprunge.us



