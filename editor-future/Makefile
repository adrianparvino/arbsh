.PHONY: uninstall

PREFIX ?= /bin

CFLAGS += -Wall -Wextra -I../include

	

all: 

	$(MAKE) curses
	$(MAKE) libc
	$(CC) editor.c -o editor ../curses-future/libterminal.a ../libc-future/libgc.a $(CFLAGS) $(LDFLAGS)
	#$(CC) editor-colorized.c -o editor-colorized ../termcap/libterminal.a ../libc/libgc.a $(CFLAGS) $(LDFLAGS)


# DEPENDS: 

curses:

	cd ../curses-future && test -e libterminal.a || $(MAKE)

libc:

	cd ../libc-future && test -e libgc.a || $(MAKE)


install:

	-@mkdir -p $(DESTDIR)/$(PREFIX)/
	-@cp -a editor $(DESTDIR)/$(PREFIX)/
	-echo "rm $(DESTDIR)/$(PREFIX)/editor" > uninstall

uninstall:

	-chmod +x uninstall
	-./uninstall

clean:

	$(RM) editor editor-colorized
	$(RM) uninstall

