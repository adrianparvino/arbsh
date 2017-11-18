CFLAGS += -Wall -Wextra -I./include/

OBJ = $(shell for i in src/*.c ; do printf "%s\n" $${i%.c}.o ; done )

LIBNAME = control

STATLIB = lib$(LIBNAME).a

DESTDIR ?= ../

.PHONY: uninstall

PREFIX ?= /arbprec/

TEST_OBJ = $(shell for i in tests/*.c ; do printf "%s\n" $${i%.c} ; done )

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
	$(RM) $(STATLIB) 
	$(RM) $(TEST_OBJ) 
	
