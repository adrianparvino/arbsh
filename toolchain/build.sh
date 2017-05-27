#!/bin/sh

# mips sh microblaze sparc

ulimit -S -t 3600 -v 2000000 -u 1200

buildno="2"

make startreport
make OM_ARCH='i686' OM_LIBC='musl' BUILDNO=$buildno OM_LINUXARCH="x86" OM_BACKWARDCOMPAT="i386"
make clean OM_ARCH='i686' OM_LIBC='musl' BUILDNO=$buildno OM_LINUXARCH="x86" OM_BACKWARDCOMPAT="i386"
make OM_ARCH='x86_64' OM_LIBC='musl' BUILDNO=$buildno OM_LINUXARCH="x86_64" OM_BACKWARDCOMPAT="x86_64"
make clean OM_ARCH='x86_64' OM_LIBC='musl' BUILDNO=$buildno OM_LINUXARCH="x86_64" OM_BACKWARDCOMPAT="x86_64"
make OM_ARCH='aarch64' OM_LIBC='musl' BUILDNO=$buildno OM_LINUXARCH="arm64" OM_BACKWARDCOMPAT="arm64"
make clean OM_ARCH='aarch64' OM_LIBC='musl' BUILDNO=$buildno OM_LINUXARCH="arm64" OM_BACKWARDCOMPAT="arm64" 
make OM_ARCH='mips' OM_LIBC='musl' BUILDNO=$buildno OM_LINUXARCH="mips" OM_BACKWARDCOMPAT="mips"
make clean OM_ARCH='mips' OM_LIBC='musl' BUILDNO=$buildno OM_LINUXARCH="mips" OM_BACKWARDCOMPAT="mips"

make -i OM_ARCH='i686' OM_LIBC='uclibc' BUILDNO=$buildno OM_LINUXARCH="x86" OM_BACKWARDCOMPAT="i386"
make clean OM_ARCH='i686' OM_LIBC='uclibc' BUILDNO=$buildno OM_LINUXARCH="x86" OM_BACKWARDCOMPAT="i386"
make -i OM_ARCH='x86_64' OM_LIBC='uclibc' BUILDNO=$buildno OM_LINUXARCH="x86_64" OM_BACKWARDCOMPAT="x86_64"
make clean OM_ARCH='x86_64' OM_LIBC='uclibc' BUILDNO=$buildno OM_LINUXARCH="x86_64" OM_BACKWARDCOMPAT="x86_64"
make -i OM_ARCH='aarch64' OM_LIBC='uclibc' BUILDNO=$buildno OM_LINUXARCH="arm64" OM_BACKWARDCOMPAT="aarch64"
make clean OM_ARCH='aarch64' OM_LIBC='uclibc' BUILDNO=$buildno OM_LINUXARCH="arm64" OM_BACKWARDCOMPAT="aarch64"
make -i OM_ARCH='mips' OM_LIBC='uclibc' BUILDNO=$buildno OM_LINUXARCH="mips" OM_BACKWARDCOMPAT="mips"
make clean OM_ARCH='mips' OM_LIBC='uclibc' BUILDNO=$buildno OM_LINUXARCH="arm64" OM_BACKWARDCOMPAT="mips"

make OM_ARCH='i686' OM_LIBC='gnu' BUILDNO=$buildno OM_LINUXARCH="x86" OM_BACKWARDCOMPAT="i386"
make clean OM_ARCH='i686' OM_LIBC='gnu' BUILDNO=$buildno OM_LINUXARCH="x86" OM_BACKWARDCOMPAT="i386"
make OM_ARCH='x86_64' OM_LIBC='gnu' BUILDNO=$buildno OM_LINUXARCH="x86_64" OM_BACKWARDCOMPAT="x86_64"
make clean OM_ARCH='x86_64' OM_LIBC='gnu' BUILDNO=$buildno OM_LINUXARCH="x86_64" OM_BACKWARDCOMPAT="x86_64"
make OM_ARCH='aarch64' OM_LIBC='gnu' BUILDNO=$buildno OM_LINUXARCH="arm64" OM_BACKWARDCOMPAT="arm64"
make clean OM_ARCH='aarch64' OM_LIBC='gnu' BUILDNO=$buildno OM_LINUXARCH="arm64" OM_BACKWARDCOMPAT="arm64"
make OM_ARCH='mips' OM_LIBC='gnu' BUILDNO=$buildno OM_LINUXARCH="mips" OM_BACKWARDCOMPAT="mips"
make clean OM_ARCH='mips' OM_LIBC='gnu' BUILDNO=$buildno OM_LINUXARCH="mips" OM_BACKWARDCOMPAT="mips"



make startreport









