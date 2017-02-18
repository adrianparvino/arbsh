#!/bin/sh

# quickly make a chroot using ldd



[ "$#" -lt 2 ] && { echo "Usage $0 /path/tool mychroot" ; exit ; }

set -xe

. ../libsh/libsh

lddwrapsh $@
