CFLAGS := -Wall -Wextra -I./include/

LDFLAGS := 

CC := gcc

OBJ = $(shell for i in src/*.c ; do echo $${i%.c}.o ; done )

AR := ar

LIBNAME = arbprec

STATLIB = lib$(LIBNAME).a

DYNLIB = lib$(LIBNAME).so

DYNCC = CC="$(CC) -fpic"

DESTDIR := ../

.PHONY: uninstall

PREFIX = /arbprec/

INCLUDES =  $(shell for i in include/$(PREFIX)/*.h ; do echo $$i ; done )

INCLUDES_TARG =  $(shell for i in include/$(PREFIX)/*.h ; do echo $(DESTDIR)/$$i ; done )

all:

	$(MAKE) static
	$(MAKE) cleanobj
	$(MAKE) dynamic

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

	$(CC) -o arbprec tests/arbprec-driver.c $(STATLIB) $(LDFLAGS) $(CFLAGS)

dynamic_create:

	$(CC) tests/stringmath.c -L. -l$(LIBNAME) -o dynamic_stringmath $(LDFLAGS) $(CFLAGS)

exec_dyn:

	LD_LIBRARY_PATH=. ./dynamic_stringmath

cleanobj:

	$(RM) $(OBJ) 

clean:
	$(MAKE) cleanobj
	$(RM) $(DYNLIB) 
	$(RM) $(STATLIB) 
	$(RM) *driver static_stringmath dynamic_stringmath arbprec

install:

	mkdir -p $(DESTDIR)/lib/
	mkdir -p $(DESTDIR)/include/$(PREFIX)
	cp $(STATLIB) $(DESTDIR)/lib/
	cp $(DYNLIB) $(DESTDIR)/lib/
	cp $(INCLUDES) $(DESTDIR)/include/$(PREFIX)
	$(MAKE) create_uninstall

create_uninstall:

	echo "#!/bin/sh" > uninstall
	echo "set -x" >> uninstall
	echo "rm $(INCLUDES_TARG)" >> uninstall
	echo "rm $(DESTDIR)/lib/$(STATLIB)" >> uninstall
	echo "rm $(DESTDIR)/lib/$(DYNLIB)" >> uninstall
	
uninstall:

	chmod +x uninstall
	./uninstall
	rm uninstall
