#!/bin/sh 

echo "Logging the build to logfile.txt ..."


TARGET_ARCH="i386"
JOBZ="-j2"
IMAGELOC="binary.img"
MOUNTPOINT="/mnt"
SIZZE="50"
SOURCESZ="/usr/src"
MAKEOBJDIRPREFIX="/storage"

#exec 1> logfile.txt

close()
{
	umount "$MOUNTPOINT"
	mdconfig -d -u "${MEMORYDISK}" 
}

error()
{ 
	echo "$1"
	echo -n !!
	echo "Failed in build.sh!" 
	close
	exit 1
} 


# Build the object code in ram 
mkdir -p "${MAKEOBJDIRPREFIX}" 
mount -o size=2000M -t tmpfs buildarea "${MAKEOBJDIRPREFIX}"


# Create and mount a UFS disk image
mkdir -p "$MOUNTPOINT"
dd if=/dev/zero of="$IMAGELOC" bs=1M count="$SIZZE"
MEMORYDISK=$(mdconfig -a -t vnode -f "${IMAGELOC}" )
bsdlabel -w -B "${MEMORYDISK}" auto
newfs -m 0 "${MEMORYDISK}a"
mount "/dev/${MEMORYDISK}a" "$MOUNTPOINT" 



# Build an archtecture specific toolchain
export TARGET_ARCH
export MAKEOBJDIRPREFIX
make "$JOBZ" -C "$SOURCESZ" toolchain 
[ "$?" != "0" ] && error "toolchain"
BUILDENVARS=`make -C $SOURCESZ buildenvvars`



# userland

# rescue
mkdir -p "${MOUNTPOINT}/dev/"
mkdir -p "${MOUNTPOINT}/rescue/"
eval $BUILDENVARS make "$JOBZ" -C "$SOURCESZ/rescue"
[ "$?" != "0" ] && error "userland"
eval $BUILDENVARS make "$JOBZ" -C "$SOURCESZ/rescue" install DESTDIR="$MOUNTPOINT" 

# custom crunched binary ( experimental )
./cgctl.sh --crt_crunch --crt_chroot


# bootloader
mkdir -p "${MOUNTPOINT}/boot/"
mkdir -p "${MOUNTPOINT}/boot/defaults/"
mkdir -p "${MOUNTPOINT}/usr/lib/"
eval $BUILDENVARS make "$JOBZ" -C "$SOURCESZ/sys/boot/"
[ "$?" != "0" ] && error "bootloader"
eval $BUILDENVARS make "$JOBZ" -C "$SOURCESZ/sys/boot/i386" install WITHOUT_MAN=y DESTDIR="$MOUNTPOINT"

# kernel 
mkdir -p "${MOUNTPOINT}/boot/kernel/"
make "$JOBZ" -C "$SOURCESZ" buildkernel NO_MODULES="yes" KERNCONF=GENERIC
[ "$?" != "0" ] && error "kernel"
export SRCCONF="/etc/tempsrc.conf"
cat > /etc/tempsrc.conf <<EOF
WITHOUT_KERNEL_SYMBOLS=yes
EOF
make "$JOBZ" -C "$SOURCESZ" installkernel DESTDIR="$MOUNTPOINT" NO_MODULES="yes" 



# loader configuration
cat > "${MOUNTPOINT}/boot/loader.conf" <<EOF
init_script="runscript"
init_chroot="/"
EOF

cat > "${MOUNTPOINT}/runscript" <<EOF
/bin/mount -a
export PATH=/usr/sbin:/usr/bin:/usr/local/sbin:/usr/local/bin:/rescue
/bin/sh
EOF

chmod +x "${MOUNTPOINT}/runscript"

# System configuration
mkdir -p "${MOUNTPOINT}/etc/"

echo "/dev/ada0a  /  ufs  rw  0  0" >> "${MOUNTPOINT}/etc/fstab"

# unmount disk image
close

