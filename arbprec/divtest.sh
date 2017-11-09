prog=bc
echo "division:"
echo "$1   $2"
./toym $1 "/" $2 $3 $4
echo "obase=$3;ibase=$3;scale=$4; $1 / $2" | $prog -l











