#!/bin/sh 

#(C) Copyright 2015. `Omnicross'. MIT/BSD 2 clause license, CM Graff



if [ "$1" = "-h" ] 
then	tail -n 50 "$0"
	exit 0
fi

set -x

USELIBC="musl"

MYTARG="i686-pc-linux-${USELIBC}"
MYLINUXARCH="x86"
MYBACKWARDCOMPAT="i386"

MYPREF="$(pwd)/toolchain/"
MYSRC="$(pwd)/src"
MYPATCH="$(pwd)/patches"
MYSTARTDIR="$(pwd)"

MYSFX="tar.gz" 
MYBINUTILS="binutils-2.25"
MYGCC="gcc-4.9.2"
MYGMP="gmp-5.1.3"
MYMPC="mpc-1.0.2"
MYMPFR="mpfr-3.1.2"
MYLINUX="linux-4.1"
#MYMUSL="musl-1.1.11"
MYMUSL="musl-1.1.6"

MYGLIBC="glibc-2.20"
MYUCLIBC="uClibc-ng-1.0.6"
MYDIET="dietlibc-0.33"
MYNEWLIB="newlib-2.2.0"

MYJOBS="-j8"
MYLANGS="c,c++"

#MYCONF="--disable-multilib "

KERNEL_MRR="https://www.kernel.org/pub/linux/kernel/v4.x/"
GNU_MRR="https://ftp.gnu.org/gnu"
MUSL_MRR="http://www.musl-libc.org/releases"
DIET_MRR="http://www.csit.parkland.edu/~cgraff1/src/"
UCLIBC_MRR="http://downloads.uclibc-ng.org/releases/1.0.6/"

# packages
MYVIM="vim-7.3.547"
MYBUSYBOX="busybox-1.21.1"
BUSYBOX_MRR="http://www.csit.parkland.edu/~cgraff1/src/"
MYDASH="dash-0.5.8"
DASH_MRR="http://www.csit.parkland.edu/~cgraff1/src/"
MYHTOP="htop-0.8"
HTOP_MRR="http://hisham.hm/htop/releases/0.8/"
MYNCURSES="ncurses-5.9"
NCURSES_MRR="http://www.csit.parkland.edu/~cgraff1/src/"
MYCOREUTILS="coreutils-8.23"
COREUTILS_MRR="http://www.csit.parkland.edu/~cgraff1/src/"
MYDROPBEAR="dropbear-2015.67"
DROPBEAR_MRR="http://www.csit.parkland.edu/~cgraff1/src/"
MYZLIB="zlib-1.2.8"
ZLIB_MRR="http://www.csit.parkland.edu/~cgraff1/src/"
MYPARTED="parted-3.1"
MYUTILLINUX="util-linux-2.26.2"
UTILLINUX_MRR="http://www.csit.parkland.edu/~cgraff1/src/"
MYE2FSPROGS="e2fsprogs-1.42.13"
MYDHCP="dhcp-4.1-ESV-R11"
DHCP_MRR="http://www.csit.parkland.edu/~cgraff1/src/"
MYNETTOOLS="net-tools-3eb367aedf1280f35105ede465c350a39b55fa91"

# Release handling

RELVERS="${RELVERS:=1.4}"
RELMRR="${RELMRR:=http://www.csit.parkland.edu/~cgraff1/}"

# Functions

mkdir_cd()
{
	rm -rf "$1"
	mkdir -p "$1" || true
	cd "$1"
}

del_tar_cd()
{ 
	rm -rf "${MYSTARTDIR}/${1}"
	tar -xf "${MYSRC}/${1}.${MYSFX}" -C "${MYSTARTDIR}"
	cd "${MYSTARTDIR}/${1}"
}

common_install_path()
{
	export PATH="${MYPREF}/bin:${PATH}"
	mkdir -p "${MYPREF}/${MYTARG}/usr/include" || true
	mkdir -p "${MYPREF}/${MYTARG}/include" || true
} 

