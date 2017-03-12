CFLAGS := -Wall -Wextra -I./include/

LDFLAGS := 

CC := gcc

OBJ = $(shell for i in arb_str_math/*.c ; do echo $${i%.c}.o ; done )

AR := ar

LIBNAME = arbstr

STATLIB = lib$(LIBNAME).a

DYNLIB = lib$(LIBNAME).so

DYNCC = CC="$(CC) -fpic"

DESTDIR := ../

.PHONY: uninstall

INCLUDES =  $(shell for i in include/*.h ; do echo $$i ; done )

INCLUDES_TARG =  $(shell for i in include/*.h ; do echo $(DESTDIR)/$$i ; done )


all:

	$(MAKE) static
	#$(MAKE) cleanobj
	#$(MAKE) dynamic


static: $(OBJ)

	$(MAKE) static_link
	$(MAKE) static_create



dynwrap: $(OBJ)


dynamic: 

	$(MAKE) $(DYNCC) dynwrap
	$(MAKE) dynamic_link
	#$(MAKE) dynamic_create



static_link:

	$(AR) -cvq $(STATLIB) $(OBJ)


dynamic_link:

	$(CC) -shared -Wl,-soname,$(DYNLIB) -o $(DYNLIB) $(OBJ)


static_create: 

	$(CC) -o stringmath tests/stringmath.c $(STATLIB) $(LDFLAGS) $(CFLAGS)
	





dynamic_create:

	$(CC) tests/driver.c -L. -l$(LIBNAME) -o dynamic_driver $(LDFLAGS) $(CFLAGS)


exec_dyn:

	LD_LIBRARY_PATH=. ./dynamic_driver

cleanobj:

	$(RM) $(OBJ) 

clean:
	$(MAKE) cleanobj
	$(RM) $(DYNLIB) 
	$(RM) $(STATLIB) 
	$(RM) *driver stringmath

install:

	mkdir -p $(DESTDIR)/lib/
	mkdir -p $(DESTDIR)/include/
	cp $(STATLIB) $(DESTDIR)/lib/
	cp $(DYNLIB) $(DESTDIR)/lib/
	cp $(INCLUDES) $(DESTDIR)/include/

	echo "#!/bin/sh" > uninstall
	echo "set -x" >> uninstall
	echo "rm $(INCLUDES_TARG)" >> uninstall
	echo "rm $(DESTDIR)/lib/$(STATLIB)" >> uninstall
	echo "rm $(DESTDIR)/lib/$(DYNLIB)" >> uninstall

	
uninstall:

	chmod +x uninstall
	./uninstall
	rm uninstall
