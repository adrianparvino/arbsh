prog1="./tests/division-test"

$prog1 $1 $2 $3 $4 

# obase must come before ibase !!

echo "have  bc  divide and then check its work, This won't be correct in bases other than 10"

echo "scale=$4;obase=${3};ibase=${3};$1/$2;a=($1/$2);$2*a" | bc -l

