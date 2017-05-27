#!/bin/sh

buildno="2"

make startreport
make OM_ARCH='i686' OM_LIBC='musl' BUILDNO=$buildno OM_LINUXARCH="x86" OM_BACKWARDCOMPAT="i386"
make clean OM_ARCH='i686' OM_LIBC='musl' BUILDNO=$buildno OM_LINUXARCH="x86" OM_BACKWARDCOMPAT="i386"
make OM_ARCH='x86_64' OM_LIBC='musl' BUILDNO=$buildno OM_LINUXARCH="x86_64" OM_BACKWARDCOMPAT="x86_64"
make clean OM_ARCH='x86_64' OM_LIBC='musl' BUILDNO=$buildno OM_LINUXARCH="x86_64" OM_BACKWARDCOMPAT="x86_64"
make OM_ARCH='aarch64' OM_LIBC='musl' BUILDNO=$buildno OM_LINUXARCH="arm64" OM_BACKWARDCOMPAT="arm64"
make clean OM_ARCH='aarch64' OM_LIBC='musl' BUILDNO=$buildno OM_LINUXARCH="arm64" OM_BACKWARDCOMPAT="arm64"

make OM_ARCH='i686' OM_LIBC='uclibc' BUILDNO=$buildno OM_LINUXARCH="x86" OM_BACKWARDCOMPAT="i386"
make clean OM_ARCH='i686' OM_LIBC='uclibc' BUILDNO=$buildno OM_LINUXARCH="x86" OM_BACKWARDCOMPAT="i386"
make OM_ARCH='x86_64' OM_LIBC='uclibc' BUILDNO=$buildno OM_LINUXARCH="x86_64" OM_BACKWARDCOMPAT="x86_64"
make clean OM_ARCH='x86_64' OM_LIBC='uclibc' BUILDNO=$buildno OM_LINUXARCH="x86_64" OM_BACKWARDCOMPAT="x86_64"
make OM_ARCH='aarch64' OM_LIBC='uclibc' BUILDNO=$buildno OM_LINUXARCH="arm64" OM_BACKWARDCOMPAT="arm"
make clean OM_ARCH='aarch64' OM_LIBC='uclibc' BUILDNO=$buildno OM_LINUXARCH="arm64" OM_BACKWARDCOMPAT="arm"

make OM_ARCH='i686' OM_LIBC='gnu' BUILDNO=$buildno OM_LINUXARCH="x86" OM_BACKWARDCOMPAT="i386"
make clean OM_ARCH='i686' OM_LIBC='gnu' BUILDNO=$buildno OM_LINUXARCH="x86" OM_BACKWARDCOMPAT="i386"
make OM_ARCH='x86_64' OM_LIBC='gnu' BUILDNO=$buildno OM_LINUXARCH="x86_64" OM_BACKWARDCOMPAT="x86_64"
make clean OM_ARCH='x86_64' OM_LIBC='gnu' BUILDNO=$buildno OM_LINUXARCH="x86_64" OM_BACKWARDCOMPAT="x86_64"
make OM_ARCH='aarch64' OM_LIBC='gnu' BUILDNO=$buildno OM_LINUXARCH="arm64" OM_BACKWARDCOMPAT="arm64"
make clean OM_ARCH='aarch64' OM_LIBC='gnu' BUILDNO=$buildno OM_LINUXARCH="arm64" OM_BACKWARDCOMPAT="arm64"
make startreport









