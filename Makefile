

.SILENT: buildenvvars clearenvvars
.PHONY: toolchain

RELEASE = grafland-0.3e.tar.gz
WEBSITE = http://www.csit.parkland.edu/~cgraff1
SPWD = $(shell pwd)
NAME = $(shell basename $(SPWD))
SSHSERVER = cgraff1@shaula.csit.parkland.edu:public_html/



all:
	

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
	-$(MAKE) -C irc
	-$(MAKE) install

	#install the outside projects last for now
	-$(MAKE) get_grafmusl
	-$(MAKE) make_grafmusl
	-$(MAKE) get_ash
	-$(MAKE) make_grafcube

renew:

	rm -rf libc
	make get_grafmusl
	cd libc && ./build.sh

get_grafmusl:

	-git clone https://www.github.com/cmgraff/grafmusl libc

make_grafmusl:

	-cd libc && ./configure --prefix=$(SPWD)/
	-$(MAKE) -C libc
	-$(MAKE) -C libc install

get_ash:

	-git clone https://www.github.com/cmgraff/ash
	-$(MAKE) -C ash

make_grafcube:

	-git clone https://www.github.com/cmgraff/grafcube game
	$(MAKE) -C game
	

clean:

	-$(MAKE) -C readline clean
	-$(MAKE) -C termcap clean
	-$(MAKE) -C curses clean
	-$(MAKE) -C posix clean 
	-$(MAKE) -C lsb clean 
	-$(MAKE) -C irc clean
	-$(MAKE) -C gsh clean
	-$(MAKE) -C editor clean
	-$(MAKE) -C arbprec clean
	-$(RM) -r include lib


install:

	-$(MAKE) -C posix install 
	-$(MAKE) -C linux install 
	-$(MAKE) -C irc install
	-$(MAKE) -C gsh install 
	-$(MAKE) -C editor install
	# Install toolchain last if it exists
	#-$(MAKE) -C toolchain install

toolchain:

	$(MAKE) -C toolchain

toolchainclean:

	$(MAKE) -C toolchain clean 

buildenvvars:

	$(MAKE) -s -C toolchain buildenvars

clearenvvars:

	$(MAKE) -s -C toolchain clearenvars

release:

	-rm README.html
	-printf "\t$(WEBSITE)/$(RELEASE)\n\n" >> README
	./.tx2html README
	-git add * .htaccess  .tx2html
	-git commit -m $(RELEASE)
	-git push origin master
	cd $(SPWD)/.. && tar -c $(NAME) -f $(RELEASE)
	cd $(SPWD)/.. && scp $(RELEASE) $(SSHSERVER)


