PREFIX ?= /bin

CFLAGS += -Wall -Wextra

all:

	$(CC) gsh.c -o gsh $(CFLAGS) $(LDFLAGS)

install:

	-@mkdir -p $(DESTDIR)/$(PREFIX)/
	-@cp -a gsh $(DESTDIR)/$(PREFIX)/
	-echo "rm $(DESTDIR)/$(PREFIX)/gsh" > uninstall.sh

uninstall:

	-chmod +x uninstall.sh
	-./uninstall.sh

clean:
	$(RM) gsh
	$(RM) uninstall.sh
	


