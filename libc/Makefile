CFLAGS = -Wall -Wextra
LDFLAGS = -lm

CC = gcc

all:

	$(MAKE) static_obj
	$(MAKE) static_link
	$(MAKE) static_create


dynamic:

	$(MAKE) dynamic_obj
	$(MAKE) dynamic_link
	$(MAKE) dynamic_create


static_obj:

	$(CC) -c stdlib/*.c $(LDFLAGS)
	$(CC) -c */*.c $(LDFLAGS)


static_link:

	ar -cvq libgc.a *.o 


static_create:

	$(CC) -o static_driver driver.c libgc.a $(LDFLAGS)


clean:

	$(RM) *.o libgc.a static_driver dynamic_driver libgc.so a.out log


dynamic_obj:

	$(CC) -c -fpic */*.c $(LDFLAGS)


dynamic_link:

	$(CC) -shared -Wl,-soname,libgc.so -o libgc.so *.o


dynamic_create:

	$(CC) driver.c -L. -lgc -o dynamic_driver $(LDFLAGS)

exec_dyn:

	LD_LIBRARY_PATH=. ./dynamic_driver blankvar


