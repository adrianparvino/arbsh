.PHONY: uninstall

CFLAGS += -Wall -Wextra
MAKEFLAGS += -i
PREFIX ?= /bin

SRC = $(wildcard *.c)
BIN = $(patsubst %.c,%,$(SRC))

all: $(BIN)

install:

	-mkdir -p $(DESTDIR)/$(PREFIX)
	cp -r $(BIN) $(DESTDIR)/$(PREFIX)
	echo "cd $(DESTDIR)/$(PREFIX)/ && rm $(BIN)" > uninstall

uninstall:

	chmod +x uninstall
	./uninstall

clean:

	$(RM) $(BIN)
	$(RM) a.out uninstall

