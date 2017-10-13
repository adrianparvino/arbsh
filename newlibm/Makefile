CFLAGS := -I./include/ -Wall -Wextra -static
#CFLAGS := -Wall -Wextra -static

LDFLAGS := 

CC := gcc

OBJ = $(shell for i in src/*.c ; do echo $${i%.c}.o ; done )

AR := ar

LIBNAME = m

STATLIB = lib$(LIBNAME).a

DYNLIB = lib$(LIBNAME).so

DYNCC = CC="$(CC) -fpic"

DESTDIR := ../

.PHONY: uninstall

INCLUDES =  $(shell for i in include/*.h ; do echo $$i ; done )

INCLUDES_TARG =  $(shell for i in include/*.h ; do echo $(DESTDIR)/$$i ; done )

TEST_OBJ = $(shell for i in tests/*.c ; do echo $${i%.c} ; done )

LDLIBS = -L. -lm

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


static_create: $(TEST_OBJ)

dynamic_create: $(TEST_OBJ)

exec_dyn:

	LD_LIBRARY_PATH=. ./tests/driver

cleanobj:

	$(RM) $(OBJ) 

clean:
	$(MAKE) cleanobj
	$(RM) $(DYNLIB)
	$(RM) $(STATLIB)
	$(RM) $(TEST_OBJ) uninstall

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
