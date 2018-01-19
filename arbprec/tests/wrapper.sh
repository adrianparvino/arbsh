if [ $1 = "add" ]
then operator="+"
fi
if [ $1 = "sub" ]
then operator="-"
fi
if [ $1 = "mul" ]
then operator="*"
fi
if [ $1 = "div" ]
then operator="/"
fi
if [ $1 = "karatsuba-mul" ]
then operator="*"
fi
if [ $1 = "mod" ]
then operator="%"
fi
./tests/$1 $2 $3 $4 $5 > log1

echo "base=$4;scale=$5;$2 ${operator} $3" | bc -l > log2

diff log1 log2
