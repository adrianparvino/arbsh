# Musl otter cross (MOC)
# Musl/gcc cross compiler, 2 stages, combined tree, relocatable toolchain
# Written by CM Graff in April 2016
# Revised in May 2016 to use gcc 6


export MAKEINFO = false
XZ = gz 
XZTOOL = gzip -d -c
ARCHIVE = tar
ARCHIVETOOL = tar -x
TARG = i686-pc-linux-musl
# Musl only needs kernel headers for a bug with mips + gcc 6.
LINUX = linux-4.1
LINUX_MRR = https://www.kernel.org/pub/linux/kernel/v4.x/
LINUXARCH = mips
#
HOST = $(shell uname -m)
SPWD = $(shell pwd)
PREF = $(SPWD)/$(TARG)-toolchain
WORK = $(PREF)-work
SRC = $(SPWD)/src/
PATCH = $(SPWD)/patches/
USELESS = $(SPWD)/$(TARG)-useless
CONFALL = \
	--with-sysroot=$(PREF)/$(TARG) \
	--disable-multilib \
	--disable-libmudflap \
	--disable-libmpx \
	--infodir=$(USELESS) \
	--localedir=$(USELESS) \
	--mandir=$(USELESS) \
	--docdir=$(USELESS) \
	--htmldir=$(USELESS) \
	--dvidir=$(USELESS) \
	--pdfdir=$(USELESS) \
	--psdir=$(USELESS) \
	--enable-stage1-languages=c \
	--with-system-zlib \
	--disable-libcilkrts \
	--disable-gnu-indirect-function


CONF_0 = \
	--enable-languages=c \
	--with-newlib \
	--disable-libssp \
	--disable-nls \
	--disable-libquadmath \
	--disable-threads \
	--disable-decimal-float \
	--disable-shared \
	--disable-libgomp \
	--disable-libatomic

CONF_1 = \
	--enable-languages=$(LANGS) \
	--disable-libsanitizer \
	--disable-binutils \
	--disable-zlib \
	--disable-intl \
	--disable-gprof \
	--disable-ld \
	--disable-gas \
	--with-headers=$(PREF)/$(TARG)/include

BINUTILS = binutils-2.26
BINUTILS_MRR = https://ftp.gnu.org/gnu/binutils/
#GCC = gcc-5.3.0
GCC = gcc-6.1.0
GCC_MRR = https://ftp.gnu.org/gnu/gcc/$(GCC)/
MUSL = musl-1.1.14
MUSL_MRR = http://www.musl-libc.org/releases/
LANGS = c,c++,fortran
SOURCE = $(SPWD)/source/
PESSIMIZE = CFLAGS="-O0 -g0" CXXFLAGS="-O0 -g0"

# This is only used to document the build
HOSTTYPE = $(shell gcc -dumpmachine)
LOGDIR = $(SPWD)/$(HOSTTYPE)_logs
LOG = $(LOGDIR)/$(TARG)-log



all:

	-mkdir -p $(LOGDIR)
	-$(MAKE) install_path
	-$(MAKE) retrieve_musl retrieve_gcc retrieve_binutils
	-$(MAKE) retrieve_mcm_patches

ifeq ($(GCC),gcc-6.1.0)
	-$(MAKE) retrieve_nsz_patches
ifeq ($(TARG), mips-pc-linux-musl)
	-$(MAKE) linux_stage_headers
endif
endif

	-$(MAKE) gcc_stage0 > $(LOG)-gcc_stage0 2>&1
	-$(MAKE) gcc_stage0_install > $(LOG)-gcc_stage0_install 2>&1
	-$(MAKE) musl > $(LOG)-musl 2>&1
	-$(MAKE) gcc_stage1 > $(LOG)-gcc_stage1 2>&1
	#-$(MAKE) gcc_stage1_check > $(LOG)-gcc_stage1_check 2>&1
	-$(MAKE) gcc_stage1_install > $(LOG)-gcc_stage1_install 2>&1
	-$(MAKE) musl_install > $(LOG)-musl_install 2>&1
	-$(MAKE) test
	cat $(LOGDIR)/README

	
