CFLAGS := -Wall -Wextra -c
LDFLAGS := -lm
CC := gcc
OBJ = $(shell for i in */*.c ; do echo $${i%.c}.o ; done )
AR := ar

LIBNAME = gc

STATLIB = lib$(LIBNAME).a

DYNLIB = lib$(LIBNAME).so


all: 
	$(MAKE) static
	$(MAKE) cleanobj
	$(MAKE) dynamic


static: $(OBJ)

	$(MAKE) static_link
	$(MAKE) static_create


dynflags:

	$(eval CC=$(CC) -fpic)

	
dynamic: dynflags $(OBJ) 

	$(MAKE) dynamic_link
	$(MAKE) dynamic_create 


static_link:

	$(AR) -cvq $(STATLIB) $(OBJ)


dynamic_link:

	$(CC) -shared -Wl,-soname,libgc.so -o $(DYNLIB) $(OBJ)


static_create: 

	$(CC) -o static_driver driver.c $(STATLIB) $(LDFLAGS)


dynamic_create:

	$(CC) driver.c -L. -l$(LIBNAME) -o dynamic_driver $(LDFLAGS)


exec_dyn:

	LD_LIBRARY_PATH=. ./dynamic_driver

cleanobj:

	$(RM) $(OBJ) 

clean:
	$(MAKE) cleanobj
	$(RM) $(DYNLIB) 
	$(RM) $(STATLIB) 
	$(RM) *driver
