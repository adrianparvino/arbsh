## Ottercross, Copyright, 2016. CM Graff. see grafos/LICENSE for copying details

HTUPLE = $(shell uname -m) 

# exported variables may be used in the build system API (a stub)
export LIBROOT = $(PWD)/libroot
export XZ = gz
export XZTOOL = gzip -d -c
export ARCHIVE = tar
export ARCHIVETOOL = tar -x
export ARCH = i686
export PLATFORM = pc-linux
export VENDOR = musl
export TARG = $(ARCH)-$(PLATFORM)-$(VENDOR)
export LINUXARCH = x86
export UCLIBCTARG = i386
export HOST = $(shell uname -m)
export SPWD = $(shell pwd)
export PREF = $(SPWD)/$(TARG)-toolchain
export WORK = $(PREF)-work
export SRC = $(SPWD)/src/
export PATCH = $(SPWD)/patches/

# This is not used here, it's part of the build system API (a stub)
export BUILDENVVARS = \
	CROSS_COMPILE=$(TARG)- \
	CC=$(TARG)-gcc \
	LD=$(TARG)-ld \
	RANLIB=$(TARG)-ranlib \
	AS=$(TARG)-as \
	CXX=$(TARG)-g++ \
	NM=$(TARG)-nm \
	STRIP=$(TARG)-strip \
	OBJDUMP=$(TARG)-objdump \
	AR=$(TARG)-ar \
	F77=$(TARG)-gfortran \
	CC_FOR_BUILD=gcc \
	HOSTCC=gcc \
	PATH=$(PREF)/bin:$(PATH)

# Configuration to "tack on" ( --with-sysroot= is supplied as an example )
#CONF = --with-sysroot=$(PREF)/$(TARG)
CONF = --with-sysroot=$(PREF)/$(TARG) --disable-multilib
# binutils
BINUTILS = binutils-2.26
BINUTILS_MRR = https://ftp.gnu.org/gnu/binutils/
BINUTILS_KRING = ftp://ftp.gnu.org/gnu/gnu-keyring.gpg
BINUTILS_SIG = $(BINUTILS).$(ARCHIVE).$(XZ).sig

# gcc
GCC = gcc-5.3.0
GCC_MRR = https://ftp.gnu.org/gnu/gcc/$(GCC)
GCC_KRING = ftp://ftp.gnu.org/gnu/gnu-keyring.gpg
GCC_SIG = $(GCC).$(ARCHIVE).$(XZ).sig

# linux
LINUX = linux-4.1
LINUX_MRR = https://www.kernel.org/pub/linux/kernel/v4.x/
LINUX_KRING =
LINUX_SIG = $(LINUX).$(ARCHIVE).sign

# musl
MUSL = musl-1.1.14
MUSL_MRR = http://www.musl-libc.org/releases/
MUSL_KRING = http://www.musl-libc.org/musl.pub
MUSL_SIG = $(MUSL).$(ARCHIVE).$(XZ).asc

# uclibc
UCLIBC_VER = 1.0.13
UCLIBC = uClibc-ng-$(UCLIBC_VER)
UCLIBC_MRR = http://downloads.uclibc-ng.org/releases/$(UCLIBC_VER)/
UCLIBC_KRING = http://waldemar-brodkorb.de/wbx.asc
UCLIBC_SIG = $(UCLIBC).$(ARCHIVE).$(XZ).asc

# glibc
GLIBC = glibc-2.20
GLIBC_MRR = https://ftp.gnu.org/gnu/glibc/
GLIBC_KRING = ftp://ftp.gnu.org/gnu/gnu-keyring.gpg
GLIBC_SIG = $(GLIBC).$(ARCHIVE).$(XZ).sig

# mpc

# gmp

# mpfr

# Languages to build (c, c++, fortran, ada and etc.)
LANGS = c,c++

# Pessimize or optimize
OPTIMIZE = CFLAGS="-O2 -g0" CXXFLAGS="-O2 -g0"
PESSIMIZE = CFLAGS="-O0 -g0" CXXFLAGS="-O0 -g0"

# autologger
HTUPLE = $(shell gcc -dumpmachine)
LOGDIR = $(HTUPLE)_logs
LOG = $(LOGDIR)/$(TARG)-log
LOGM ?= 2>&1 | tee