universe:

	-$(RM) $(LOGDIR)
	-mkdir -p $(LOGDIR)
	-printf "Automatic testing of build from %s;\n" "$(HOSTTYPE)" > $(LOGDIR)/$(HOSTTYPE)-report
	grep PRETTY_NAME /etc/os-release >> $(LOGDIR)/$(HOSTTYPE)-report
	date >> $(LOGDIR)/$(HOSTTYPE)-report
	printf "\nbinutils: %s\n" "$(BINUTILS)" >> $(LOGDIR)/$(HOSTTYPE)-report
	printf "gcc: %s\n" "$(GCC)" >> $(LOGDIR)/$(HOSTTYPE)-report
	printf "musl: %s\n\n" "$(MUSL)" >> $(LOGDIR)/$(HOSTTYPE)-report

	-$(MAKE) all TARG=aarch64-pc-linux-musl
	-$(MAKE) cleanall TARG=aarch64-pc-linux-musl
	-$(MAKE) all TARG=x86_64-pc-linux-musl
	-$(MAKE) cleanall TARG=x86_64-pc-linux-musl
	-$(MAKE) all TARG=sh-pc-linux-musl
	-$(MAKE) cleanall TARG=sh-pc-linux-musl
	-$(MAKE) all TARG=mips-pc-linux-musl
	-$(MAKE) cleanall TARG=mips-pc-linux-musl
	-$(MAKE) all TARG=microblaze-pc-linux-musl
	-$(MAKE) cleanall TARG=microblaze-pc-linux-musl
	-$(MAKE) all TARG=i586-pc-linux-musl
	-$(MAKE) cleanall TARG=i586-pc-linux-musl
	-cp Makefile $(LOGDIR)/BUILDUSED.mak

test:

	# Some trivial compile time tests
	-/$(PREF)/bin/$(TARG)-gcc pthreads-test.c -lpthread && \
	/$(PREF)/bin/$(TARG)-gcc -v 2>&1 | grep posix && \
	/$(PREF)/bin/$(TARG)-gcc testing.c && \
		printf "%s\t--> %s  (pthreads, c" "$(HOSTTYPE)" "$(TARG)" >> $(LOGDIR)/$(HOSTTYPE)-report || \
		printf "%s\t--> %s  (failed" "$(HOSTTYPE)" "$(TARG)" >> $(LOGDIR)/$(HOSTTYPE)-report
	-/$(PREF)/bin/$(TARG)-g++ testing.cpp && \
		printf ", c++" >> $(LOGDIR)/$(HOSTTYPE)-report 
	-/$(PREF)/bin/$(TARG)-gfortran testing.f && \
		printf ", fortran" >> $(LOGDIR)/$(HOSTTYPE)-report
	-printf ")\n" >> $(LOGDIR)/$(HOSTTYPE)-report 
	
	-cp $(LOGDIR)/$(HOSTTYPE)-report $(LOGDIR)/README
	

install_path: 

	$(eval PATH=$(PREF)/bin:$(PATH))
	-@mkdir -p $(WORK) $(SRC) $(PATCH) $(SOURCE)
	-@mkdir -p $(PREF)/$(TARG)/usr/include
	-@mkdir -p $(PREF)/include


retrieve_gcc:

	-@cd $(SRC) && test -e $(GCC).$(ARCHIVE).$(XZ) || \
		wget $(GCC_MRR)/$(GCC).$(ARCHIVE).$(XZ)
	-@cd $(SOURCE) && test -e $(GCC) || \
		$(XZTOOL) $(SRC)/$(GCC).$(ARCHIVE).$(XZ) | $(ARCHIVETOOL)


retrieve_binutils:

	-@cd $(SRC) && test -e $(BINUTILS).$(ARCHIVE).$(XZ) || \
		wget $(BINUTILS_MRR)/$(BINUTILS).$(ARCHIVE).$(XZ)
	-@cd $(SOURCE) && test -e $(BINUTILS) || \
		$(XZTOOL) $(SRC)/$(BINUTILS).$(ARCHIVE).$(XZ) | $(ARCHIVETOOL)


retrieve_musl: 

	-@cd $(SRC) && test -e $(MUSL).$(ARCHIVE).$(XZ) || \
		wget $(MUSL_MRR)/$(MUSL).$(ARCHIVE).$(XZ)
	-@cd $(SOURCE) && test -e $(MUSL) || \
		$(XZTOOL) $(SRC)/$(MUSL).$(ARCHIVE).$(XZ) | $(ARCHIVETOOL)


