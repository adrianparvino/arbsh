.PHONY: uninstall

PREFIX ?= /bin

CFLAGS += -Wall -Wextra

all:

	$(MAKE) libc
	$(MAKE) termcap
	$(MAKE) readline

	$(CC) irc.c -o irc ../readline/libreadline.a ../termcap/libterminal.a ../libc/libgc.a $(CFLAGS) $(LDFLAGS)

# DEPENDS:

libc:
	cd ../libc && test -e libgc.a || $(MAKE)

termcap:
	cd ../termcap && test -e libterminal.a || $(MAKE)

readline:
	cd ../readline && test -e libreadline.a || $(MAKE)

install:

	-@mkdir -p $(DESTDIR)/$(PREFIX)/
	-@cp -a irc $(DESTDIR)/$(PREFIX)/
	-echo "rm $(DESTDIR)/$(PREFIX)/irc" > uninstall

uninstall:

	-chmod +x uninstall
	-./uninstall

clean:

	$(RM) irc
	$(RM) uninstall

