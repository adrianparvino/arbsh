#!/bin/sh


shellstat()
{

	FILE="$1"

	WHOAMI=$(whoami)

	printf "..."
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

	printf "..."

	if [ -G "$FILE" ]
	then printf " $WHOAMI :"
	else printf " ....... :"
	fi

	if [ -O "$FILE" ]
	then printf " $WHOAMI "
	else printf " ....... "
	fi
	printf " $1\n"

}

LONGLIST="0"
ARGSTRING=""
DEEP="0"

for i in $@
do	case "$i" in
	-l) LONGLIST="1"
	shift
	;;
	-R) DEEP="1"
	shift
	;;
	*) ARGSTRING="${ARGSTRING} ${i}"
	;;
	esac
done


LINES=$(tput lines)
ROWS=$(tput cols)

WORKD="."

if [ "$#" -gt "0" ]
then	WORKD="$ARGSTRING"
fi



STARS="${WORKD}/*"

if [ "$DEEP" = "1" ]
then	STARS="${WORKD}/* ${WORKD}/*/* ${WORKD}/*/*/* ${WORKD}/*/*/*/* "
fi

CYCLE="0" 
LINED="" 
LILEN="0" 
C="0" 
N="0" 
LEN="0" 
TLEN="0"

for i in $STARS 
do	TLEN="${#i}"
	[ -e "$i" ] || continue
	if [ "$TLEN" -gt "$LEN" ]
	then	LEN="${TLEN}"
	fi
	eval ARRAY_"$C"="$i"

	N=$(( $N + 1))
	C=$(( $C + 1 ))
done 

# sorting
#C="1"
#while [ "$C" -lt "$N" ]
#do D="$C" 
#while [ "$D" -gt "0" -a \
#"$( eval printf '$'ARRAY_$D )" -lt \
#"$( eval printf '$'ARRAY_$(( $D - 1 )) )" ]
#do 
#HOLD="$( eval printf '$'ARRAY_$D )" 
#eval ARRAY_"$D"="$( eval printf '$'ARRAY_$(( $D - 1 )) )" 
#eval ARRAY_$(( $D - 1 ))="$HOLD"
#D=$(( $D - 1 ))
#done 
#C=$(( $C + 1 ))
#done 
  
# screen width calculations
C="1"
if [ $LEN -lt $ROWS ]
then	NUMIT=$(($ROWS / $LEN))
else	NUMIT="1"
fi

# print
while [ "$C" -lt "$N" ]
do	if [ $LONGLIST -ne "0" ]
	then	shellstat "$( eval printf '$'ARRAY_$C )"
	else	printf "%-*s " "$LEN" "$( eval printf '$'ARRAY_$C )"
	
		if [ $(( $C % $NUMIT )) = "0" ]
		then	printf "\n"
		fi
	fi
	C=$(( C + 1 )) 
done

printf "\n"
