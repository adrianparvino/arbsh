#!/bin/sh

MIDDLE=pc-linux

export LOGM='>'

testcompiler()
{
	./${ARCH}-pc-linux-${VENDOR}-toolchain/bin/${ARCH}-pc-linux-${VENDOR}-gcc -v > \
		${ARCH}-${MIDDLE}-${VENDOR}-results 2>&1
	printf "%s\n" "Simple cat test (includes unistd.h)" >> \
		${ARCH}-${MIDDLE}-${VENDOR}-results 2>&1
	./${ARCH}-pc-linux-${VENDOR}-toolchain/bin/${ARCH}-pc-linux-${VENDOR}-gcc ../cbin/cat.c >> \
		${ARCH}-${MIDDLE}-${VENDOR}-results 2>&1 && \
		mv ${ARCH}-${MIDDLE}-${VENDOR}-results ${ARCH}-${MIDDLE}-${VENDOR}-good
}

document()
{
	rm ${ARCH}-${MIDDLE}-${VENDOR}-report
	printf "MACHTYPE == $MACHTYPE" >> ${ARCH}-${MIDDLE}-${VENDOR}-report 2>&1
	date >> ${ARCH}-${MIDDLE}-${VENDOR}-report 2>&1
	grep 'NAME' /etc/os-release >> ${ARCH}-${MIDDLE}-${VENDOR}-report 2>&1
	for i in *good
	do     
		[ -f ${i} ] && printf  "${MACHTYPE}\t--> ${i%-good}\n" >> \
			${ARCH}-${MIDDLE}-${VENDOR}-report 2>&1
	done
	
}
# document

BUILDBOOL=yes
#TEST1=yes
#TEST2=yes
#TEST3=yes
TEST4=yes
TEST5=yes
TEST6=yes



# Highly unlikely.
if [ "$TEST1" = "yes" ]
then
for j in musl uclibc gnu
do      for i in xtensa alpha c6x metag arc cris
        do      ARCH=$i
                VENDOR=$j
                if [ "$BUILDBOOL" = "yes" ]
                then    make $@ \
                        ARCH=$i \
                        VENDOR=$j \
                        LINUXARCH=$i \
                        UCLIBCTARG=$i >${ARCH}-${MIDDLE}-${VENDOR}-log 2>&1
                        testcompiler
                else    testcompiler
                fi
        done
done
fi


# Primary off-the-beaten-trail tests.
if [ "$TEST2" = "yes" ]
then
for j in musl uclibc gnu
do      for i in mips sh microblaze sparc
        do      ARCH=$i
                VENDOR=$j
                if [ "$BUILDBOOL" = "yes" ]
                then    make $@ \
                        ARCH=$i \
                        VENDOR=$j \
                        LINUXARCH=$i \
                        UCLIBCTARG=$i >${ARCH}-${MIDDLE}-${VENDOR}-log 2>&1
                        testcompiler
                else    testcompiler
                fi
        done
done
fi

# powerpc64 ( nice to test )

if [ "$TEST3" = "yes" ]
then
for j in musl uclibc gnu
do      for i in powerpc64
	do      ARCH=$i 
		VENDOR=$j
		if [ "$BUILDBOOL" = "yes" ]
                then 	make $@ \
			ARCH=$i \
			VENDOR=$j \
			LINUXARCH=powerpc \
			UCLIBCTARG=powerpc >${ARCH}-${MIDDLE}-${VENDOR}-log 2>&1
			testcompiler
		else	testcompiler
		fi
	done
done
fi

# aarch64 ( nice to test )

if [ "$TEST4" = "yes" ]
then
for j in musl uclibc gnu
do      for i in aarch64
	do      ARCH=$i 
		VENDOR=$j
		if [ "$BUILDBOOL" = "yes" ]
                then 	make $@ \
			ARCH=$i \
			VENDOR=$j \
			LINUXARCH=arm64 \
			UCLIBCTARG=arm >${ARCH}-${MIDDLE}-${VENDOR}-log 2>&1
			testcompiler
		else 	testcompiler 
		fi
	done
done
fi
# x86_64 ( nearly always builds )

if [ "$TEST5" = "yes" ]
then
for j in musl uclibc gnu
do      for i in x86_64
	do      ARCH=$i 
		VENDOR=$j
		if [ "$BUILDBOOL" = "yes" ]
                then 	make $@ \
			ARCH=$i \
			VENDOR=$j \
			LINUXARCH=x86_64 \
			UCLIBCTARG=x86_64 >${ARCH}-${MIDDLE}-${VENDOR}-log 2>&1
			testcompiler
		else	testcompiler
		fi
	done
done
fi

# *86 family ( nearly always builds )

if [ "$TEST6" = "yes" ]
then
for j in uclibc gnu musl
do	for i in i486 i586 i686
	do	ARCH=$i 
		VENDOR=$j
		if [ "$BUILDBOOL" = "yes" ]
		then	ARCH=$i VENDOR=$j
			make $@ \
			ARCH=$i \
			VENDOR=$j \
			LINUXARCH=x86 \
			UCLIBCTARG=i386
			testcompiler
		else 	testcompiler
		fi
	done
done
fi

document

