
all:
	$(MAKE) exponentation
	$(MAKE) hex_to_int
	$(MAKE) hex_to_ip
	$(MAKE) integer_to_spoken
	$(MAKE) sort

clean:
	$(RM) exponentation hex_to_int hex_to_ip integer_to_spoken sort
	
install:

	@mkdir -p $(DESTDIR)
	@cp -a exponentation hex_to_int hex_to_ip integer_to_spoken sort $(DESTDIR)
