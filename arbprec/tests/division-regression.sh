./tests/division-test $1 $2 $3 $4 >log

./tests/2division $1 $2 $3 $4> log2

diff log log2

if [ -s log -a -s log2 ]
then	echo "control files are equal and non empty"
else	echo "control files ere empty, something went wrong"
fi
