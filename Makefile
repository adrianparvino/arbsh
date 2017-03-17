
.SILENT: buildenvars clearenvars
.PHONY: toolchain


RELEASE = grafland-0.3b.tar.gz
WEBSITE = http://www.csit.parkland.edu/~cgraff1
SPWD = $(shell pwd)
NAME = $(shell basename $(SPWD))
SSHSERVER = cgraff1@shaula.csit.parkland.edu:public_html/



all:

	-$(MAKE) -C libc
	-$(MAKE) -C libc install
	-$(MAKE) -C termcap install
	-$(MAKE) -C readline
	-$(MAKE) -C readline install
	-$(MAKE) -C curses
	-$(MAKE) -C curses install
	-$(MAKE) -C arbprec
	-$(MAKE) -C arbprec install
	-$(MAKE) -C gsh
	-$(MAKE) -C editor
	-$(MAKE) -C posix
	-$(MAKE) -C linux
	-$(MAKE) -C irc
	-$(MAKE) -C gtop
	

clean:

	-$(MAKE) -C readline clean
	-$(MAKE) -C termcap clean
	-$(MAKE) -C libc clean
	-$(MAKE) -C curses clean
	-$(MAKE) -C posix clean 
	-$(MAKE) -C linux clean 
	-$(MAKE) -C irc clean
	-$(MAKE) -C gsh clean
	-$(MAKE) -C editor clean
	-$(MAKE) -C gtop clean
	-$(RM) -r include lib


install:

	-$(MAKE) -C posix install 
	-$(MAKE) -C linux install 
	-$(MAKE) -C irc install
	-$(MAKE) -C gsh install 
	-$(MAKE) -C editor install
	-$(MAKE) -C gtop install 
	# Install toolchain last if it exists
	#-$(MAKE) -C toolchain install


uninstall:

	-$(MAKE) -C posix uninstall 
	-$(MAKE) -C linux uninstall 
	-$(MAKE) -C irc uninstall
	-$(MAKE) -C gsh uninstall
	-$(MAKE) -C editor uninstall
	-$(MAKE) -C gtop uninstall
	#-$(MAKE) -C toolchain uninstall

toolchain:

	$(MAKE) -C toolchain

toolchainclean:

	$(MAKE) -C toolchain clean 

buildenvars:

	$(MAKE) -s -C toolchain buildenvars

clearenvars:

	$(MAKE) -s -C toolchain clearenvars

release:

	-rm README.html
	-printf "\t$(WEBSITE)/$(RELEASE)\n" >> README
	-printf "\n" >> README
	-chmod +x legacy/libsh/text_to_html.sh README
	./legacy/libsh/text_to_html.sh README
	-git add *
	-git commit -m $(RELEASE)
	-git push origin master
	cd $(SPWD)/.. && tar -c $(NAME) -f $(RELEASE)
	cd $(SPWD)/.. && scp $(RELEASE) $(SSHSERVER)