# gpg checking
STATUS = $(shell cat status)
export GNUPGHOME = $(SPWD)/gnupg


all:

	-mkdir -p $(LOGDIR)
	$(MAKE) install_path
	$(MAKE) binutils_retrieve
	$(MAKE) gcc_stage_retrieve
	$(MAKE) gcc_stage0 $(LOGM) $(LOG)-gcc_stage0 2>&1
	$(MAKE) gcc_stage0_install $(LOGM) $(LOG)-gcc_stage0_install 2>&1

ifeq ($(VENDOR),musl)
	# -$(MAKE) linux_stage_headers
	$(MAKE) musl_stage $(LOGM) $(LOG)-musl_stage 2>&1
	$(MAKE) musl_gcc_stage1 $(LOGM) $(LOG)-musl_gcc_stage1 2>&1
endif

ifeq ($(VENDOR),uclibc)
	-$(MAKE) linux_stage_headers $(LOGM) $(LOG)-linux_stage_headers 2>&1
	-$(MAKE) -i uclibc_stage $(LOGM) $(LOG)-uclibc_stage 2>&1
	-$(MAKE) -i uclibc_gcc_stage1 $(LOGM) $(LOG)-uclibc_gcc_stage1 2>&1
	-$(MAKE) -i uclibc_gcc_stage1_install $(LOGM) $(LOG)-uclibc_gcc_stage1_install 2>&1
endif

ifeq ($(VENDOR),gnu)
	-$(MAKE) linux_stage_headers $(LOGM) $(LOG)-linux_stage_headers 2>&1
	-$(MAKE) -i gnu_stage $(LOGM) $(LOG)-gnu_stage 2>&1
	-$(MAKE) -i gnu_gcc_stage1 $(LOGM) $(LOG)-gnu_gcc_stage1 2>&1
	-$(MAKE) -i gnu_gcc_stage1_install $(LOGM) $(LOG)-gnu_gcc_stage1_install 2>&1
endif


install_path: 

	$(eval PATH=$(PREF)/bin:$(PATH))
	-@mkdir -p $(PREF)/$(TARG)/usr/include
	-@mkdir -p $(PREF)/$(TARG)/include
	-@mkdir -p $(SPWD)/src $(SPWD)/patches
	-@mkdir -p $(LIBROOT)
	-@mkdir -p $(WORK)
	-@mkdir -p $(GNUPGHOME)
	-@chmod 700 $(GNUPGHOME)


binutils_retrieve:

	-@mkdir -p $(WORK)

	-@cd $(SRC) && test -e $(BINUTILS).$(ARCHIVE).$(XZ) || \
		wget $(BINUTILS_MRR)/$(BINUTILS).$(ARCHIVE).$(XZ)
	-@cd $(SRC) && test -e $(BINUTILS_SIG) || \
		wget $(BINUTILS_MRR)/$(BINUTILS_SIG) 
	-@cd $(SRC) && test -e ring || wget $(BINUTILS_KRING) -O ring 
	-@cd $(SRC) && gpg --verify --keyring ./ring  \
		$(BINUTILS_SIG) $(BINUTILS).$(ARCHIVE).$(XZ)
	-@cd $(WORK) && test -e $(BINUTILS) || \
		$(XZTOOL) $(SRC)/$(BINUTILS).$(ARCHIVE).$(XZ) | $(ARCHIVETOOL)


linux_stage:

	-mkdir -p $(WORK)/$(LINUX)-build
	-mkdir -p $(GNUPGHOME)
	-chmod 700 $(GNUPGHOME)
	-touch $(SPWD)/status
	-cd $(SRC) && test -e $(LINUX).$(ARCHIVE).$(XZ) || \
		wget $(LINUX_MRR)/$(LINUX).$(ARCHIVE).$(XZ)

	-cd $(SRC) && test -e $(LINUX_SIG) || wget $(LINUX_MRR)/$(LINUX_SIG)
	-cd $(SRC) && test -e $(LINUX).$(ARCHIVE) || gzip $(LINUX).$(ARCHIVE).$(XZ) -d -c > $(LINUX).$(ARCHIVE)
	-cd $(SRC) && gpg --status-file $(SPWD)/status --verify $(LINUX_SIG) $(LINUX).$(ARCHIVE)
	-$(MAKE) linux_stage2
	
