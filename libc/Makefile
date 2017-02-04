CFLAGS := -Wall -Wextra -c
LDFLAGS := -lm
CC := gcc
OBJ = $(shell for i in */*.c ; do echo $${i%.c}.o ; done )
AR := ar


all: $(OBJ)
	
	$(MAKE) static_link
	$(MAKE) static_create


dynflags:

	$(eval CC=$(CC) -fpic)
	
dynamic: dynflags $(OBJ)

	$(MAKE) dynamic_link
	$(MAKE) dynamic_create 

static_link:

	$(AR) -cvq libgc.a $(OBJ)

dynamic_link:

	$(CC) -shared -Wl,-soname,libgc.so -o libgc.so */*.o

static_create: 

	$(CC) -o static_driver driver.c libgc.a $(LDFLAGS)

dynamic_create:

	$(CC) driver.c -L. -lgc -o dynamic_driver $(LDFLAGS)

exec_dyn:

	LD_LIBRARY_PATH=. ./dynamic_driver

clean:

	$(RM) *.a *_driver *.so log */*.o
