# http://draconux.free.fr/download/os-dev/linux0.01/Image/hd_oldlinux.img.zip


#KVERS = linux-0.96c
#MIRROR = https://www.kernel.org/pub/linux/kernel/Historic/old-versions/

MIRROR = https://www.kernel.org/pub/linux/kernel/v2.6/ 
#KVERS = linux-2.6.0
KVERS = linux-2.6.39


#MIRROR = https://www.kernel.org/pub/linux/kernel/v2.0/
#KVERS = linux-2.0.1


#MIRROR = https://www.kernel.org/pub/linux/kernel/v1.0/
#KVERS = linux-1.0

#MIRROR = https://www.kernel.org/pub/linux/kernel/v1.2/
#KVERS = linux-1.2.0

SUFX = .tar.gz


build:
	#cd ${KVERS} && echo y | make menuconfig

	cd ${KVERS} && ARCH=i386 defconfig make
	#make -C ${KVERS}

untar:

	tar -xf ${KVERS}${SUFX}

get:

	wget "${MIRROR}/${KVERS}${SUFX}"

clean:

	rm ${KVERS}${SUFX}
