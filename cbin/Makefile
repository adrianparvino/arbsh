CFLAGS += -Wall -Wextra
MAKEFLAGS += -i
PREFIX ?= /bin

SRC = $(wildcard *.c)
BIN = $(patsubst %.c,%,$(SRC))

all: $(BIN)


install:
	-mkdir -p $(DESTDIR)/$(PREFIX)
	cp -r $(BIN) $(DESTDIR)/$(PREFIX)
	echo "cd $(DESTDIR)/$(PREFIX)/ && rm $(BIN)" > uninstal.sh

uninstall:
	$(MAKE) uninstal
	./uninstal

clean:
	$(RM) $(BIN)
	$(RM) a.out uninstal uninstal.sh