common_source_stage()
{ 
	mkdir -p "${MYSRC}" || true
	cd "${MYSRC}"
	[ -f "${MYMUSL}.${MYSFX}" ] || wget "${MUSL_MRR}/${MYMUSL}.${MYSFX}"
	[ -f "${MYLINUX}.${MYSFX}" ] || wget "${KERNEL_MRR}/${MYLINUX}.${MYSFX}"
	[ -f "${MYGMP}.${MYSFX}" ] || wget "${GNU_MRR}/gmp/${MYGMP}.${MYSFX}"
	[ -f "${MYMPFR}.${MYSFX}" ] || wget "${GNU_MRR}/mpfr/${MYMPFR}.${MYSFX}"
	[ -f "${MYMPC}.${MYSFX}" ] || wget "${GNU_MRR}/mpc/${MYMPC}.${MYSFX}"
	[ -f "${MYGCC}.${MYSFX}" ] || wget "${GNU_MRR}/gcc/${MYGCC}/${MYGCC}.${MYSFX}"
	[ -f "${MYBINUTILS}.${MYSFX}" ] || wget "${GNU_MRR}/binutils/${MYBINUTILS}.${MYSFX}"
	[ -f "${MYGLIBC}.${MYSFX}" ] || wget "${GNU_MRR}/glibc/${MYGLIBC}.${MYSFX}"
	[ -f "${MYDIET}.${MYSFX}" ] || wget "${DIET_MRR}/${MYDIET}.${MYSFX}"
	[ -f "${MYUCLIBC}.${MYSFX}" ] || wget "${UCLIBC_MRR}/${MYUCLIBC}.${MYSFX}" 

	# musl needs a gcc patch until gcc adds tuple naming support
	mkdir -p "${MYPATCH}" || true
	cd "${MYPATCH}"
	[ -f gcc-4.9.2-musl.diff ] || wget "${DIET_MRR}/gcc-4.9.2-musl.diff"
	
}

common_clean_stage()
{
	rm -rf "${MYPREF}"
	rm -rf "${MYSTARTDIR}/${MYBINUTILS}"
	rm -rf "${MYSTARTDIR}/${MYGCC}"
	rm -rf "${MYSTARTDIR}/${MYGLIBC}"
	rm -rf "${MYSTARTDIR}/${MYLINUX}"
	rm -rf "${MYSTARTDIR}/${MYMPC}"
	rm -rf "${MYSTARTDIR}/${MYMPC}-build"
	rm -rf "${MYSTARTDIR}/${MYMPFR}" 
	rm -rf "${MYSTARTDIR}/${MYMPFR}-build"
	rm -rf "${MYSTARTDIR}/${MYGMP}"
	rm -rf "${MYSTARTDIR}/${MYGMP}-build"
	rm -rf "${MYSTARTDIR}/${MYMUSL}"
	rm -rf "${MYSTARTDIR}/${MYUCLIBC}"
	rm -rf "${MYSTARTDIR}/${MYDIET}"
	rm -rf "${MYSTARTDIR}/${MYNEWLIB}"
	rm -rf "${MYSTARTDIR}/${MYBINUTILS}-build"
	rm -rf "${MYSTARTDIR}/${MYBINUTILS}-build-target"
	rm -rf "${MYSTARTDIR}/${MYGCC}-build"
	rm -rf "${MYSTARTDIR}/${MYGCC}-build-second"
	rm -rf "${MYSTARTDIR}/${MYGCC}-build-target"
	rm -rf "${MYSTARTDIR}/${MYGLIBC}-build"
	rm -rf "${MYSTARTDIR}/${MYNEWLIB}-build"
	rm -rf "${MYSTARTDIR}/${MYDASH}"
	rm -rf "${MYSTARTDIR}/${MYBUSYBOX}"
	rm -rf "${MYSTARTDIR}/a.out"
	rm -rf "${MYSTARTDIR}/libroot"
	rm -rf "${MYSTARTDIR}/testbin"
	rm -rf "${MYSTARTDIR}/testbin.c" 
}

common_binutils_stage_make()
{
	tar -xf "${MYSRC}/${MYBINUTILS}.${MYSFX}" -C "${MYSTARTDIR}"
	mkdir_cd "${MYSTARTDIR}/${MYBINUTILS}-build"
	"${MYSTARTDIR}/${MYBINUTILS}/configure" \
	--prefix="${MYPREF}" \
	--target="${MYTARG}" \
	$MYCONF 
	make "${MYJOBS}" 
}

common_binutils_stage_install()
{ 
	cd "${MYSTARTDIR}/${MYBINUTILS}-build" 
	make install 
} 

common_linux_stage()
{ 
	tar -xf "${MYSRC}/${MYLINUX}.${MYSFX}" -C "${MYSTARTDIR}"
	cd "${MYSTARTDIR}/${MYLINUX}" 
	make ARCH="${MYLINUXARCH}" \
	INSTALL_HDR_PATH="${MYPREF}/${MYTARG}/" \
	headers_install 
} 

