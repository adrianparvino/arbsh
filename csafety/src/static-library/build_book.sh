#!/bin/sh


for i in Makefile dog.c frog.c swan.c; do printf -- "%s:\n\n" "$i"; cat $i | sed 's|^|\t|g' ; done



