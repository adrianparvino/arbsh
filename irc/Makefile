

PREFIX ?= /bin

CFLAGS = -Wall -Wextra

all:

	$(CC) irc.c -o irc $(CFLAGS) $(LDFLAGS)

install:

	-@mkdir -p $(DESTDIR)/$(PREFIX)/
	-@cp -a irc $(DESTDIR)/$(PREFIX)/
	-echo "rm $(DESTDIR)/$(PREFIX)/irc" > uninstall.sh

uninstall:

	-chmod +x uninstall.sh
	-./uninstall.sh

clean:
	$(RM) irc
	$(RM) uninstall.sh
	


