CFLAGS = -Wall

DIR = :=

all:

	$(MAKE) build
	$(MAKE) archive
	$(MAKE) create

build:
	#gcc -c ctype/*.c
	#gcc -c libgen/*.c
	gcc -c string/*.c
	#gcc -c stdlib/*.c


archive:
	ar -cvq libc.a *.o

create:
	gcc -o driver driver.c libc.a -static 

clean:
	rm -rf *.o libc.a driver