common_gcc_stage_make()
{
	tar -xf "${MYSRC}/${MYGCC}.${MYSFX}" -C "${MYSTARTDIR}"
	tar -xf "${MYSRC}/${MYGMP}.${MYSFX}" -C "${MYSTARTDIR}"
	tar -xf "${MYSRC}/${MYMPFR}.${MYSFX}" -C "${MYSTARTDIR}" 
	tar -xf "${MYSRC}/${MYMPC}.${MYSFX}" -C "${MYSTARTDIR}"

	cd "${MYSTARTDIR}/${MYGCC}" 
	case "${USELIBC}" in
		musl) patch -p1 < "${MYSTARTDIR}/patches/${MYGCC}-musl.diff"
		;;
	esac
	ln -s "${MYSTARTDIR}/${MYMPFR}" mpfr 
	ln -s "${MYSTARTDIR}/${MYGMP}" gmp 
	ln -s "${MYSTARTDIR}/${MYMPC}" mpc 

	mkdir_cd "${MYSTARTDIR}/${MYGCC}-build" 
	"${MYSTARTDIR}/${MYGCC}/configure" \
	--prefix="${MYPREF}" \
	--target="${MYTARG}" \
	--enable-languages=c \
	--with-newlib \
	--disable-libssp \
	--disable-nls \
	--disable-libquadmath \
	--disable-threads \
	--disable-decimal-float \
	--disable-shared \
	--disable-libmudflap \
	--disable-libgomp \
	--disable-libatomic \
	$MYCONF 

	make "${MYJOBS}" CFLAGS="-O0 -g0" CXXFLAGS="-O0 -g0" 
}

common_gcc_stage_install()
{ 
	cd "${MYSTARTDIR}/${MYGCC}-build"
	make install 
} 

musl_stage()
{ 
	rm -rf "${MYSTARTDIR}/${MYMUSL}"
	tar -xf "${MYSRC}/${MYMUSL}.${MYSFX}" -C "${MYSTARTDIR}"
	cd "${MYSTARTDIR}/${MYMUSL}" 

	"${MYSTARTDIR}/${MYMUSL}/configure" \
	--prefix="/" \
	--enable-debug \
       	--enable-optimize \
       	CROSS_COMPILE="${MYTARG}-" CC="${MYTARG}-gcc" 
	make "${MYJOBS}" 
	
	make install DESTDIR="${MYPREF}/${MYTARG}/" 

	mkdir_cd "${MYSTARTDIR}/${MYGCC}-build-second"
	"${MYSTARTDIR}/${MYGCC}/configure" \
	--prefix="${MYPREF}" \
	--target="${MYTARG}" \
	--enable-languages="${MYLANGS}" \
	--disable-libmudflap \
	--disable-libsanitizer \
	--with-headers="${MYPREF}/${MYTARG}/include" \
	--disable-nls \
	--with-ld="${MYPREF}/bin/${MYTARG}-ld" \
	--with-as="${MYPREF}/bin/${MYTARG}-as" \
	$MYCONF 

	make "${MYJOBS}" 
	make install 

	cd "${MYSTARTDIR}/${MYMUSL}" 
       	make install DESTDIR="${MYPREF}/${MYTARG}/" 
} 

uclibc_stage()
{ 
	rm -rf "${MYSTARTDIR}/${MYUCLIBC}"
	tar -xf "${MYSRC}/${MYUCLIBC}.${MYSFX}" -C "${MYSTARTDIR}"
	cd "${MYSTARTDIR}/${MYUCLIBC}" 
	mkdir -p "${MYPREF}/${MYTARG}/usr/src/linux"
	echo "KERNEL_HEADERS=\"${MYPREF}/${MYTARG}/include\"" >> .config 
	echo "TARGET_${MYBACKWARDCOMPAT}=y" >> .config 
	echo "RUNTIME_PREFIX=\"${MYPREF}/${MYTARG}/\"" >> .config 
	echo "DEVEL_PREFIX=\"${MYPREF}/${MYTARG}/\"" >> .config 
	echo "HAVE_SHARED=y" >> .config 
	echo "UCLIBC_HAS_THREADS_NATIVE=y" >> .config 
	echo "UCLIBC_HAS_UTMPX=y" >> .config
	echo "UCLIBC_HAS_UTMP=y" >> .config
	echo "UCLIBC_SUSV3_LEGACY=y" >> .config
	echo "UCLIBC_HAS_WCHAR=y" >> .config
	echo "UCLIBC_HAS_NETWORK_SUPPORT=y" >> .config
	echo "UCLIBC_HAS_FULL_RPC=y" >> .config
	echo "UCLIBC_HAS_REENTRANT_RPC=y" >> .config
	echo "UCLIBC_HAS_RPC=y" >> .config

	echo y | make CROSS="${MYTARG}-" "${MYJOBS}" oldconfig 
	make CROSS="${MYTARG}-" PREFIX="" install 

	mkdir_cd "${MYSTARTDIR}/${MYGCC}-build-second" 
       	#--disable-libquadmath \ 

	"${MYSTARTDIR}/${MYGCC}/configure" \
	--prefix="${MYPREF}" \
	--target="${MYTARG}" \
	--enable-languages="${MYLANGS}" \
	--disable-libmudflap \
	--disable-libsanitizer \
	--with-headers="${MYPREF}/${MYTARG}/include" \
	--disable-nls \
	--with-ld="${MYPREF}/bin/${MYTARG}-ld" \
	--with-as="${MYPREF}/bin/${MYTARG}-as" \
	$MYCONF

       	make "${MYJOBS}"
       	make install 

	cd "${MYPREF}/${MYTARG}/lib" 
	ln -s ld-uClibc.so.1 ld-uClibc.so.0 || true
	ln -s ld-uClibc.so.2 ld-uClibc.so.0 || true 
} 

