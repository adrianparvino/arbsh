if [ $# -lt 1 ]
then	printf "%s\n" "Usage $0 [mul|div|sub|add|mul2|karatsuba-mul]"
	exit
fi

./tests/wrapper.sh ${1} 3 3 10 10

./tests/wrapper.sh ${1} 12123786 123 10 10

./tests/wrapper.sh ${1} 123876 1278 10 10

./tests/wrapper.sh ${1} 12398 127 10 10

./tests/wrapper.sh ${1} 12371623 10 10 10

./tests/wrapper.sh ${1} 1298712 10 10 12736

./tests/wrapper.sh ${1} 12376 123 10 178

./tests/wrapper.sh ${1} 127836 61 10 10

./tests/wrapper.sh ${1} 2138 123 10 10

./tests/wrapper.sh ${1} 128 12 10 10

./tests/wrapper.sh ${1} 671823 36 10 10






