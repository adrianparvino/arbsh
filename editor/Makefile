.PHONY: uninstall

PREFIX ?= /bin

CFLAGS += -Wall -Wextra

	

all: 

	$(MAKE) termcap
	$(MAKE) libc
	$(CC) editor.c -o editor ../termcap/libterminal.a ../libc/libgc.a $(CFLAGS) $(LDFLAGS)


# DEPENDS: 

termcap:

	cd ../termcap && $(MAKE)

libc:

	cd ../libc && $(MAKE)


install:

	-@mkdir -p $(DESTDIR)/$(PREFIX)/
	-@cp -a editor $(DESTDIR)/$(PREFIX)/
	-echo "rm $(DESTDIR)/$(PREFIX)/editor" > uninstall

uninstall:

	-chmod +x uninstall
	-./uninstall

clean:

	$(RM) editor editor-testing
	$(RM) uninstall

