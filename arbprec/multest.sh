prog="time bc"
echo "multiplication:"
time ./toym $1 "*" $2 $3 $4
echo "obase=$3;ibase=$3;scale=$4; $1 * $2" | $prog -l
