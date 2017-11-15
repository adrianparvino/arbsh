

#extra="valgrind"
extra="time"
#extra=""

rm log log2

./control/tests/division-test $1 $2 $3 $4 >log

#$extra ./tests/2division $1 $2 $3 $4> log2
./tests/algd $1 $2 $3 $4> log2

if diff log log2 
then 	if [ -s log -a -s log2 ]
	then	printf "%s\n" "control files are equal and non empty."
	else	printf "%s\n" "control files ere equal, but empty. something went wrong!"
	fi
else	printf "%s\n" "The diff failed!"
fi

