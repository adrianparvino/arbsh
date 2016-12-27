#!/bin/sh


LINES=$(tput lines)
ROWS=$(tput cols)

WHOAMI=$(whoami)

. ../libsh/libsh

# Argument parsing
LONGLIST="0"
ARGS=""
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
	*)	ARGS="${ARGS} ${i}"
		;;
	esac
done


# Default to printing the current working directory
WORKD="."
if [ "$#" -gt "0" ]
then	WORKD="$ARGS"
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
N="0" 
LEN="0" 
TLEN="0"
for i in $STARS $HSTARS
do	TLEN="${#i}"
	[ -e "$i" ] || continue
	# Save longest line length
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
cnt="0"
sft="0"
sftc="0"
vary="0"

while [ "$cnt" -lt "$N" ]
do	#eval OARRAY_"$sft"="$( eval printf '$'ARRAY_$cnt )"
	eval OARRAY_"$cnt"="$( eval printf '$'ARRAY_$cnt )"
	sft=$(($sft + $NUMIT ))
	sftc=$(($sftc + 1))
	cnt=$(( $cnt + 1 )) 
	if [ $sftc = $((($N / $NUMIT) + 1)) ]
	then	vary=$(( $vary + 1 ))
		sft=$vary
		sftc="0"
	fi
done

# print
C="0"
while [ "$C" -lt "$N" ]
do	if [ $LONGLIST -ne "0" ]
	then	shellstat "$( eval printf '$'OARRAY_$C )"
	else	if [ $((($C % $NUMIT))) = "0"  -a "$C" != "0" ]
		then	printf "\n"
		fi 
		printf "%-*s " "$LEN" "$( eval printf '$'OARRAY_$C )"
	fi
	C=$(( $C + 1 )) 
done
printf "\n"



