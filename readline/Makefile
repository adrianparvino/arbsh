CFLAGS := -Wall -Wextra -c -lm -Iinclude -I../include

LDFLAGS := -lm

CC := gcc

OBJ = $(shell for i in *.c ; do echo $${i%.c}.o ; done )

AR := ar

LIBNAME = readline

STATLIB = lib$(LIBNAME).a

DYNLIB = lib$(LIBNAME).so

DYNCC = CC="$(CC) -fpic"

DESTDIR := ../

all:

	$(MAKE) static
	$(MAKE) cleanobj
	$(MAKE) dynamic


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


cleanobj:

	$(RM) $(OBJ)


clean:
	$(MAKE) cleanobj
	$(RM) $(DYNLIB)
	$(RM) $(STATLIB)

install:

	-mkdir -p $(DESTDIR)/lib/
	-mkdir -p $(DESTDIR)/include/
	cp -r $(STATLIB) $(DESTDIR)/lib/
	cp -r $(DYNLIB) $(DESTDIR)/lib/
	cp -r include/readline/ $(DESTDIR)/include/

