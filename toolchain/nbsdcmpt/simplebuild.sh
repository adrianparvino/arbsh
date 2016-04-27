#!/bin/bash

set -x 
mkdir -p $MAKEOBJDIRPREFIX 
MACHINE=i386
MACHINE_ARCH=i386
progname=${0##*/}
toppid=$$
results=/dev/null
export HOST_SH=/bin/bash 

bomb()
{ 
	echo $@
	exit 1
} 

which()
{
	(
		IFS=":"
		for dir in ${PATH}; do
			if [ -x "${dir}/${1}" ]; then
				result="${dir}/${1}"
				break
			fi
		done
	)
	printf "%s\n" "${result}"
} 

nobomb_getmakevar()
{
	[ -x "${make}" ] || return 1
	"${make}" -m ${TOP}/share/mk -s -B -f- _x_ <<EOF || return 1
_x_:
	echo \${$1}
.include <bsd.prog.mk>
.include <bsd.kernobj.mk>
EOF
} 

bomb_getmakevar()
{
	[ -x "${make}" ] || bomb "bomb_getmakevar $1: ${make} is not executable"
	nobomb_getmakevar "$1" || bomb "bomb_getmakevar $1: ${make} failed"
} 

getmakevar()
{
	if [ -x "${make}" ]; then
		bomb_getmakevar "$1"
	else
		echo "\$$1"
	fi
}

setmakeenv()
{
	eval "$1='$2'; export $1"
	makeenv="${makeenv} $1"
}

unsetmakeenv()
{
	eval "unset $1"
	makeenv="${makeenv} $1"
}

make_in_dir()
{
	dir="$1"
	op="$2"
	cd "${dir}" ||
	    bomb "Failed to cd to \"${dir}\""
	"${makewrapper}" ${parallel} ${op} ||
	    bomb "Failed to make ${op} in \"${dir}\""
	cd "${TOP}" ||
	    bomb "Failed to cd back to \"${TOP}\""
}

print_tooldir_make()
{
	local possible_TOP_OBJ
	local possible_TOOLDIR
	local possible_make
	local tooldir_make

	if [ -n "${TOOLDIR}" ]; then
		echo "${TOOLDIR}/bin/${toolprefix}make"
		return 0
	fi 
	local host_ostype="${uname_s}-$(
		echo "${uname_r}" | sed -e 's/([^)]*)//g' -e 's/ /_/g'
		)-$(
		echo "${uname_p}" | sed -e 's/([^)]*)//g' -e 's/ /_/g'
		)"

	for possible_TOP_OBJ in \
		"${TOP_objdir}" \
		"${MAKEOBJDIRPREFIX:+${MAKEOBJDIRPREFIX}${TOP}}" \
		"${TOP}" \
		"${TOP}/obj" \
		"${TOP}/obj.${MACHINE}"
	do
		[ -n "${possible_TOP_OBJ}" ] || continue
		possible_TOOLDIR="${possible_TOP_OBJ}/tooldir.${host_ostype}"
		possible_make="${possible_TOOLDIR}/bin/${toolprefix}make"
		if [ -x "${possible_make}" ]; then
			break
		else
			unset possible_make
		fi
	done
	
	: ${possible_make:=$(which ${toolprefix}make '')}
	: ${possible_make:=$(which nbmake '')}
	: ${possible_make:=$(which bmake '')}
	: ${possible_make:=$(which make '')} 

	if [ -x "${possible_make}" ]; then
		possible_TOOLDIR="$(
			make="${possible_make}" \
			nobomb_getmakevar TOOLDIR 2>/dev/null
			)"
		if [ $? = 0 ] && [ -n "${possible_TOOLDIR}" ] \
		    && [ -d "${possible_TOOLDIR}" ];
		then
			tooldir_make="${possible_TOOLDIR}/bin/${toolprefix}make"
			if [ -x "${tooldir_make}" ]; then
				echo "${tooldir_make}"
				return 0
			fi
		fi
	fi
	return 1
}


