CFLAGS += -I./include/ -I../include -Wall -Wextra

LDFLAGS +=

OBJ = $(shell for i in src/*/*.c ; do echo $${i%.c}.o ; done )

LIBNAME = gcurses

STATLIB = lib$(LIBNAME).a

DESTDIR ?= ../

.PHONY: uninstall

TEST_OBJ = $(shell for i in tests/*.c ; do echo $${i%.c} ; done )

LDLIBS += -L. -l$(LIBNAME)

all:

	$(MAKE) static

static: $(OBJ)

	$(MAKE) static_link
	$(MAKE) static_create

static_link:

	$(AR) -cvq $(STATLIB) $(OBJ)

static_create: $(TEST_OBJ)

cleanobj:

	$(RM) $(OBJ) 

clean:
	$(MAKE) cleanobj
	$(RM) $(STATLIB)
	$(RM) $(TEST_OBJ) uninstall

install:

	mkdir -p $(DESTDIR)/lib/
	mkdir -p $(DESTDIR)/include/
	cp $(STATLIB) $(DESTDIR)/lib/
	cp -r include/* $(DESTDIR)/include/


