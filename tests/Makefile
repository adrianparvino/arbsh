CFLAGS += -Wall -Wextra 

all:

	cd ../libc && test -e libgc.a || $(MAKE) static

	$(CC) ctype-driver.c -o ctype-driver ../libc/libgc.a
	$(CC) stdio-driver.c -o stdio-driver ../libc/libgc.a -lm

clean:

	$(RM) ctype-driver
	$(RM) stdio-driver
