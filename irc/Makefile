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
	cd ../libc && $(MAKE)

termcap:
	cd ../termcap && $(MAKE)

readline:
	cd ../readline && $(MAKE)

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

