./tests/2division $1 $2 $3 $4

printf "%s\n" "scale=$4;obase=$3;ibase=$3; $1 / $2 " | bc -l
