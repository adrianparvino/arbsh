.PHONY: uninstall

PREFIX ?= /bin/

DESTDIR ?= ../

CFLAGS += -Wall -Wextra -I../include

LDFLAGS += -L../lib 

LDLIBS += -lcurses

OBJ = $(shell for i in *.c; do echo $${i%%.c} ; done)

all: $(OBJ)

install:

	-@mkdir -p $(DESTDIR)/$(PREFIX)/
	-@cp -a $(OBJ) $(DESTDIR)/$(PREFIX)/

clean:

	$(RM) $(OBJ)
	$(RM) uninstall

native:

	$(MAKE) -C . LDLIBS='-lgcurses'

