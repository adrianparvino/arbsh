#./toym $1 $2
#echo "bc control"
prog=bc
echo "multiplication:"
./toym $1 "*" $2 $3 $4
echo "obase=$3;ibase=$3;scale=$4; $1 * $2" | $prog -l
echo "division:"
./toym $1 "/" $2 $3 $4
echo "obase=$3;ibase=$3;scale=$4; $1 / $2" | $prog -l
#echo "scale=100; $1 + $2" | bc -l
echo "addition:"
./toym $1 "+" $2 $3 $4
echo "obase=$3;ibase=$3;scale=$4; $1 + $2" | $prog -l
echo "subtraction:"
./toym $1 "-" $2  $3 $4
#echo "scale=100; $1 - $2" | bc -l
echo "obase=$3;ibase=$3;scale=$4; $1 - $2" | $prog -l
echo "sqrt:"
echo "obase=$3;ibase=$3;scale=$4; sqrt($1)" | $prog -l

