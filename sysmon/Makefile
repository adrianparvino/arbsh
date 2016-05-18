.PHONY: uninstall

PREFIX ?= /bin

CFLAGS += -Wall -Wextra

all:

	$(CC) procsysmon.c -o procsysmon $(CFLAGS) $(LDFLAGS)

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

