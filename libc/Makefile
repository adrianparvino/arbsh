CFLAGS = -Wall -Wextra

all:

	$(MAKE) build
	$(MAKE) archive
	$(MAKE) create


dynamic:

	$(MAKE) dynobj
	$(MAKE) dynlink
	$(MAKE) dyncreate


build:

	gcc -c */*.c 


archive:

	ar -cvq libc.a *.o 


create:

	gcc -o driver driver.c libc.a -lm


clean:

	rm -rf *.o libc.a driver dynamic_driver libcoo.so


dynobj:

	gcc -c -fpic */*.c


dynlink:

	gcc -shared -Wl,-soname,libcoo.so -o libcoo.so *.o


dyncreate:

	gcc driver.c -L. -lcoo -o dynamic_driver -lm

exec_dyn:

	LD_LIBRARY_PATH=. ./dynamic_driver blankvar


