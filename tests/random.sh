#!/bin/sh

COUNT=0
while [ "$COUNT" -lt 100 ]
do	COUNT=$((COUNT +1))
	./tests/rand-div-test 2> some.bc > log
	bc -lq some.bc > log2
	if diff log log2
	then	printf "%s\n" "passed"
	else	exit 1
		printf "Test failed! look inside of 'some.bc' to reveal the failing numbers!\n"
	fi
	sleep 1
done
