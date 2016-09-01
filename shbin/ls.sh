#!/bin/sh

LINES=$(tput lines)
ROWS=$(tput cols)

WHOAMI=$(whoami)

shellstat()
{ 
	FILE="$1"
	BOOL="0"
	[ -h "$FILE" -a "$BOOL" = "0" ] && printf "l" && BOOL="1"
	[ -b "$FILE" -a "$BOOL" = "0" ] && printf "b" && BOOL="1"
	[ -c "$FILE" -a "$BOOL" = "0" ] && printf "c" && BOOL="1"
	[ "$BOOL" = "0" ] && printf "-"
	
	printf "..."
	[ -r "$FILE" ] && printf "r" || printf "-"
	[ -w "$FILE" ] && printf "w" || printf "-"
	[ -x "$FILE" ] && printf "x" || printf "-"
	printf "..."
	[ -G "$FILE" ] && printf " $WHOAMI :" || printf " ....... :"
	[ -O "$FILE" ] && printf " $WHOAMI " || printf " ....... "
	printf " $1\n"
}

# Argument parsing
LONGLIST="0"
ARGSTRING=""
DEEP="0"
HIDDEN="0"

for i in $@
do	case "$i" in
	-l)	LONGLIST="1"
		shift
		;;
	-R)	DEEP="1"
		shift
		;;
	-a)	HIDDEN="1"
		shift
		;;
	*)	ARGSTRING="${ARGSTRING} ${i}"
		;;
	esac
done


# Default to printing the current working directory
WORKD="."
if [ "$#" -gt "0" ]
then	WORKD="$ARGSTRING"
fi

# Determine depth and whether to printy hidden files
HSTARS=""
STARS="${WORKD}/*"
if [ "$HIDDEN" = "0" ]
then	STARS="${WORKD}/*"
else	HSTARS="${WORKD}/.*"
fi

if [ "$DEEP" = "1" ]
then	if [ "$HIDDEN" = "0" ]
	then	STARS="${WORKD}/* ${WORKD}/*/* ${WORKD}/*/*/* ${WORKD}/*/*/*/* "
	else	HSTARS="${WORKD}/.* ${WORKD}/.*/.* ${WORKD}/.*/.*/.* ${WORKD}/.*/.*/.*/.* "
	fi
fi


# Directory walk
N="1" 
LEN="0" 
TLEN="0"
for i in $STARS $HSTARS
do	TLEN="${#i}"
	[ -e "$i" ] || continue
	[ "$TLEN" -gt "$LEN" ] && LEN="${TLEN}"
	
	eval ARRAY_"$N"="$i"
	eval OARRAY_"$N"="......"

	N=$(( $N + 1))
done 

  
# screen width calculations
if [ "$LEN" -lt "$ROWS" ]
then	NUMIT=$(($ROWS / $LEN))
else	NUMIT="1"
fi


# shuffle 
cnt="1"
sft="1"
sftc="1"
vary="1"



while [ "$cnt" -lt "$N" ]
do	#eval OARRAY_"$sft"="$( eval printf '$'ARRAY_$cnt )"
	eval OARRAY_"$cnt"="$( eval printf '$'ARRAY_$cnt )"
	sft=$(($sft + $NUMIT ))
	
	if [ $sftc = $((($N / $NUMIT) + 1)) ]
	then	vary=$(( $vary + 1 ))
		sft=$vary
		sftc="0"
	fi
	sftc=$(($sftc + 1))
	
	cnt=$(( $cnt + 1 )) 
done

# print
C="1"
while [ "$C" -lt "$N" ]
do	if [ $LONGLIST -ne "0" ]
	then	shellstat "$( eval printf '$'OARRAY_$C )"
	else	printf "%-*s " "$LEN" "$( eval printf '$'OARRAY_$C )"
		if [ $((($C % $NUMIT) + 1)) = "1" ]
		then	printf "\n"
		fi
	fi
	C=$(( $C + 1 )) 
done
printf "\n"

