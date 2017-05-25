#!/bin/sh

buildno="1"

make OM_ARCH='i686' OM_LIBC='musl' BUILDNO=$buildno
make clean OM_ARCH='i686' OM_LIBC='musl' BUILDNO=$buildno
make OM_ARCH='x86_64' OM_LIBC='musl' BUILDNO=$buildno
make clean OM_ARCH='x86_64' OM_LIBC='musl' BUILDNO=$buildno
make OM_ARCH='aarch64' OM_LIBC='musl' BUILDNO=$buildno
make clean OM_ARCH='aarch64' OM_LIBC='musl' BUILDNO=$buildno

make OM_ARCH='i686' OM_LIBC='uclibc' BUILDNO=$buildno
make clean OM_ARCH='i686' OM_LIBC='uclibc' BUILDNO=$buildno
make OM_ARCH='x86_64' OM_LIBC='uclibc' BUILDNO=$buildno
make clean OM_ARCH='x86_64' OM_LIBC='uclibc' BUILDNO=$buildno
make OM_ARCH='aarch64' OM_LIBC='uclibc' BUILDNO=$buildno
make clean OM_ARCH='aarch64' OM_LIBC='uclibc' BUILDNO=$buildno

make OM_ARCH='i686' OM_LIBC='gnu' BUILDNO=$buildno
make clean OM_ARCH='i686' OM_LIBC='gnu' BUILDNO=$buildno
make OM_ARCH='x86_64' OM_LIBC='gnu' BUILDNO=$buildno
make clean OM_ARCH='x86_64' OM_LIBC='gnu' BUILDNO=$buildno
make OM_ARCH='aarch64' OM_LIBC='gnu' BUILDNO=$buildno
make clean OM_ARCH='aarch64' OM_LIBC='gnu' BUILDNO=$buildno
make finishreport

buildno=$((buildno + 1))







