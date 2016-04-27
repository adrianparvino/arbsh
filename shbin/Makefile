

PREFIX=/shbin/

all:
	$(MAKE) crosstoolchain
	$(MAKE) dog
	$(MAKE) duwrap
	$(MAKE) grop
	$(MAKE) headsh
	$(MAKE) remaster
	$(MAKE) which
	$(MAKE) ldd_wrapper

clean:
	$(RM) crosstoolchain dog duwrap grop headsh remaster which ldd_wrapper
	
install:

	@mkdir -p $(DESTDIR)/$(PREFIX)/
	@cp -a crosstoolchain \
	dog \
	duwrap \
	grop \
	headsh \
	remaster \
	which \
	ldd_wrapper \
	$(DESTDIR)/$(PREFIX)/
