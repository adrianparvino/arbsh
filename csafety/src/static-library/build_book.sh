#!/bin/sh


for i in dog.c frog.c swan.c animals.h main.c Makefile; do printf -- "%s:\n\n" "$i"; cat $i | sed 's|^|\t|g' ; done



