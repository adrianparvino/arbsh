#!/bin/sh

#make all 

# test one
echo
echo "populating with random data .. "
echo
dd if=/dev/urandom of=testfile1 bs=1M count=10 2>/dev/null
echo 
./cat testfile1 > testfile2 
diff testfile1 testfile2 && echo "$0 first test successful"
rm testfile1 testfile2 


# test 2
echo
echo "populating with random data .. "
echo
dd if=/dev/urandom of=testfile1 bs=1M count=100 2>/dev/null
echo 
./cat testfile1 > testfile2 
diff testfile1 testfile2 && echo "$0 second test successful"
rm testfile1 testfile2 


# test 3
echo
echo "populating with random data .. "
echo
dd if=/dev/urandom of=testfile1 bs=1M count=1000 2>/dev/null
echo 
./cat testfile1 > testfile2 
diff testfile1 testfile2 && echo "$0 third test successful"
rm testfile1 testfile2





