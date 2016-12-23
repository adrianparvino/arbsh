
.SILENT: buildenvars clearenvars
.PHONY: toolchain


RELEASE = grafland-0.3a.tar.gz
WEBSITE = http://www.csit.parkland.edu/~cgraff1
SPWD = $(shell pwd)
NAME = $(shell basename $(SPWD))
SSHSERVER = cgraff1@shaula.csit.parkland.edu:public_html/



all:

	-$(MAKE) -C bin 
	-$(MAKE) -C irc
	-$(MAKE) -C gsh
	-$(MAKE) -s -C shbin
	-$(MAKE) -C editor
	-$(MAKE) -C sysmon
	-$(MAKE) -C math

clean:

	$(MAKE) -C bin clean 
	$(MAKE) -C irc clean
	$(MAKE) -C gsh clean
	$(MAKE) -C shbin clean
	$(MAKE) -C editor clean
	$(MAKE) -C sysmon clean
	$(MAKE) -C math clean


install:

	-$(MAKE) -C bin install 
	-$(MAKE) -C irc install
	-$(MAKE) -C gsh install
	-$(MAKE) -C shbin install 
	-$(MAKE) -C editor install
	-$(MAKE) -C sysmon install
	-$(MAKE) -C math install
	# Install toolchain last if it exists
	-$(MAKE) -C toolchain install


uninstall:

	-$(MAKE) -C bin uninstall 
	-$(MAKE) -C irc uninstall
	-$(MAKE) -C gsh uninstall
	-$(MAKE) -C shbin uninstall 
	-$(MAKE) -C editor uninstall
	-$(MAKE) -C sysmon uninstall
	#-$(MAKE) -C math uninstall 
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

	rm README.html
	-printf "\t$(WEBSITE)/$(RELEASE)\n" >> README
	-printf "\n" >> README
	printf '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"> <pre>\n' > README.html
	cat README >> README.html
	printf '</pre>\n' >> README.html
	sed -i 's/\(http.*\)/<a href="&">&<\/a>/g' README.html
	sed -i 's/\([a-Z,0-9,.,-]*@.*\)/<a href="mailto:&">&<\/a>/g' README.html
	sed -i '2s/\(^[^\t][a-Z].*\)/<br clear="left"\/><\/pre><dl><strong>&<\/strong><\/dl><pre>/' README.html
	sed -i 's/\(^[^\t][a-Z].*\)/<br clear="left"\/><\/pre><dl>&<\/dl><pre>/g' README.html
	sed -i 's/\(^[^\t]-.*\)/<\/pre><dd><hr\/><\/dd><pre>/g' README.html
	sed -i 's/\([a-Z,0-9,\/,.,-]*.png\)/<\/pre><dl><img src="&" style="float:left;height:15em;margin-right:1em"><\/img><pre><\/dl>/g' README.html

	-git add *
	-git commit -m $(RELEASE)
	-git push origin master
	cd $(SPWD)/.. && tar -c $(NAME) -f $(RELEASE)
	cd $(SPWD)/.. && scp $(RELEASE) $(SSHSERVER)


