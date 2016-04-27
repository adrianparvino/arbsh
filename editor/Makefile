# editor - A simple text editor 
# See LICENSE file for copyright and license details.


PREFIX ?= /bin

CFLAGS = -Wall -Wextra

all:

	$(CC) editor.c -o editor $(CFLAGS) $(LDFLAGS)

sieve:
	$(CC) sieve.c -o sieve $(CFLAGS) $(LDFLAGS)

install:

	-@mkdir -p $(DESTDIR)/$(PREFIX)/
	-@cp -a editor $(DESTDIR)/$(PREFIX)/
	-echo "rm $(DESTDIR)/$(PREFIX)/editor" > uninstall.sh

uninstall:

	-chmod +x uninstall.sh
	-./uninstall.sh

clean:
	$(RM) editor
	$(RM) uninstall.sh
	

