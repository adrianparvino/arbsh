CFLAGS += -Wall -Wextra -I./include/

OBJ = $(shell for i in src/*.c ; do echo $${i%.c}.o ; done )

LIBNAME = arbprec

STATLIB = lib$(LIBNAME).a

DYNCC = CC="$(CC) -fpic"

DESTDIR ?= ../

.PHONY: uninstall

PREFIX ?= /arbprec/

INCLUDES = $(shell for i in include/$(PREFIX)/*.h ; do echo $$i ; done )

INCLUDES_TARG = $(shell for i in include/$(PREFIX)/*.h ; do echo $(DESTDIR)/$$i ; done )

TEST_OBJ = $(shell for i in tests/*.c ; do echo $${i%.c} ; done )

LDLIBS += -L. -l$(LIBNAME)

all:

	$(MAKE) static
	$(MAKE) create_test

static: $(OBJ)

	$(MAKE) static_link

static_link:

	$(AR) -cvq $(STATLIB) $(OBJ)


create_test: $(TEST_OBJ)

cleanobj:

	$(RM) $(OBJ) 

clean:
	$(MAKE) cleanobj
	$(MAKE) -C control clean
	$(RM) $(DYNLIB) 
	$(RM) $(STATLIB) 
	$(RM) $(TEST_OBJ)
	$(RM) uninstall
	$(RM) log log2
	

install:

	mkdir -p $(DESTDIR)/lib/
	mkdir -p $(DESTDIR)/include/$(PREFIX)
	cp $(STATLIB) $(DESTDIR)/lib/
	cp $(INCLUDES) $(DESTDIR)/include/$(PREFIX)
	$(MAKE) create_uninstall

create_uninstall:

	echo "#!/bin/sh" > uninstall
	echo "set -x" >> uninstall
	echo "rm $(INCLUDES_TARG)" >> uninstall
	echo "rm $(DESTDIR)/lib/$(STATLIB)" >> uninstall

test:

	-$(MAKE) clean
	-$(MAKE) 
	-CFLAGS="" $(MAKE) -C control clean
	-CFLAGS="" $(MAKE) -C control
	-./tests/regressions.sh
	
uninstall:

	chmod +x uninstall
	./uninstall
	rm uninstall
