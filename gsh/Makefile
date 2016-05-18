.PHONY: uninstall

PREFIX ?= /bin

CFLAGS += -Wall -Wextra

all:

	$(CC) gsh.c -o gsh $(CFLAGS) $(LDFLAGS)
	$(CC) gsh-testing.c -o gsh-testing $(CFLAGS) $(LDFLAGS)

install:

	-@mkdir -p $(DESTDIR)/$(PREFIX)/
	-@cp -a gsh $(DESTDIR)/$(PREFIX)/
	-echo "rm $(DESTDIR)/$(PREFIX)/gsh" > uninstall

uninstall:

	-chmod +x uninstall
	-./uninstall

clean:

	$(RM) gsh
	$(RM) gsh-testing
	$(RM) uninstall

