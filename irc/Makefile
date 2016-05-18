.PHONY: uninstall

PREFIX ?= /bin

CFLAGS += -Wall -Wextra

all:

	$(CC) irc.c -o irc $(CFLAGS) $(LDFLAGS)

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