linux_stage2:

	-gpg --keyserver hkp://keys.gnupg.net --recv-keys $(STATUS) 
	-cd $(SRC) && gpg --verify $(LINUX_SIG) $(LINUX).$(ARCHIVE)
	-tar -xf $(SRC)/$(LINUX).$(ARCHIVE) -C $(WORK)

linux_stage_headers: linux_stage

	$(MAKE) -C $(WORK)/$(LINUX) ARCH=$(LINUXARCH) \
	INSTALL_HDR_PATH=$(PREF)/$(TARG)/ \
	headers_install \
	O=$(WORK)/$(LINUX)-build

linux_stage_clean:

	-@rm -rf $(WORK)/$(LINUX)-build 

gcc_stage_retrieve:

	-@cd $(SRC) && test -e $(GCC).$(ARCHIVE).$(XZ) || \
		wget $(GCC_MRR)/$(GCC).$(ARCHIVE).$(XZ)
	-@cd $(SRC) && test -e $(GCC_SIG) || \
		wget $(GCC_MRR)/$(GCC_SIG)
	-@cd $(SRC) && test -e ring || wget $(GCC_KRING) -O ring
	-@cd $(SRC) && gpg --verify --keyring ./ring  \
		$(GCC_SIG) $(GCC).$(ARCHIVE).$(XZ)
	-@cd $(WORK) && test -e $(GCC) || \
		$(XZTOOL) $(SRC)/$(GCC).$(ARCHIVE).$(XZ) | $(ARCHIVETOOL)

gcc_stage0: 

	-@mkdir -p $(WORK)/$(GCC)-build

ifeq ($(VENDOR),musl) 
	-@cd $(SPWD)/patches/ && wget http://www.csit.parkland.edu/~cgraff1/src/$(GCC)-musl.diff 
	-@cd $(WORK)/$(GCC) && patch -N -p1 < $(SPWD)/patches/$(GCC)-musl.diff
