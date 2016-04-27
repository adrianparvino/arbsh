

PREFIX ?= /bin

CFLAGS = -Wall -Wextra

all:

	$(CC) procsysmon.c -o procsysmon $(CFLAGS) $(LDFLAGS)

install:

	-@mkdir -p $(DESTDIR)/$(PREFIX)/
	-@cp -a procsysmon $(DESTDIR)/$(PREFIX)/
	-echo "rm $(DESTDIR)/$(PREFIX)/procsysmon" > uninstall.sh

uninstall:

	-chmod +x uninstall.sh
	-./uninstall.sh

clean:
	$(RM) procsysmon
	$(RM) uninstall.sh
	


