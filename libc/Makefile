CFLAGS = -Wall

DIR = :=

all:

	$(MAKE) build
	$(MAKE) archive
	$(MAKE) create

build:
	gcc -c ctype/*.c
	gcc -c libgen/*.c
	gcc -c string/*.c
	gcc -c stdlib/*.c
	gcc -c unistd/*.c


archive:
	ar -cvq libc.a *.o



create:
	gcc -o driver driver.c libc.a

clean:
	rm -rf *.o libc.a driver

dynbuild:

	gcc -c -fpic ctype/*.c
	gcc -c -fpic libgen/*.c
	gcc -c -fpic string/*.c
	gcc -c -fpic stdlib/*.c
	gcc -c -fpic unistd/*.c

dynlink:

	gcc -shared -Wl,-soname,libc.so.1 -o libc.so.1.0.1 *.o

dyncreate:
	gcc driver.c -o dynamic_driver -L. -lc