endif
	# In-tree binutils:
	-cd  $(WORK)/$(GCC) && ln -s $(WORK)/$(BINUTILS)/* .

	@mkdir -p $(WORK)/$(GCC)-build
	@cd $(WORK)/$(GCC)-build && $(WORK)/$(GCC)/configure \
	--prefix=$(PREF) \
	--target=$(TARG) \
	--enable-languages=c \
	--with-newlib \
	--disable-libssp \
	--disable-nls \
	--disable-libquadmath \
	--disable-threads \
	--disable-decimal-float \
	--disable-shared \
	--disable-libmudflap \
	--disable-libgomp \
	--disable-libatomic \
	$(CONF)

	$(PESSIMIZE) $(MAKE) -C $(WORK)/$(GCC)-build 

gcc_stage0_install:

	$(MAKE) -C $(WORK)/$(GCC)-build install 

gcc_stage_clean:

	-@rm -rf $(WORK)/$(GCC)-build

musl_stage_retrieve:

	-@cd $(SRC) && test -e $(MUSL).$(ARCHIVE).$(XZ) || \
		wget $(MUSL_MRR)/$(MUSL).$(ARCHIVE).$(XZ)
	-@cd $(SRC) && test -e $(MUSL_SIG) || \
		wget $(MUSL_MRR)/$(MUSL_SIG)
	-@cd $(SRC) && test -e ring || wget $(MUSL_KRING) -O ring
	-@cd $(SRC) && gpg --import ring
	-@cd $(SRC) && gpg --verify $(MUSL_SIG) $(MUSL).$(ARCHIVE).$(XZ)
	-@cd $(WORK) && test -e $(MUSL) || \
		$(XZTOOL) $(SRC)/$(MUSL).$(ARCHIVE).$(XZ) | $(ARCHIVETOOL)

musl_stage: install_path

	$(MAKE) -i musl_stage_retrieve

	@cd $(WORK)/$(MUSL) && $(WORK)/$(MUSL)/configure \
	--prefix=/ \
	--enable-debug \
	--enable-optimize \
	CROSS_COMPILE=$(TARG)- \
	CC=$(TARG)-gcc 
	$(MAKE) -C $(WORK)/$(MUSL)
	$(MAKE) -C $(WORK)/$(MUSL) install DESTDIR=$(PREF)/$(TARG)/

musl_gcc_stage1:

	-@rm -rf $(WORK)/$(GCC)-stage1
	@mkdir -p $(WORK)/$(GCC)-stage1
	@cd $(WORK)/$(GCC)-stage1 && $(WORK)/$(GCC)/configure \
	--prefix=$(PREF) \
	--target=$(TARG) \
	--enable-languages=$(LANGS) \
	--disable-libmudflap \
	--disable-libsanitizer \
	--with-headers=$(PREF)/$(TARG)/include \
	--disable-nls \
	--with-ld=$(PREF)/bin/$(TARG)-ld \
	--with-as=$(PREF)/bin/$(TARG)-as \
	$(CONF) 

	$(MAKE) -C $(WORK)/$(GCC)-stage1
	$(MAKE) -C $(WORK)/$(GCC)-stage1 install

	$(MAKE) -C $(WORK)/$(MUSL) install DESTDIR=$(PREF)/$(TARG)/

musl_stage_clean:

	-@rm -rf $(WORK)/$(MUSL)
	-@rm -rf $(WORK)/$(GCC)-stage1

uclibc_stage: install_path

	-@cd $(SRC) && test -e $(UCLIBC).$(ARCHIVE).$(XZ) || \
		  wget $(UCLIBC_MRR)/$(UCLIBC).$(ARCHIVE).$(XZ)
	-@cd $(SRC) && test -e $(UCLIBC_SIG) || \
		wget $(UCLIBC_MRR)/$(UCLIBC_SIG)
	-@cd $(SRC) && test -e ring || wget $(UCLIBC_KRING) -O ring
	-@cd $(SRC) && gpg --import ring
	-@cd $(SRC) && gpg --verify $(UCLIBC_SIG) $(UCLIBC).$(ARCHIVE).$(XZ)
	-@cd $(WORK) && test -e $(UCLIBC) || \
		  $(XZTOOL) $(SRC)/$(UCLIBC).$(ARCHIVE).$(XZ) | $(ARCHIVETOOL)

	@cd $(WORK)/$(UCLIBC) && mkdir -p $(PREF)/$(TARG)/usr/src/linux
	@cd $(WORK)/$(UCLIBC) && echo "KERNEL_HEADERS=\"$(PREF)/$(TARG)/include\"" >> .config 
	@cd $(WORK)/$(UCLIBC) && echo "TARGET_$(UCLIBCTARG)=y" >> .config 
	@cd $(WORK)/$(UCLIBC) && echo "RUNTIME_PREFIX=\"$(PREF)/$(TARG)/\"" >> .config 
	@cd $(WORK)/$(UCLIBC) && echo "DEVEL_PREFIX=\"$(PREF)/$(TARG)/\"" >> .config 
	@cd $(WORK)/$(UCLIBC) && echo "HAVE_SHARED=y" >> .config 
	@cd $(WORK)/$(UCLIBC) && echo "UCLIBC_HAS_THREADS_NATIVE=y" >> .config 
	#@cd "$(SPWD)/$(UCLIBC)" && echo "UCLIBC_HAS_UTMPX=y" >> .config 
	#@cd "$(SPWD)/$(UCLIBC)" && echo "UCLIBC_HAS_UTMP=y" >> .config 
	@cd $(WORK)/$(UCLIBC) && echo "UCLIBC_SUSV3_LEGACY=y" >> .config 
	@cd $(WORK)/$(UCLIBC) && echo "UCLIBC_HAS_WCHAR=y" >> .config 
	#@cd "$(SPWD)/$(UCLIBC)" && echo "UCLIBC_HAS_NETWORK_SUPPORT=y" >> .config 
	#@cd "$(SPWD)/$(UCLIBC)" && echo "UCLIBC_HAS_FULL_RPC=y" >> .config 
	#@cd "$(SPWD)/$(UCLIBC)" && echo "UCLIBC_HAS_REENTRANT_RPC=y" >> .config 
	#@cd "$(SPWD)/$(UCLIBC)" && echo "UCLIBC_HAS_RPC=y" >> .config
	-@cd $(WORK)/$(UCLIBC) && echo y | make CROSS="$(TARG)-"  oldconfig
	$(MAKE) -C $(WORK)/$(UCLIBC) CROSS="$(TARG)-" PREFIX="" install

uclibc_gcc_stage1: install_path 

	@mkdir -p $(WORK)/$(GCC)-stage1

	-@cd $(WORK)/$(GCC)-stage1 && $(WORK)/$(GCC)/configure \
	--prefix=$(PREF) \
	--target=$(TARG) \
	--enable-languages=$(LANGS) \
	--disable-werror \
	--disable-threads \
	--disable-libquadmath \
	--disable-libmudflap \
	--disable-libsanitizer \
	--with-ld=$(PREF)/bin/$(TARG)-ld \
	--with-as=$(PREF)/bin/$(TARG)-as \
	--with-headers=$(PREF)/$(TARG)/include \
	--disable-nls \
	$(CONF)

	$(MAKE) -i -C $(WORK)/$(GCC)-stage1

uclibc_gcc_stage1_install: install_path

	$(MAKE) -i -C $(WORK)/$(GCC)-stage1 install

gnu_stage: install_path

	-@cd $(SRC) && test -e $(GLIBC).$(ARCHIVE).$(XZ) || \
		wget $(GLIBC_MRR)/$(GLIBC).$(ARCHIVE).$(XZ)
	-@cd $(SRC) && test -e $(GLIBC_SIG) || \
		wget $(GLIBC_MRR)/$(GLIBC_SIG)
	-@cd $(SRC) && test -e ring || wget $(GLIBC_KRING) -O ring
	-@cd $(SRC) && gpg --verify --keyring ./ring  \
		$(GLIBC_SIG) $(GLIBC).$(ARCHIVE).$(XZ)
	-@cd $(WORK) && test -e $(GLIBC) || \
		$(XZTOOL) $(SRC)/$(GLIBC).$(ARCHIVE).$(XZ) | $(ARCHIVETOOL)

	@rm -rf $(WORK)/$(GLIBC)-build/
	-@mkdir -p $(WORK)/$(GLIBC)-build

	@cd $(WORK)/$(GLIBC)-build && $(WORK)/$(GLIBC)/configure \
	--prefix=$(PREF)/$(TARG) \
	--host=$(TARG) \
	--build=$(HTUPLE) \
	--target=$(TARG) \
	--with-headers=$(PREF)/$(TARG)/include \
	--disable-werror \
	--enable-obsolete-rpc \
	--enable-kernel=2.6.32 \
	--enable-add-ons \
	libc_cv_forced_unwind=yes \
	libc_cv_c_cleanup=yes \
	libc_cv_ctors_header=yes \
	$(CONF)

	$(MAKE) -C $(WORK)/$(GLIBC)-build 
	$(MAKE) -C $(WORK)/$(GLIBC)-build install

gnu_gcc_stage1:

	#-@touch $(PREF)/$(TARG)/include/gnu/stubs.h 

	@rm -rf $(WORK)/$(GCC)-stage1
	@mkdir -p $(WORK)/$(GCC)-stage1
	-@cd $(WORK)/$(GCC)-stage1 && $(WORK)/$(GCC)/configure \
	--prefix=$(PREF) \
	--target=$(TARG) \
	--enable-languages=$(LANGS) \
	--with-headers=$(PREF)/$(TARG)/include \
	--with-ld=$(PREF)/bin/$(TARG)-ld \
	--with-as=$(PREF)/bin/$(TARG)-as \
	--disable-werror \
	--disable-shared \
	$(CONF) 

	$(MAKE) -C $(WORK)/$(GCC)-stage1 
	$(MAKE) -C $(WORK)/$(GCC)-stage1 install 

gnu_gcc_stage1_install:

	$(MAKE) -C $(WORK)/$(GLIBC)-build
	$(MAKE) -C $(WORK)/$(GLIBC)-build install

clean:
	-$(MAKE) cleanall

cleanall:

	-@rm -rf $(WORK)
	-@rm -rf $(GNUPGHOME)

cleanhard:

	-$(MAKE) cleanall
	-@rm -rf $(PREF)
	-@rm -rf $(LOGDIR)


