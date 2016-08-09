gcc -Wall -c cat.c


gcc -Wall -c date.c


ar -cvq libutils.a date.o cat.o


gcc -o main main.c libutils.a


gcc -o main main.c -L. -lutils




