if [ $# -lt 1 ]
then	printf "%s\n" "Usage $0 [mul|div|sub|add|mul2|karatsuba-mul]"
	exit
fi

./tests/wrapper.sh ${1} 3 3 10 10






