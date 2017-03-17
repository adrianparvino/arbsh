.PHONY: uninstall

PREFIX ?= /bin/

DESTDIR ?= ../

CFLAGS += -Wall -Wextra -I../include

LDFLAGS += -L../lib

LDLIBS += 

OBJ = $(shell for i in *.c; do echo $${i%%.c} ; done)

OBJ_TARG =  $(shell for i in *.c; do echo $(DESTDIR)/$(PREFIX)/$${i%%.c} ; done)

all: $(OBJ)

install:

	-@mkdir -p $(DESTDIR)/$(PREFIX)/
	-@cp -a $(OBJ) $(DESTDIR)/$(PREFIX)/
	-echo "rm $(OBJ_TARG)" > uninstall

uninstall:

	-chmod +x uninstall
	-./uninstall

clean:

	$(RM) $(OBJ)
	$(RM) uninstall

