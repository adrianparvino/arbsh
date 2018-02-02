#!/bin/sh

COUNT=0
while [ $((COUNT +1)) -lt 100 ]
do	./tests/rand-div-test 2> some.bc > log
	bc -lq some.bc > log2
	if diff log log2
	then	printf "%s\n" "passed"
	fi
	sleep 1
done
