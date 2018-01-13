./tests/mul $1 $2 $4 $3 > log1

echo "$1 * $2" | bc -l > log2

diff log1 log2
