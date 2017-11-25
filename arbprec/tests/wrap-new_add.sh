if [ $3 = "grind" ]
then	valgrind ./tests/new_add $1 $2 10
else	./tests/new_add $1 $2 10
fi

echo "$1 + $2" | bc -l