gcc_stage0: 

	-@cd $(PATCH) && wget http://www.csit.parkland.edu/~cgraff1/src/$(GCC)-musl.diff
	-@cd $(SOURCE)/$(GCC) && patch -N -p1 < $(PATCH)/$(GCC)-musl.diff
	-@cd $(SOURCE)/$(GCC) && ln -s $(SOURCE)/$(BINUTILS)/* .

	@mkdir -p $(WORK)/$(GCC)-0
	@cd $(WORK)/$(GCC)-0 && $(SOURCE)/$(GCC)/configure \
	--prefix=$(PREF) \
	--target=$(TARG) \
	$(CONFALL) \
	$(CONF_0)

	@$(PESSIMIZE) $(MAKE) -C $(WORK)/$(GCC)-0


gcc_stage0_install:

	@$(MAKE) -C $(WORK)/$(GCC)-0 install


musl: install_path 

	-@mkdir -p $(WORK)/$(MUSL)-0
	@cd $(WORK)/$(MUSL)-0 && $(SOURCE)/$(MUSL)/configure \
	--prefix=/ \
	--enable-debug \
	--enable-optimize \
	CROSS_COMPILE=$(TARG)- \
	CC=$(TARG)-gcc
	@$(MAKE) -C $(WORK)/$(MUSL)-0
	@$(MAKE) musl_install


musl_install:

	@$(MAKE) -C $(WORK)/$(MUSL)-0 install DESTDIR=$(PREF)/$(TARG)/


gcc_stage1:

	@mkdir -p $(WORK)/$(GCC)-1
	-@cd $(WORK)/$(GCC)-1 && $(SOURCE)/$(GCC)/configure \
	--prefix=$(PREF) \
	--target=$(TARG) \
	$(CONFALL) \
	$(CONF_1)

	-@$(MAKE) -C $(WORK)/$(GCC)-1

gcc_stage1_check:

	-@$(MAKE) -C $(WORK)/$(GCC)-1 check

gcc_stage1_install:

	-@$(MAKE) -C $(WORK)/$(GCC)-1 install

clean:

	-$(RM) -rf $(WORK)

cleanall:

	-$(RM) -rf $(WORK)
	-$(RM) -rf $(PREF)
	-$(RM) -rf $(USELESS)

destroy:

	-$(MAKE) cleanall TARG=aarch64-pc-linux-musl
	-$(MAKE) cleanall TARG=x86_64-pc-linux-musl
	-$(MAKE) cleanall TARG=sh-pc-linux-musl
	-$(MAKE) cleanall TARG=mips-pc-linux-musl
	-$(MAKE) cleanall TARG=microblaze-pc-linux-musl
	-$(MAKE) cleanall TARG=i586-pc-linux-musl

retrieve_mcm_patches:

	-git clone https://github.com/richfelker/musl-cross-make $(SOURCE)/mcm && \
	{ cat $(SOURCE)/mcm/patches/$(GCC)/* | ( cd $(SOURCE)/$(GCC) && patch -f -N -p1 ) ; \
	cat $(SOURCE)/mcm/patches/$(BINUTILS)/* | ( cd $(SOURCE)/$(BINUTILS) && patch -f -N -p1 ) ; } ;

retrieve_nsz_patches:

	-cd $(PATCH) && wget http://port70.net/~nsz/musl/gcc-6.1.0/0003-libgcc_s.patch
	-cd $(SOURCE)/$(GCC) && patch -f -N -p1 < $(PATCH)/0003-libgcc_s.patch

linux_stage:

	-@cd $(SRC) && test -e $(LINUX).$(ARCHIVE).$(XZ) || \
		wget $(LINUX_MRR)/$(LINUX).$(ARCHIVE).$(XZ)
	-@cd $(SOURCE) && test -e $(LINUX) || \
		$(XZTOOL) $(SRC)/$(LINUX).$(ARCHIVE).$(XZ) | $(ARCHIVETOOL)

linux_stage_headers: linux_stage

	$(MAKE) -C $(SOURCE)/$(LINUX) ARCH=$(LINUXARCH) \
	INSTALL_HDR_PATH=$(PREF)/$(TARG)/ \
	headers_install \
	O=$(WORK)/$(LINUX)-build
