.PHONY: uninstall


SRC = $(wildcard *.sh)
BIN = $(patsubst %.sh,%,$(SRC))

PREFIX ?= /bin

all: $(BIN)

clean:

	$(RM) $(BIN) uninstall
	
install:

	@mkdir -p $(DESTDIR)/$(PREFIX)/
	@cp -a $(BIN) $(DESTDIR)/$(PREFIX)/
	echo "cd $(DESTDIR)/$(PREFIX)/ && rm $(BIN)" > uninstall

uninstall:

	chmod +x uninstall
	./uninstall
