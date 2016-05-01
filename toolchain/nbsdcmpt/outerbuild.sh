#!/bin/sh

# rough notes for building netbsd on linux 
#export EXTERNAL_TOOLCHAIN=/home/blakor/cmgraff/grafland/toolchain/musl-toolchain-gcc-4.9.2-rotrial/
#export $(cd .. ; make  buildenvars)
#env 
#exit

export TOP_obj=$(pwd)/store
export MAKEOBJDIRPREFIX=$(pwd)/store
export MKMAN=no
export MKSHARE=no

HOLD=$(pwd)
OM_NBMAKE=${MAKEOBJDIRPREFIX}/$HOLD/usr/src/tooldir.Linux-3.2.0-4-amd64-x86_64/bin/nbmake-i386

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


#cp simplebuild.sh usr/src
# all work is done in the netbsd tree
cd usr/src
printf "build time\n" > ../../om_timestamp
date >> ../../om_timestamp

# simplebuild is the same as running ./build.sh -j8 -U -u -m i386 makewrapper
../../simplebuild.sh 

${OM_NBMAKE} do-top-obj do-tools-obj

${OM_NBMAKE} -C tools depend-nbperf all-nbperf install-nbperf
${OM_NBMAKE} -C tools depend-tic all-tic install-tic
#${OM_NBMAKE} -C tools depend-yacc all-yacc install-yacc 



#${OM_NBMAKE} -C tools depend-nbperf all-nbperf install-nbperf

#cd tools
#${OM_NBMAKE} depend-nbperf all-nbperf install-nbperf
#cd nbperf
#${OM_NBMAKE}
#${OM_NBMAKE} install
exit

${OM_NBMAKE} do-top-obj do-tools-obj do-tools -j8
date >> ../../om_timestamp

cat ../../om_timestamp
exit

${OM_NBMAKE} \
do-top-obj \
do-tools-obj \
do-tools \
obj \
do-distrib-dirs \
includes  \
do-tools-compat \
do-lib-csu \
do-libgcc \
do-libpcc \
do-lib-libc \
-j8

date >> ../../om_timestamp

cat ../../om_timestamp

# test the build system
cd bin/cat

${OM_NBMAKE} clean
${OM_NBMAKE}


#./build.sh -j8 -U -u -m i386 kernel=GENERIC 
#cp usr/src/sys/arch/amd64/conf/INSTALL usr/src/sys/arch/amd64/conf/MY_KERNEL 
