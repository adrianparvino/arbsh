#!/bin/sh

populate()
{
	# wget http://ftp.netbsd.org/pub/pkgsrc/stable/pkgsrc.tar.bz2
	wget ftp://ftp.netbsd.org/pub/NetBSD/NetBSD-6.1.4/source/sets/gnusrc.tgz
	wget ftp://ftp.netbsd.org/pub/NetBSD/NetBSD-6.1.4/source/sets/sharesrc.tgz
	wget ftp://ftp.netbsd.org/pub/NetBSD/NetBSD-6.1.4/source/sets/src.tgz 
	wget ftp://ftp.netbsd.org/pub/NetBSD/NetBSD-6.1.4/source/sets/syssrc.tgz
}
if ! [ -e gnusrc.tgz ]
then	populate
fi


unpack()
{
	# tar -xf pkgsrc.tar.bz2
	for file in *.tgz
	do
		tar xfz $file
	done
}
if ! [ -d usr ]
then	# make a read only source tree
	unpack
	chmod -w -R usr
fi
(
	cd usr/src
	