initdefaults()
{
	makeenv=
	makewrapper=
	makewrappermachine=
	runcmd=
	operations=
	removedirs=

	[ -d usr.bin/make ] || cd "$(dirname $0)"
	[ -d usr.bin/make ] ||
	    bomb "build.sh must be run from the top source level"
	[ -f share/mk/bsd.own.mk ] ||
	    bomb "src/share/mk is missing; please re-fetch the source tree"

	unsetmakeenv INFODIR
	unsetmakeenv LESSCHARSET
	unsetmakeenv MAKEFLAGS
	setmakeenv LC_ALL C 

	uname_s=$(uname -s 2>/dev/null)
	uname_r=$(uname -r 2>/dev/null)
	uname_m=$(uname -m 2>/dev/null)
	uname_p=$(uname -p 2>/dev/null || echo "unknown")
	case "${uname_p}" in
	''|unknown|*[^-_A-Za-z0-9]*) uname_p="${uname_m}" ;;
	esac

	id_u=$(id -u 2>/dev/null || /usr/xpg4/bin/id -u 2>/dev/null) 
	
	unset PWD
	TOP=$(/bin/pwd -P 2>/dev/null || /bin/pwd 2>/dev/null)
	setmakeenv MAKEOBJDIR "\${.CURDIR:C,^$TOP,$STUFF,}"
	setmakeenv HOST_SH "${HOST_SH}"
	setmakeenv BSHELL "${HOST_SH}"
	setmakeenv CONFIG_SHELL "${HOST_SH}" 
	toolprefix=nb
	do_expertmode=false

	tmpdir="${TMPDIR-/tmp}/nbbuild$$"
	mkdir "${tmpdir}" || bomb "Cannot mkdir: ${tmpdir}"
	
	results="${tmpdir}/build.sh.results" 

	setmakeenv NETBSDSRCDIR "${TOP}" 

	case "${KERNOBJDIR}" in
	''|/*)	;;
	*)	KERNOBJDIR="${TOP}/${KERNOBJDIR}"
		setmakeenv KERNOBJDIR "${KERNOBJDIR}"
		;;
	esac 

	DISTRIBVER="$(${HOST_SH} ${TOP}/sys/conf/osrelease.sh)"
	setmakeenv BUILDSEED "NetBSD-$(${HOST_SH} ${TOP}/sys/conf/osrelease.sh -m)"
	setmakeenv MKARZERO "yes"
	# parse options code
	setmakeenv MKUNPRIVED yes
	setmakeenv MKUPDATE yes

	makeenv="${makeenv} TOOLDIR MACHINE MACHINE_ARCH MAKEFLAGS"
	[ -z "${BUILDID}" ] || makeenv="${makeenv} BUILDID"
	MAKEFLAGS="-de -m ${TOP}/share/mk ${MAKEFLAGS}"
	MAKEFLAGS="${MAKEFLAGS} MKOBJDIRS=${MKOBJDIRS-yes}"
	export MAKEFLAGS MACHINE MACHINE_ARCH
}
rebuildmake()
{
	make="$(print_tooldir_make)"
	cd "${tmpdir}"
	env CC="${HOST_CC-cc}" CPPFLAGS="${HOST_CPPFLAGS}" \
		CFLAGS="${HOST_CFLAGS--O}" LDFLAGS="${HOST_LDFLAGS}" \
		${HOST_SH} "${TOP}/tools/make/configure" ||
	    bomb "Configure of ${toolprefix}make failed"
	${HOST_SH} buildmake.sh ||
	    bomb "Build of ${toolprefix}make failed"
	make="${tmpdir}/${toolprefix}make"
	cd "${TOP}"
	rm -f usr.bin/make/*.o usr.bin/make/lst.lib/*.o
}

validatemakeparams()
{ 
	MKOBJDIRS=$(getmakevar MKOBJDIRS)
	MKUNPRIVED=$(getmakevar MKUNPRIVED)
	MKUPDATE=$(getmakevar MKUPDATE) 

	mkdir -p "${TOP_obj}" ||
	    bomb "Can't create top level object directory" \
			"${TOP_obj}" 

	cd tools
	"${make}" -m ${TOP}/share/mk obj NOSUBDIR= ||
	    bomb "Failed to make obj in tools"
	cd "${TOP}" 
	
	
	for var in TOOLDIR DESTDIR
	do
		eval oldval=\"\$${var}\"
		newval="$(getmakevar $var)"
		if ! $do_expertmode; then
			: ${_SRC_TOP_OBJ_:=$(getmakevar _SRC_TOP_OBJ_)}
			case "$var" in
			DESTDIR)
				: ${newval:=${_SRC_TOP_OBJ_}/destdir.${MACHINE}}
				makeenv="${makeenv} DESTDIR"
				;; 
			esac
		fi
		eval ${var}=\"\${newval}\"
		eval export ${var}
	done

	# RELEASEMACHINEDIR is just a subdir name, e.g. "i386".
	RELEASEMACHINEDIR=$(getmakevar RELEASEMACHINEDIR)
	removedirs="${TOOLDIR}"
	removedirs="${removedirs} ${DESTDIR}"
}


createmakewrapper()
{ 
	mkdir -p "${TOOLDIR}/bin" 
	cp "${make}" "${TOOLDIR}/bin/${toolprefix}make" ||
	    bomb "Failed to install \$TOOLDIR/bin/${toolprefix}make"
	if [ -z "${makewrapper}" ]; then
		makewrapper="${TOOLDIR}/bin/${toolprefix}make-${makewrappermachine:-${MACHINE}}"
		[ -z "${BUILDID}" ] || makewrapper="${makewrapper}-${BUILDID}"
	fi

	rm -f "${makewrapper}" 
	makewrapout=">>\${makewrapper}"

	eval cat <<EOF ${makewrapout}
#! ${HOST_SH}
# Set proper variables to allow easy "make" building of a NetBSD subtree.
# Generated from:  \$NetBSD: build.sh,v 1.253.2.1 2012/03/02 16:48:10 riz Exp $
# with these arguments: ${_args}
#

EOF
	{
		for f in ${makeenv}; do
			if eval "[ -z \"\${$f}\" -a \"\${${f}-X}\" = \"X\" ]"; then
				eval echo "unset ${f}"
			else
				eval echo "${f}=\'\$$(echo ${f})\'\;\ export\ ${f}"
			fi
		done

		eval cat <<EOF
MAKEWRAPPERMACHINE=${makewrappermachine:-${MACHINE}}; export MAKEWRAPPERMACHINE
USETOOLS=yes; export USETOOLS
EOF
	} | eval sort -u "${makewrapout}"
	eval cat <<EOF "${makewrapout}"

exec "\${TOOLDIR}/bin/${toolprefix}make" \${1+"\$@"}
EOF
	[ "${runcmd}" = "echo" ] && echo EOF
	chmod +x "${makewrapper}"
}


# main 
initdefaults
rebuildmake
validatemakeparams
createmakewrapper

