CFLAGS := -I./include/ -Wall -Wextra

LDFLAGS := 

CC := gcc

OBJ = $(shell for i in src/*/*.c ; do echo $${i%.c}.o ; done )

AR := ar

LIBNAME = ccc

STATLIB = lib$(LIBNAME).a

DYNLIB = lib$(LIBNAME).so

DYNCC = CC="$(CC) -fpic"


all:

	$(MAKE) static
	#$(MAKE) cleanobj
	#$(MAKE) dynamic


static: $(OBJ)

	$(MAKE) static_link



dynwrap: $(OBJ)

	
dynamic: 

	$(MAKE) $(DYNCC) dynwrap
	$(MAKE) dynamic_link



static_link:

	$(AR) -cvq $(STATLIB) $(OBJ)


dynamic_link:

	$(CC) -shared -Wl,-soname,$(DYNLIB) -o $(DYNLIB) $(OBJ)


static_create: 

	$(CC) -o static_driver ../tests/driver.c $(STATLIB) $(LDFLAGS)


dynamic_create:

	$(CC) ../tests/driver.c -L. -l$(LIBNAME) -o dynamic_driver $(LDFLAGS)


exec_dyn:

	LD_LIBRARY_PATH=. ./dynamic_driver

cleanobj:

	$(RM) $(OBJ) 

clean:
	$(MAKE) cleanobj
	$(RM) $(DYNLIB) 
	$(RM) $(STATLIB) 
	$(RM) *driver log stringmath

