time ./tests/division-test $1 $2 $3 $4 >log

time ./tests/2division $1 $2 $3 $4> log2

diff log log2


