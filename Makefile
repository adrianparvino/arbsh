.SILENT: buildenvvars clearenvvars
.PHONY: ironwill

RELEASE = arbsh-0.4b.tar.gz
WEBSITE = http://www.csit.parkland.edu/~cgraff1
SPWD = $(shell pwd)
NAME = $(shell basename $(SPWD))
SSHSERVER = cgraff1@shaula.csit.parkland.edu:public_html/ 

all:

	
	-$(MAKE) -C readline
	
	-$(MAKE) -C arbprec
	-$(MAKE) -C gsh
	-$(MAKE) -C posix

	-$(MAKE) install
	#install the outside projects last

outside:

	-$(MAKE) get_graflibc
	-$(MAKE) make_graflibc
	-$(MAKE) make_ash
	# it's unlikely that the game builds on the user's target
	-$(MAKE) make_cube-zero

renew:

	rm -rf libc
	$(MAKE) get_graflibc
	$(MAKE) -C libc test

get_graflibc:

	-git clone https://www.github.com/cmgraff/graflibc libc

make_graflibc:

	-cd libc && ./configure --prefix=$(SPWD)/
	-$(MAKE) -C libc
	-$(MAKE) -C libc install

get_ash:

	-git clone https://www.github.com/cmgraff/ash
	-$(MAKE) -C ash

make_ash:

	-$(MAKE) get_ash
	-$(MAKE) -C ash install

make_cube-zero:

	-git clone https://www.github.com/cmgraff/cube-zero game
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
	-$(MAKE) -C libc clean
	-$(MAKE) -C ash clean
	-$(MAKE) -C game clean
	-$(RM) -r include lib bin


install:

	-$(MAKE) -C posix install
	-$(MAKE) -C gsh install
	-$(MAKE) -C readline install 
	-$(MAKE) -C arbprec install
	# Install ironwill last if it exists
	#-$(MAKE) -C ironwill install

ironwill:

	$(MAKE) -C ironwill

ironwillclean:

	$(MAKE) -C ironwill clean 

buildenvars:

	@$(MAKE) -s -C ironwill buildenvars

clearenvars:

	@$(MAKE) -s -C ironwill clearenvars

release:

	-rm README.html
	-printf "\t$(WEBSITE)/$(RELEASE)\n\n" >> README
	./.tx2html README
	-git add * .htaccess  .tx2html
	-git commit -m $(RELEASE)
	-git push origin master
	cd $(SPWD)/.. && tar -c $(NAME) -f $(RELEASE)
	cd $(SPWD)/.. && scp $(RELEASE) $(SSHSERVER)


