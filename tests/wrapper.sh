#!/bin/sh

num1=$2
num2=$3
scale=$5
spec=0


if [ $1 = "ag-add" ]
then	operator="+"
	spec=1
fi
if [ $1 = "ag-sub" ]
then	operator="-"
	spec=1
fi
if [ $1 = "ag-mul" ]
then	operator="*"
	spec=1
fi
if [ $1 = "add" ]
then	operator="+"
fi
if [ $1 = "sub" ]
then	operator="-"
fi
if [ $1 = "mul" ]
then	operator="*"
fi
if [ $1 = "mul2" ]
then	operator="*"
	num2=$2
fi

if [ $1 = "exp" ]
then	operator="^"
fi

if [ $1 = "ag-div" ]
then	operator="/"
	spec=1
fi
if [ $1 = "div" ]
then	operator="/"
fi
if [ $1 = "karatsuba-mul" ]
then	operator="*"
	#scale=1000
fi

if [ $1 = "karatsuba-mul2" ]
then	operator="*"
	#scale=1000
fi
if [ $1 = "mod" ]
then	operator="%"
fi
if [ $1 = "exp" ]
then	operator="^"
fi
if [ $1 = "nsqrt" ]
then	# this test does not work yet
	./tests/$1 $2 $4 $5 > log1
	echo "scale=$5; sqrt($num1) " | bc -l > log2
	if ! diff log1 log2
	then    printf "test failed\n\n\nThe failing test was:\n"
		printf "%s\n" "./tests/$1 $2 $4 $5"
		printf "Continuing...\n"
	else	printf "passed\n"
	fi
	exit
fi
if [ $spec = "1" ]
then	./tests/$1 $2 $3 $4 $5 > log1
	echo "base=$4;scale=$scale;$num1 ${operator} $num1" | bc -l > log2
else

./tests/$1 $2 $3 $4 $5 > log1

echo "base=$4;scale=$scale;$num1 ${operator} $num2" | bc -l > log2
fi

if ! diff log1 log2
then	printf "test failed\n\n\nThe failing test was:\n"
	printf "%s\n" "./tests/$1 $1 $3 $4 $5"
	printf "Continuing...\n"
else	printf "passed\n"
fi

