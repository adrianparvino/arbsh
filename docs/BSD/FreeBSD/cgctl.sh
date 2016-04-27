#!/bin/sh 

# (C) 2014, cgctl, cgraf, MIT License 

SRCCODE="/usr/src"
BINNAME="crunched"
IMGSIZE="20m"
IMGNAME="mfsroot"
STRTDIR="$(pwd)"

help()
{

	printf  "$0 :


	--crt_crunch      Creates the crunched binary 'crunched'.
	--crt_chroot      Creates a chroot with the crunched bin at 'mnt'.
	--crt_ramdisk     Create a ramdisk with the chroot at 'mnt'.
	--programs=LIST   Use a whitespace delineated list of programs
			  instead of the file 'crunchlist'. 
	--help            This help screen.
	--clean           Delete everything and get ready for a new build.

	Usage:  cgctl --crt_crunch --crt_chroot --crt_ramdisk
	Usage:  cgctl --crt_crunch --crt_chroot
	        ... some custom action to modify 'mnt'
	        cgctl --crt_ramdisk
	Usage:  cgctl --crt_crunch \\
		--crt_chroot \\
		--crt_ramdisk \\
		--programs=\"cat ls sh top csh init\" 
		

	Cgctl is a script to automate the process of using crunchgen
	to create an mfsroot or to otherwise automate the creation of
	crunched binaries.
	
	cgctl requires the presence of the file 'crunchlist' which must
	contain an entry for each program you wish to crunch on its own
	line. It can not contain any additional comments and must be
	in the directory that this script is being run from. 
	\n"

	exit 0

}

dog()
{ 
        i="${1}"

        while IFS= read j
        do      printf '%s\n' "$j"
        done < "${i:=/dev/stdin}"

} 


cdwrap()
{
	mkdir -p "$1"

        if ! cd "$1"
        then    printf "Unable to cd to %s. exiting..\n" "$1"
                exit 1
        fi
}

checkfile()
{
	if ! [ -f "$1" ] 
	then 	"file '$1' does not exist! Exiting!"
		exit 1
	fi
} 

clean()
{ 
	rm "$IMGNAME" 
	rm "${IMGNAME}.gz"
	rm "$BINNAME"
	rm log_of_crt_crunch
	rm -rf mnt crnch
}


crt_crunch()
{ 
	cdwrap crnch 

	echo -n > "${BINNAME}.conf"
	echo "srcdirs ${SRCCODE}/bin" >> "${BINNAME}.conf" 
	echo "srcdirs ${SRCCODE}/sbin" >> "${BINNAME}.conf" 
	echo "srcdirs ${SRCCODE}/usr.bin" >> "${BINNAME}.conf" 
	echo "srcdirs ${SRCCODE}/usr.sbin" >> "${BINNAME}.conf" 
	echo "srcdirs ${SRCCODE}/libexec" >> "${BINNAME}.conf" 
	
	CGCTLPROGS=${CGCTLPROGS:=$(dog ../crunchlist)} 

	for i in $CGCTLPROGS
	do
		if [ -e ${SRCCODE}/*/${i}/Makefile ]
		then
			echo "progs ${i}" >> "${BINNAME}.conf"
    
			for j in $(dog ${SRCCODE}/*/${i}/Makefile) 
			do 	case "$j" in 
				-l* ) 	echo "libs $j" >> "${BINNAME}.conf" 
					echo  "libs $j" >> ../log_of_crt_crunch 
					;;
				esac
			done 
		fi
   
	done 

	echo "ln sh -sh" >> "${BINNAME}.conf" 
	echo "ln csh -csh" >> "${BINNAME}.conf" 
	echo "ln test [" >> "${BINNAME}.conf" 

	BUILDENVARS=$(make -C ${SRCCODE} buildenvvars )

	eval $BUILDENVARS crunchgen  "${BINNAME}.conf"

	eval $BUILDENVARS make -f "${BINNAME}.mk" objs exe 

	# Leave behind a copy of the binary ( this should probably be replaced )
	cp "${BINNAME}"  "${STRTDIR}/{BINNAME}"

	cdwrap "$STRTDIR"

}

crt_chroot() 
{ 
	cdwrap /mnt 

	DIRLIST="sbin bin usr/bin usr/sbin" 

	mkdir sbin
	
	checkfile "${STRTDIR}/{BINNAME}"
	cp "${STRTDIR}/{BINNAME}" sbin/init



	CGCTLPROGS=${CGCTLPROGS:=$(dog ../crunchlist)} 

	for j in $DIRLIST
	do 	mkdir -p "$j" 
		for i in $CGCTLPROGS
		do 	echo "$i" >> "$STRTDIR/log_of_crt_chroot"
			ln sbin/init "${j}/${i}" 
		done 
	done 

	mkdir dev
	mkdir etc
	mkdir home
	mkdir root
	mkdir sys
	mkdir var
	mkdir tmp

	cdwrap "$STRTDIR" 
}



crt_ramdisk() 
{ 
	makefs -s "$IMGSIZE" -t ffs "$IMGNAME" mnt
	gzip -9 "$IMGNAME" -c > "${IMGNAME}.gz"
}


# Handle user options 
if [ "$#" = "0" ]
then 	help
fi

for i in "$@"
do
        case "$i" in
	--crt_crunch)
		CRTCRUNCHYES="1" 
		;;
	--crt_chroot)
		CRTCHROOTYES="1" 
		;;
	--crt_ramdisk)
		CRTRAMDISKYES="1" 
		;; 
        -h|--help|help)
                help
                ;;
	--clean)  
		CRTCLEANYES="1" 
                ;;
	--programs=*)
                CGCTLPROGS="${1#*=}" 
                ;; 
	esac
	shift
done

if [ "$CRTCLEANYES" = "1" ]
then	clean
fi

if [ "$CRTCRUNCHYES" = "1" ]
then	crt_crunch
fi

if [ "$CRTCHROOTYES" = "1" ]
then	crt_chroot
fi

if [ "$CRTRAMDISKYES" = "1" ]
then	crt_ramdisk
fi
