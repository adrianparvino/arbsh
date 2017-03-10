
DESTDIR=/usr/include/

DESTDIR=../include


all:

	@echo "Nothing to be made"
	@echo "Try: make install DESTDIR=/path/to/headers/"
	@echo "Or:  make link DESTDIR=/path/to/headers/"

install:

	-mkdir -p $(DESTDIR)/
	cp -r include/termcap $(DESTDIR)/


link:

	ln include/termcap/ $(DESTDIR)/
