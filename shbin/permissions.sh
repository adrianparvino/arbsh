#!/bin/sh

FILE="$1"



if [ -r "$FILE" ]
then printf "r"
else printf "-"
fi 

if [ -w "$FILE" ]
then printf "w"
else printf "-"
fi 

if [ -x "$FILE" ]
then printf "x"
else printf "-"
fi

if [ -G "$FILE" ]
then printf " current group "
else printf " foreign group "
fi

if [ -O "$FILE" ]
then printf " current user "
else printf " foreign user "
fi
printf " "

printf "\n"

