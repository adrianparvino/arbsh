

PREFIX=/shbin/

LIST = crosstoolchain dog duwrap grop headsh remaster which ldd_wrapper ls


all: $(LIST)

clean:
	$(RM) $(LIST) 
	
install:

	@mkdir -p $(DESTDIR)/$(PREFIX)/
	@cp -a $(LIST) $(DESTDIR)/$(PREFIX)/
