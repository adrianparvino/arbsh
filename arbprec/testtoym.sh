prog1="time ./toym"

prog2="time bc"

$prog1 $1 "/" $2 $3 $4

echo "ibase=$3; obase=$3; scale=$4; $1 + $2" | time bc -l


