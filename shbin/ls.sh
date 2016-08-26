#!/bin/sh
statfile()
{
	stat --printf "%A  %U  %n  \n" "$1"
}
LINES=$(tput lines)
ROWS=$(tput cols)

WORKD="."

if [ $# -gt 0 ]
then	WORKD="$@"
fi

STARS="${WORKD}/* ${WORKD}/*/* ${WORKD}/*/*/* "

CYCLE="0"

LINED=""

LILEN="0"

#printf "%s" "$LINED"

C="0"

#N="$#"

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

	N=$((N + 1))
	C=$(( $C + 1 ))
done 

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
  
C="1"
if [ $LEN -lt $ROWS ]
then	NUMIT=$(( $ROWS / $LEN))
else	NUMIT="1"
fi

while [ "$C" -lt "$N" ]
do	#printf "%-*s " "$LEN" "$( eval printf '$'ARRAY_$C )"
	statfile "$( eval printf '$'ARRAY_$C )"
	if [ $(( $C % $NUMIT )) = "0" ]
	then	printf "\n"
	fi
	C=$(( C + 1 )) 
done

printf "\n"
