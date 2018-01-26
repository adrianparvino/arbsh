
all: 

	-$(MAKE) -C readline
	-$(MAKE) -C arbprec
	
clean:

	$(MAKE) -C readline clean
	$(MAKE) -C arbprec clean 