gnu_stage()
{ 
	tar -xf "${MYSRC}/${MYGLIBC}.${MYSFX}" -C ${MYSTARTDIR}
	mkdir_cd "${MYSTARTDIR}/${MYGLIBC}-build" 
	
       	"${MYSTARTDIR}/${MYGLIBC}/configure" \
       	--prefix="${MYPREF}/${MYTARG}" \
	--host="${MYTARG}" \
	--build="${MACHTYPE}" \
	--target="${MYTARG}" \
	--with-headers="${MYPREF}/${MYTARG}/include" \
	--disable-werror \
	--enable-obsolete-rpc \
	--enable-kernel=2.6.32 \
	--enable-add-ons \
	libc_cv_forced_unwind=yes \
	libc_cv_c_cleanup=yes \
	libc_cv_ctors_header=yes \
	${MYCONF} 

	make "${MYJOBS}" 
	make install 

	mkdir_cd "${MYSTARTDIR}/${MYGCC}-build-second"
	"${MYSTARTDIR}/${MYGCC}/configure" \
	--prefix="${MYPREF}" \
	--target="${MYTARG}" \
	--enable-languages="${MYLANGS}" \
	--with-headers="${MYPREF}/${MYTARG}/include" \
        --with-ld="${MYPREF}/bin/${MYTARG}-ld" \
        --with-as="${MYPREF}/bin/${MYTARG}-as" \
        --disable-werror \
        --disable-shared \
        $MYCONF 

	make "${MYJOBS}" 
	make install 
	
	cd "${MYSTARTDIR}/${MYGLIBC}-build"
        make "${MYJOBS}"
        make install
	cd "${MYPREF}/${MYTARG}/"
        (
                IFS='/'
                for i in ${MYPREF}/${MYTARG}/
                do      j="${j}../"
                done
                mkdir_cd "./${MYPREF}/${MYTARG}/"
                ln -s "${j}/lib" lib
        ) 
}
dietlibc_stage()
{
        rm -rf "${MYSTARTDIR}/${MYDIET}"
        tar -xf "${MYSRC}/${MYDIET}.${MYSFX}" -C "${MYSTARTDIR}"
        cd "${MYSTARTDIR}/${MYDIET}"
        set +e
        make ARCH="${MYBACKWARDCOMPAT}" CROSS="${MYTARG}-" all
        #make ARCH="${MYBACKWARDCOMPAT}" CROSS="${MYTARG}-" dyn
        make ARCH="${MYBACKWARDCOMPAT}" DESTDIR="${MYPREF}" prefix="" install
        cp "bin-${MYBACKWARDCOMPAT}/diet" "${MYPREF}/bin/"
        cp "bin-${MYBACKWARDCOMPAT}/diet" "${MYPREF}/bin/${MYTARG}-diet"
        printf "To use the dietlibc cross compiler run:\n"
        printf "PATH=$PATH \\\\\n"
        printf "  diet ${MYTARG}-gcc some.c\n"
}

# Helper functions for making releases and updating the web page
make_release()
{ 
        cp -r omnicross "omnicross-${RELVERS}"
        tar -c "omnicross-${RELVERS}" | gzip -c > "omnicross-${RELVERS}.tar.gz"
}

update_page()
{ 
        echo "<html>" >> index.html
        echo "  <A HREF=\"../omnicross-${RELVERS}.tar.gz\">omnicross-${RELVERS}.tar.gz</A>" >> index.html
        echo "  <br>" >> index.html
        echo "</html>" >> index.html
	echo "	${RELMRR}/omnicross-${RELVERS}.tar.gz" >> README
}

