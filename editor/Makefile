.PHONY: uninstall

PREFIX ?= /bin

CFLAGS += -Wall -Wextra

all:

	$(CC) editor.c -o editor $(CFLAGS) $(LDFLAGS)

install:

	-@mkdir -p $(DESTDIR)/$(PREFIX)/
	-@cp -a editor $(DESTDIR)/$(PREFIX)/
	-echo "rm $(DESTDIR)/$(PREFIX)/editor" > uninstall

uninstall:

	-chmod +x uninstall
	-./uninstall

clean:

	$(RM) editor
	$(RM) uninstall

