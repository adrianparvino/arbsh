.PHONY: uninstall

PREFIX ?= /bin

CFLAGS += -Wall -Wextra -I usr/include

HERE = $(PWD)

all:

	cd ../readline && test -e libreadline.a || $(MAKE) 
	$(CC) gsh.c -o gsh ../readline/libreadline.a $(CFLAGS) $(LDFLAGS)
	#$(CC) gsh-testing.c -o gsh-testing $(CFLAGS) $(LDFLAGS)

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

