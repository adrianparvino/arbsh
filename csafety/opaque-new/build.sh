
set -x

gcc -c opaque.c -o opaque.o

gcc main-driver.c opaque.o -o main-driver



