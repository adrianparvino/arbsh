#!/bin/sh


dmesg | tail -n 10 1> testfile1
./dmesg | tail -n 10 1> testfile2 
diff testfile1 testfile2 && echo "$0 test one complete" 
rm testfile1 testfile2


dmesg | tail -n 30 1> testfile1
./dmesg | tail -n 30 1> testfile2
diff testfile1 testfile2 && echo "$0 test two complete" 
rm testfile1 testfile2

dmesg | tail -n 50 1> testfile1
./dmesg | tail -n 50 1> testfile2
diff testfile1 testfile2 && echo "$0 test two complete" 
rm testfile1 testfile2



