#!/bin/sh

# (C) 2014, Docs, cgraf

# Create a minimal FreeBSD installation that uses an
# "mfsroot" memory disk.

# Create a crunched binary.
mkdir crunches
cd crunches
cat > crunched.conf <<EOF
srcdirs /usr/src/bin /usr/src/sbin 
srcdirs /usr/src/usr.bin /usr/src/usr.sbin 
srcdirs /usr/src/libexec 

# progs getty
progs init mount newfs sh
progs pwd_mkdb reboot ls hostname cp shutdown ifconfig 
progs ping chmod cat test moused mdconfig fsck dmesg
progs chown sync sleep ln chroot umount dhclient vi
progs rm du mount mkdir

ln sh -sh

libs -lcrypt -lufs  -ledit -ltermcap 
libs -lutil  -ltermcap -lgeom -lbsdxml 
libs -ljail -lsbuf -lipx -lncurses 
libs -lsbuf -lm -lkvm -lipsec  -lbsdxml 
EOF

crunchgen crunched.conf
make -f crunched.mk
cp crunched ..
cd ..


# start creating the root directory system.
mkdir mnt2
cd mnt2
mkdir bin tmp usr root etc home var sbin dev
cd usr
mkdir -p bin sbin libexec share/misc
cd ../var
mkdir -p run db crash 
cd ..  

# copy in the crunched binary 
cp ../crunched sbin/init

# hard link off all of its utilities
ln sbin/init  bin/ls
ln sbin/init  sbin/mount
ln sbin/init  sbin/mount_ffs
ln sbin/init  sbin/mount_mfs
ln sbin/init  sbin/umount
ln sbin/init  bin/sh 
ln sbin/init  usr/libexec/getty
ln sbin/init  sbin/ttyflags
ln sbin/init  sbin/pwd_mkdb
ln sbin/init  usr/bin/passwd
ln sbin/init  usr/bin/login
ln sbin/init  sbin/reboot
ln sbin/init  sbin/newfs 
ln sbin/init  bin/hostname 
ln sbin/init  sbin/shutdown 
ln sbin/init  sbin/ifconfig 
ln sbin/init  sbin/ping 
ln sbin/init  sbin/poweroff 
ln sbin/init  bin/cat 
ln sbin/init  bin/chmod 
ln sbin/init  bin/test
ln sbin/init  usr/bin/more 
ln sbin/init  usr/sbin/chown 
ln sbin/init  bin/sync 
ln sbin/init  bin/sleep 
ln sbin/init  bin/ln 
ln sbin/init  usr/sbin/vnconfig 
ln sbin/init  usr/sbin/moused 
ln sbin/init  sbin/getty
ln sbin/init  sbin/fsck
ln sbin/init  sbin/dmesg
ln sbin/init  usr/sbin/chroot 
ln sbin/init  bin/dhclient 
ln sbin/init  usr/sbin/du 
ln sbin/init  usr/bin/vi


# Copy in some essential files. ( not really complete )
echo "export PATH=/sbin:/bin:/usr/sbin:/usr/bin" >> etc/profile 
cp /etc/master.passwd etc
cp /etc/ttys etc
cp /etc/pwd.db etc
cp /etc/spwd.db etc
cp /etc/passwd etc 
cp /usr/share/misc/term* usr/share/misc/
cp /etc/gettytab etc 
cp /etc/dhcpd.conf etc/dhcpd.conf
cp /sbin/resolvconf sbin 
cp /etc/hosts etc

cd ..

# Create the ramdisk 
makefs -s 5m -t ffs mfsroot mnt2 
gzip -9 mfsroot 

# Create and mount the main disk image.
dd if=/dev/zero of=binary.img bs=1M count=50
mdconfig -a -t vnode -f binary.img -u 0
bsdlabel -w -B md0 auto
newfs -m 0 md0a
mount /dev/md0a /mnt

# get a standard kernel, uncompress it and gzip the kernel.
fetch ftp://ftp.freebsd.org/pub/FreeBSD/snapshots/i386/i386/9.2-STABLE/kernel.txz 
tar -xf kernel.txz -C .  
gzip -9 boot/kernel/kernel 

# copy in the kernel
mkdir -p /mnt/boot/kernel 
cp boot/kernel/kernel.gz /mnt/boot/kernel
cp boot/kernel/tmpfs.ko  /mnt/boot/kernel

# copy in most of /boot 
cp -r /boot/[a,b.c,d.e,f,g,l,m,p,s,v,z]* /mnt/boot

# create (overwrite) the "loader.conf" configuration file
cat > /mnt/boot/loader.conf <<EOF
geom_uzip_load="YES"
tmpfs_load="YES"
mfs_load="YES"
mfs_type="mfs_root"
mfs_name="/mfsroot"
ahci_load="YES"
vfs.root.mountfrom="ufs:/dev/md0"
EOF
  
# copy in the mfsroot.gz 
cp mfsroot.gz /mnt 

umount /mnt
mdconfig -d -u 0

