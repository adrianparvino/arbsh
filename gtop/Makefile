.PHONY: uninstall

PREFIX ?= /bin

CFLAGS += -Wall -Wextra

all:

	$(MAKE) -C ../libc && test -e libgc.a || $(MAKE)
	$(MAKE) -C ../termcap && test -e libterminal.a || $(MAKE)
	$(CC) procsysmon.c -o procsysmon ../termcap/libterminal.a ../libc/libgc.a $(CFLAGS) $(LDFLAGS)

install:

	-@mkdir -p $(DESTDIR)/$(PREFIX)/
	-@cp -a procsysmon $(DESTDIR)/$(PREFIX)/
	-echo "rm $(DESTDIR)/$(PREFIX)/procsysmon" > uninstall

uninstall:

	-chmod +x uninstall
	-./uninstall

clean:

	$(RM) procsysmon
	$(RM) uninstall

