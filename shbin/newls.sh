#!/bin/sh


# (C) 2014, MIT license, "insertion_sort.sh" 

LINES=$(tput lines)
ROWS=$(tput cols)

insertion_sort()
{
	C="0" 
	N="$#"

	for i in $@
	do 	eval ARRAY_"$C"="$i" 
		C=$(( $C + 1 ))
	done 

	C="1" 

	while [ "$C" -lt "$N" ]
	do 	D="$C" 
		while [ "$D" -gt "0" -a \
		"$( eval printf '$'ARRAY_$D )" -lt \
		"$( eval printf '$'ARRAY_$(( $D - 1 )) )" ]
		do 
			HOLD="$( eval printf '$'ARRAY_$D )" 
			eval ARRAY_"$D"="$( eval printf '$'ARRAY_$(( $D - 1 )) )" 
			eval ARRAY_$(( $D - 1 ))="$HOLD"
			D=$(( $D - 1 ))
		done 
		C=$(( $C + 1 ))
	done 
  
	C="0" 

	while [ "$C" -lt "$N" ]
	do 	printf "%s\n"  "$( eval printf '$'ARRAY_$C )" 
		C=$(( C + 1 )) 
	done

}
#insertion_sort $@ 



# A simple implementation of ls in POSIX compatible shell 

WORKD="."

STARS="/*"

CYCLE="0"

LINED=""

LILEN="0"

#for i in ${WORKD}/$STARS
#do	LINED="${LINED}    ${i}"
	
	
#done

#printf "%s" "$LINED"



	C="0" 
	#N="$#"
	N="0"
	LEN="0"
	TLEN="0"

	#for i in $@
	for i in ${WORKD}/$STARS
	do 	TLEN="${#i}"
		if [ "$TLEN" -gt "$LEN" ]
		then	LEN="${TLEN}"
		fi
		eval ARRAY_"$C"="$i"
		
		N=$((N + 1))
		C=$(( $C + 1 ))
	done 

	#C="1" 

	#while [ "$C" -lt "$N" ]
	#do 	D="$C" 
	#	while [ "$D" -gt "0" -a \
	#	"$( eval printf '$'ARRAY_$D )" -lt \
	#	"$( eval printf '$'ARRAY_$(( $D - 1 )) )" ]
	#	do 
	#		HOLD="$( eval printf '$'ARRAY_$D )" 
	#		eval ARRAY_"$D"="$( eval printf '$'ARRAY_$(( $D - 1 )) )" 
	#		eval ARRAY_$(( $D - 1 ))="$HOLD"
	#		D=$(( $D - 1 ))
	#	done 
	#	C=$(( $C + 1 ))
	#done 
  
	C="1"
	NUMIT=$(( $ROWS / $LEN))
	#echo $NUMIT
	#exit
	while [ "$C" -lt "$N" ]
	do 	printf "%-*s " "$LEN" "$( eval printf '$'ARRAY_$C )"
		if [ $(( $C % $NUMIT )) = "1" ]
		then	printf "\n"
		fi
		C=$(( C + 1 )) 
	done
	printf "\n"
