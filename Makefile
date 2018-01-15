
all: 

	-$(MAKE) -C readline
	-$(MAKE) -C arbprec
	-$(MAKE) install
	
clean:

	$(MAKE) -C readline clean
	$(MAKE) -C arbprec clean
	$(RM) -r include lib bin

install:

	-$(MAKE) -C readline install 
	-$(MAKE) -C arbprec install