# Stages for target packages and testing
make_libroot()
{ 
	mkdir_cd "${MYSTARTDIR}/libroot" 
	cp -r "${MYPREF}/"*-*/* "${MYSTARTDIR}/libroot/" 
}

test_libroot()
{ 
	cd "${MYSTARTDIR}"
	echo "#include <stdio.h>" > testbin.c
	echo "int main(){" >> testbin.c 
	echo "	printf(\"\\\n\\\nThis is the Omnicross test binary!\\\n\");" >> testbin.c
	echo "	return 0 ; }" >> testbin.c 
	"${MYPREF}/bin/${MYTARG}-gcc" "${MYSTARTDIR}/testbin.c" -o "${MYSTARTDIR}/libroot/testbin" 
	sudo chroot "${MYSTARTDIR}/libroot/" "/testbin"
}

get_packages()
{
	mkdir -p "${MYSRC}" || true
	cd "${MYSRC}"
	[ -f "${MYSRC}/${MYBUSYBOX}.${MYSFX}" ] || wget "${BUSYBOX_MRR}${MYBUSYBOX}.${MYSFX}"
	[ -f "${MYSRC}/omnicross-busybox-minimal.1" ] || wget "${BUSYBOX_MRR}/omnicross-busybox-minimal.1"
	[ -f "${MYSRC}/${MYDASH}.${MYSFX}" ] || wget "${DASH_MRR}/${MYDASH}.${MYSFX}"
	[ -f "${MYSRC}/${MYHTOP}.${MYSFX}" ] || wget "${HTOP_MRR}/${MYHTOP}.${MYSFX}"
	[ -f "${MYSRC}/${MYNCURSES}.${MYSFX}" ] || wget "${NCURSES_MRR}/${MYNCURSES}.${MYSFX}"
	[ -f "${MYSRC}/${MYVIM}.${MYSFX}" ] || wget "${NCURSES_MRR}/${MYVIM}.${MYSFX}"
	[ -f "${MYSRC}/${MYZLIB}.${MYSFX}" ] || wget "${ZLIB_MRR}/${MY}.${MYSFX}"
	[ -f "${MYSRC}/${MYDROPBEAR}.${MYSFX}" ] || wget "${DROPBEAR_MRR}/${MY}.${MYSFX}"
	[ -f "${MYSRC}/${MYUTILLINUX}.${MYSFX}" ] || wget "${UTILLINUX_MRR}/${MY}.${MYSFX}"
	[ -f "${MYSRC}/${MYCOREUTILS}.${MYSFX}" ] || wget "${COREUTILS_MRR}/${MY}.${MYSFX}"
	[ -f "${MYSRC}/${MYE2FSPROG}.${MYSFX}" ] || wget "${E2FSPROGS_MRR}/${MY}.${MYSFX}"
	[ -f "${MYSRC}/${MYDHCP}.${MYSFX}" ] || wget "${DHCP_MRR}/${MY}.${MYSFX}"
} 
clean_packages()
{
	rm -rf "${MYSTARTDIR}/${MYBUSYBOX}"
	rm -rf "${MYSTARTDIR}/${MYDASH}"
	rm -rf "${MYSTARTDIR}/${MYHTOP}"
	rm -rf "${MYSTARTDIR}/${MYNCURSES}"
	rm -rf "${MYSTARTDIR}/${MYVIM}"
	rm -rf "${MYSTARTDIR}/${MYZLIB}"
	rm -rf "${MYSTARTDIR}/${MYDROPBEAR}"
	rm -rf "${MYSTARTDIR}/${MYUTILLINUX}"
        rm -rf "${MYSTARTDIR}/${MYCOREUTILS}"
} 

clean_otterland()
{
	rm -rf "${MYSTARTDIR}/Gsh"
	rm -rf "${MYSTARTDIR}/cbin"
	rm -rf "${MYSTARTDIR}/irc"
}

make_environment()
{
	#export ARCH="${MYBACKWARDSCOMPAT}"
	
	export CROSS_COMPILE="${MYTARG}-"
	export CC="${MYTARG}-gcc"

	if [ "$USELIBC" = "dietlibc" ]
	then
		export CROSS_COMPILE="diet ${MYTARG}-" 
		export CC="diet ${MYTARG}-gcc"
	fi

	export LD="${MYTARG}-ld"
	export RANLIB="${MYTARG}-ranlib"
	export AS="${MYTARG}-as"
	export CPP="${MYTARG}-cpp"
	export CXX="${MYTARG}-g++"
	export NM="${MYTARG}-nm"
	export STRIP="${MYTARG}-strip" 
} 

make_gmp_target()
{ 
	mkdir_cd "${MYSTARTDIR}/${MYGMP}-build"
	"${MYSTARTDIR}/${MYGMP}/configure" \
	--prefix="${MYPREF}/${MYTARG}" \
	--host="${MYTARG%%-*}"
	make "${MYJOBS}"
	make install 
} 

make_mpc_target()
{ 
	mkdir_cd "${MYSTARTDIR}/${MYMPC}-build"
	"${MYSTARTDIR}/${MYMPC}/configure" \
	--prefix="${MYPREF}/${MYTARG}" \
	--host="${MYTARG%%-*}"
	make "${MYJOBS}"
	make install
} 

make_mpfr_target()
{ 
	mkdir_cd "${MYSTARTDIR}/${MYMPFR}-build"
	"${MYSTARTDIR}/${MYMPFR}/configure" \
	--prefix="${MYPREF}/${MYTARG}" \
	--host="${MYTARG%%-*}" 
	make "${MYJOBS}"
	make install 
} 

make_binutils_target()
{ 
	tar -xf "${MYSRC}/${MYBINUTILS}.${MYSFX}" -C "${MYSTARTDIR}"
	mkdir_cd "${MYSTARTDIR}/${MYBINUTILS}-build-target"
	"${MYSTARTDIR}/${MYBINUTILS}/configure" \
	--prefix="${MYSTARTDIR}/libroot" \
	--host="${MYTARG}" \
	--disable-werror 
	#--disable-libiberty
	make "${MYJOBS}"
	make install 
} 
make_gcc_target()
{ 
	mkdir_cd "${MYSTARTDIR}/${MYGCC}-build-target" 
	"${MYSTARTDIR}/${MYGCC}/configure" \
	--prefix="${MYSTARTDIR}/libroot" \
	--enable-languages=c \
	--disable-libssp \
	--disable-nls \
	--disable-libquadmath \
	--disable-threads \
	--disable-decimal-float \
	--disable-shared \
	--disable-libmudflap \
	--disable-libgomp \
	--disable-libatomic \
	--host=${MYTARG} \
	--target=${MYTARG} CFLAGS="-O0 -g0" CXXFLAGS="-O0 -g0" 

	make "${MYJOBS}"   
	make install  

	cp "${MYPREF}/lib/gcc/${MYTARG}/4.9.2/"* "${MYSTARTDIR}/libroot/lib/gcc/${MYTARG}/4.9.2/" 
	case "${USELIBC}" in
                musl) 	cd "${MYSTARTDIR}/${MYMUSL}"
			make install DESTDIR="${MYSTARTDIR}/libroot"
			;; 
        esac 
	
}

make_linux_target()
{
	tar -xf "${MYSRC}/${MYLINUX}.${MYSFX}" -C ${MYSTARTDIR}
	cd "${MYSTARTDIR}/${MYLINUX}" 
	
	#< CONFIG_8139CP=y
	#---
	#> # CONFIG_8139CP is not set
	
	
	make ARCH="${MYBACKWARDCOMPAT}" defconfig 
	sed -i 's|# CONFIG_8139CP is not set|CONFIG_8139CP=y|g' .config
	make "${MYJOBS}" \
	ARCH="${MYLINUXARCH}" \
	CROSS_COMPILE="${MYTARG}-"

	mkdir -p "${MYSTARTDIR}/libroot/boot"
	make \
	INSTALL_PATH="${MYSTARTDIR}/libroot/boot" \
	install ARCH="${MYLINUXARCH}" CROSS_COMPILE="${MYTARG}-"

	cd "${MYSTARTDIR}/libroot/boot"
	ln vmlinu* vmlinuz
}

make_dash_target()
{ 
	tar -xf "${MYSRC}/${MYDASH}.${MYSFX}" -C "${MYSTARTDIR}"
	cd "${MYSTARTDIR}/${MYDASH}"
	"${MYSTARTDIR}/${MYDASH}/configure" \
	--prefix="${MYSTARTDIR}/libroot" \
	--host="${MYTARG}"
	make "${MYJOBS}"
	make install
	
	cd "${MYSTARTDIR}/libroot/bin/"
	ln dash sh || true
}

make_busybox_target()
{ 
	tar -xf "${MYSRC}/${MYBUSYBOX}.${MYSFX}" -C "${MYSTARTDIR}"
	cd "${MYSTARTDIR}/${MYBUSYBOX}" 
	cp "${MYSRC}/omnicross-busybox-minimal.1" .config 
	make "${MYJOBS}"
	make CONFIG_PREFIX="${MYSTARTDIR}/libroot" install
}

make_htop_target()
{
	tar -xf "${MYSRC}/${MYHTOP}.${MYSFX}" -C "${MYSTARTDIR}"
	cd "${MYSTARTDIR}/${MYHTOP}"
	#"${MYSTARTDIR}/${MYHTOP}/autogen.sh"
	"${MYSTARTDIR}/${MYHTOP}/configure" \
        --prefix="${MYSTARTDIR}/libroot" \
	--host="${MYTARG%%-*}" \
	cross_compiling=yes
	# ac_user_opts__with_proc=no
	#--build="${MACHTYPE}" 
	
	make "${MYJOBS}"
        make install
}

make_ncurses_target()
{
        tar -xf "${MYSRC}/${MYNCURSES}.${MYSFX}" -C "${MYSTARTDIR}"
        cd "${MYSTARTDIR}/${MYNCURSES}"
	"${MYSTARTDIR}/${MYNCURSES}/configure" \
        --prefix="${MYPREF}/${MYTARG}" \
        --host="${MYTARG%%-*}"
        make "${MYJOBS}"
        make install

	cp -r "${MYPREF}/${MYTARG}/include/ncurses/"* "${MYPREF}/${MYTARG}/include/"
	cd "${MYPREF}/${MYTARG}/lib/"
	ln libncurses.a libtinfo.a
} 

make_vim_target()
{
        tar -xf "${MYSRC}/${MYVIM}.${MYSFX}" -C "${MYSTARTDIR}"
        cd "${MYSTARTDIR}/${MYVIM}"
        "${MYSTARTDIR}/${MYVIM}/configure" \
	--prefix="${MYPREF}/${MYTARG}" \
	--host="${MYTARG}" \
	--target="${MYTARG}" vim_cv_toupper_broken="yes"
        make "${MYJOBS}"
        make install DESTDIR="${MYSTARTDIR}/libroot"
}

make_coreutils_target()
{
        tar -xf "${MYSRC}/${MYCOREUTILS}.${MYSFX}" -C "${MYSTARTDIR}" 
        cd "${MYSTARTDIR}/${MYCOREUTILS}" 
        "${MYSTARTDIR}/${MYCOREUTILS}/configure" \
	--prefix="${MYSTARTDIR}/libroot" \
        --host="${MYTARG}" \
        --target="${MYTARG}" 
	#--enable-single-binary=symlinks \
        make "${MYJOBS}" 
        make install-exec
}

make_zlib_toolchain()
{ 
        tar -xf "${MYSRC}/${MYZLIB}.${MYSFX}" -C "${MYSTARTDIR}"
	cd "${MYSTARTDIR}/${MYZLIB}"
        "${MYSTARTDIR}/${MYZLIB}/configure" \
        --prefix="${MYPREF}/${MYTARG}"
        make "${MYJOBS}"
        make install
}
make_zlib_target()
{
	tar -xf "${MYSRC}/${MYZLIB}.${MYSFX}" -C "${MYSTARTDIR}"
        cd "${MYSTARTDIR}/${MYZLIB}"
	"${MYSTARTDIR}/${MYZLIB}/configure" \
        --prefix="${MYSTARTDIR}/libroot"
        make "${MYJOBS}"
        make install
}

make_dropbear_target()
{
	# TOOLCHAIN DEPENDENCY:
	make_zlib_toolchain
	# TARGET DEPENDENCY:
	make_zlib_target

	tar -xf "${MYSRC}/${MYDROPBEAR}.${MYSFX}" -C "${MYSTARTDIR}" 
        cd "${MYSTARTDIR}/${MYDROPBEAR}"
        "${MYSTARTDIR}/${MYDROPBEAR}/configure" \
        --host="${MYTARG}" \
        --target="${MYTARG}"
        make "${MYJOBS}" 
        make install DESTDIR="${MYSTARTDIR}/libroot" 
}

make_e2fsprogs_toolchain()
{
	tar -xf "${MYSRC}/${MYE2FSPROGS}.${MYSFX}" -C "${MYSTARTDIR}"
        cd "${MYSTARTDIR}/${MYE2FSPROGS}"
        "${MYSTARTDIR}/${MYE2FSPROGS}/configure" \
	--prefix="${MYPREF}/${MYTARG}" \
        --host="${MYTARG}" \
        --target="${MYTARG}" 
        make "${MYJOBS}"
	make install 
}

make_e2fsprogs_target()
{
        tar -xf "${MYSRC}/${MYE2FSPROGS}.${MYSFX}" -C "${MYSTARTDIR}"
        cd "${MYSTARTDIR}/${MYE2FSPROGS}"
        "${MYSTARTDIR}/${MYE2FSPROGS}/configure" \
        --prefix="${MYSTARTDIR}/libroot" \
        --host="${MYTARG}" \
        --target="${MYTARG}"
        make "${MYJOBS}"
        make install 
}

make_parted_target()
{
	# DEPENDENCY:
	#make_utillinux_target
	#make_e2fsprogs_toolchain
	
        tar -xf "${MYSRC}/${MYPARTED}.${MYSFX}" -C "${MYSTARTDIR}"
        cd "${MYSTARTDIR}/${MYPARTED}"
        "${MYSTARTDIR}/${MYPARTED}/configure" \
        --host="${MYTARG%-*}-gnu" \
        --target="${MYTARG%-*}-gnu" \
	--disable-device-mapper \
	--without-readline
        make "${MYJOBS}"
        make install-exec DESTDIR="${MYSTARTDIR}/libroot"
} 

make_utillinux_target()
{
        tar -xf "${MYSRC}/${MYUTILLINUX}.${MYSFX}" -C "${MYSTARTDIR}"
        cd "${MYSTARTDIR}/${MYUTILLINUX}"
        "${MYSTARTDIR}/${MYUTILLINUX}/configure" \
        --host="${MYTARG}" \
        --target="${MYTARG}" \
	--without-ncurses \
	--without-terminfo \
	--disable-more
        make "${MYJOBS}"
        make install DESTDIR="${MYSTARTDIR}/libroot"
	make install DESTDIR="${MYPREF}/${MYTARG}"
	cp -r "${MYPREF}/${MYTARG}/usr/lib/" "${MYPREF}/${MYTARG}/lib/"
}

make_dhcp_target()
{
	tar -xf "${MYSRC}/${MYDHCP}.${MYSFX}" -C "${MYSTARTDIR}"
        cd "${MYSTARTDIR}/${MYDHCP}"
        "${MYSTARTDIR}/${MYDHCP}/configure" \
	--prefix="${MYSTARTDIR}/libroot" \
        --host="${MYTARG}" \
        --target="${MYTARG}" ac_cv_file__dev_random=yes
	make "${MYJOBS}"
	make install
}

make_nettools_target()
{
	#tar -xf "${MYSRC}/${MYNETTOOLS}.${MYSFX}" -C "${MYSTARTDIR}"
        cd "${MYSTARTDIR}/${MYNETTOOLS}"
        "${MYSTARTDIR}/${MYNETTOOLS}/configure.sh config.h" \
        --prefix="${MYSTARTDIR}/libroot" \
        --host="${MYTARG}" \
        --target="${MYTARG}" 
        make "${MYJOBS}"
        make install
}
make_Gsh_target()
{
	cd "${MYSTARTDIR}"
	ln -s ../Gsh .
	cd "${MYSTARTDIR}/Gsh"
	make clean
	make CFLAGS=-static
	make install DESTDIR="${MYSTARTDIR}/libroot/bin/"
	cd "${MYSTARTDIR}/libroot/bin/"
	ln -s gsh sh
}
make_irc_target()
{
	cd "${MYSTARTDIR}"
        ln -s ../irc .
        cd "${MYSTARTDIR}/irc"
        make clean
        make CFLAGS=-static
        make install DESTDIR="${MYSTARTDIR}/libroot/bin/"
}
make_cbin_target()
{
	cd "${MYSTARTDIR}"
        ln -s ../cbin .
        cd "${MYSTARTDIR}/cbin"
        make clean
        make
        make install DESTDIR="${MYSTARTDIR}/libroot/bin/"
}



# Run user requested components from cli and exit
for USERCLIOPTIONS in $@
do 	"$USERCLIOPTIONS"
	shift
	[ "$#" = "0" ] && exit 0
done 



# Omnicross 

# toolchain stages: 

	common_install_path
	common_source_stage
	common_clean_stage
	common_binutils_stage_make
	common_binutils_stage_install
	common_linux_stage
	common_gcc_stage_make
	common_gcc_stage_install

	"${USELIBC}_stage"

# target package stages (not guaranteed to work for all targets and libc)

	#clean_packages
	#get_packages
	#make_environment
	#make_libroot
	#test_libroot 
	
	#make_gmp_target
	#make_mpfr_target
	#make_mpc_target
	#make_binutils_target
	#make_gcc_target

	
	#make_linux_target
	#make_dash_target
	#make_busybox_target
	#make_ncurses_target
	#make_htop_target
	#make_vim_target
	#make_coreutils_target
	#make_dropbear_target
	#make_parted_target
	#make_utillinux_target
	#make_e2fsprogs_target
	#make_dhcp_target

# GrafOS 
	
	#clean_otterland
	#make_irc_target
	#make_cbin_target
	#make_Gsh_target
	
	

