

PREFIX=/shbin/

LIST = dog duwrap grop headsh remaster which ldd_wrapper ls remove_executable exponentation hex_to_int hex_to_ip integer_to_spoken sort 


all: $(LIST)

clean:
	$(RM) $(LIST) 
	
install:

	@mkdir -p $(DESTDIR)/$(PREFIX)/
	@cp -a $(LIST) $(DESTDIR)/$(PREFIX)/
