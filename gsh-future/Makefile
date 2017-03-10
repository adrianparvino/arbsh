.PHONY: uninstall

PREFIX ?= /bin

CFLAGS += -Wall -Wextra -I../include

HERE = $(PWD)

all:

	
	$(CC) gsh.c -o gsh ../readline-future/libreadline.a $(CFLAGS) $(LDFLAGS)
	$(CC) gsh-testing.c -o gsh-testing ../readline-future/libreadline.a $(CFLAGS) $(LDFLAGS)
	

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

