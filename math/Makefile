CC = gcc 
CFLAGS = -Wall -Wextra -lm -O0

all:

	$(CC) testmath.c -o testmath $(CFLAGS)
	$(CC) multiplication.c -o multiplication $(CFLAGS)
	$(CC) stringmath.c -o stringmath $(CFLAGS)
	$(CC) astronomy_calculator.c -o astcalc $(CFLAGS)
	$(CC) bigintmath.c -o bigintmath $(CFLAGS)


clean:

	$(RM) testmath multiplication stringmath astcalc bigintmath


install:

	cp -a testmath multiplication stringmath astcalc bigintmath $(DESTDIR)/bin/



