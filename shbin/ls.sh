#!/bin/sh

LINES=$(tput lines)
ROWS=$(tput cols)
WHOAMI=$(whoami)

shellstat()
{ 
	FILE="$1"
	printf "..."
	if [ -r "$FILE" ]
	then	printf "r"
	else	printf "-"
	fi 
	if [ -w "$FILE" ]
	then	printf "w"
	else	printf "-"
	fi 
	if [ -x "$FILE" ]
	then	printf "x"
	else	printf "-"
	fi
	printf "..."
	if [ -G "$FILE" ]
	then	printf " $WHOAMI :"
	else	printf " ....... :"
	fi
	if [ -O "$FILE" ]
	then	printf " $WHOAMI "
	else	printf " ....... "
	fi
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

N="1" 
LEN="0" 
TLEN="0"

for i in $STARS $HSTARS
do	TLEN="${#i}"
	[ -e "$i" ] || continue
	if [ "$TLEN" -gt "$LEN" ]
	then	LEN="${TLEN}"
	fi
	eval ARRAY_"$N"="$i"
	eval OARRAY_"$N"="......"

	N=$(( $N + 1))
done 

  
# screen width calculations
C="0"
NUMIT=$(($ROWS / $LEN))
#if [ "$LEN" -lt "$ROWS" ]
#then	
#else	NUMIT="1"
#fi


cnt="1"
sft="1"
sftc="1"
vary="1"

# shuffle
while [ "$cnt" -lt "$N" ]
do	eval OARRAY_"$sft"="$( eval printf '$'ARRAY_$cnt )"
	#eval OARRAY_"$cnt"="$( eval printf '$'ARRAY_$cnt )"
	sft=$(($sft + $NUMIT ))
	sftc=$(($sftc + 1))
	if [ $sftc = $(($(( $N / $NUMIT)) + 1)) ]
	then	vary=$(( $vary + 1 ))
		sft=$vary
		
		sftc="0"
	fi
	
	cnt=$(( $cnt + 1 )) 
done

# print
C="1"
while [ "$C" -lt "$N" ]
do	if [ $LONGLIST -ne "0" ]
	then	shellstat "$( eval printf '$'OARRAY_$C )"
	else	printf "%-*s " "$LEN" "$( eval printf '$'OARRAY_$C )"
		if [ $(($C % $NUMIT)) = "0" ]
		then	printf "\n"
		fi
	fi
	C=$(( $C + 1 )) 
done
printf "\n"

