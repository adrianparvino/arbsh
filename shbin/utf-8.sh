i=200
while [ "$i" -lt 207  ]
do 	i=$((i + 1))
	busybox printf "\342\\${i}\240"
done
