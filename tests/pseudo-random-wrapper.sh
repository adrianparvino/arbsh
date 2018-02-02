#!/bin/sh

if [ $# != 1 ]
then	printf "Requires a test type, like 'div', 'add', 'sub' or 'mul'\n"
	exit 1
fi

COUNT=0
while [ "$COUNT" -lt 100 ]
do	COUNT=$((COUNT +1))
	./tests/pseudo-random-tests $1 2> some.bc > log
	bc -lq some.bc > log2
	if diff log log2
	then	printf "%s\n" "Giant pseudo-random number test passed."
	else	exit 1
		printf"%s\n"  "Test failed! look inside of 'some.bc' to reveal the failing numbers!"
	fi
	sleep 1
done
