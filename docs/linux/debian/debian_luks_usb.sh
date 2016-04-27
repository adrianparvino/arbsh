#!/bin/sh

# DeCryptoStrap_usb_1.0
# This script is an attempt to standardize the variables used for all of my future debootstrap scripts


# Work by frogsnot

_ARCHITECTURE="amd64"

_RELEASE="squeeze"

_TAR_BALL="/home/tarball_with_kernel_grub.tar"

_IMAGE_PATH="/home/my_new_image.img"

_MAIN_DEV="/dev/sdb"

_BOOT_DEV="${_MAIN_DEV}1"            

_ROOT_DEV="${_MAIN_DEV}2"           

_HOME_DEV="${_MAIN_DEV}3"            

_BOOT_FS="ext2"

_ROOT_FS="ext2"

_HOME_FS="ext2"

_CRYPTO_HOME="1"

_CRYPTO_ROOT="2" 

_INCLUDES="\
htop,\
nmap,\
busybox,\
cryptsetup,\
linux-image-2.6.32-5-amd64,\
grub2"

_EXCLUDES="\
nano"

_CHROOT_DIR="/mnt/my_chrooten"

_ROOT_PASSWD="fr0g"

_USER_NAME="frog"

_USER_PASSWD="fr0g"

_USER_GROUPS="cdrom,floppy,audio,dip,video,plugdev"

_USER_SHELL="/bin/bash"

_MIRROR="http://cdn.debian.net/debian/"

_BOOT_START="5"

_BOOT_END="80"

_ROOT_START="80"

_ROOT_END="1000"

_HOME_START="1000"

_HOME_END="4000"
# End of vars


# Zero out the device
echo "Please wait .."
dd if=/dev/urandom of="${_MAIN_DEV}" bs=100M count=20  

# Make a partition table
parted "${_MAIN_DEV}" mklabel msdos

# Make /boot
parted "${_MAIN_DEV}" mkpart primary "${_BOOT_START}M" "${_BOOT_END}M"

# Make /
parted "${_MAIN_DEV}" mkpart primary "${_ROOT_START}M" "${_ROOT_END}M"

# Make /home
parted "${_MAIN_DEV}" mkpart primary "${_HOME_START}M" "${_HOME_END}M"

# Format /boot
/sbin/mkfs."${_BOOT_FS}" -L /boot "${_BOOT_DEV}"

# Encrypt and format /
cryptsetup --verbose --verify-passphrase luksFormat "${_ROOT_DEV}"
cryptsetup luksOpen "${_ROOT_DEV}" "${_CRYPTO_ROOT}"
/sbin/mkfs."${_ROOT_FS}" -L / /dev/mapper/"${_CRYPTO_ROOT}"

# Encrypt and format /home
cryptsetup --verbose --verify-passphrase luksFormat "${_HOME_DEV}"
cryptsetup luksOpen "${_HOME_DEV}" "${_CRYPTO_HOME}"
/sbin/mkfs."${_HOME_FS}" -L /home /dev/mapper/"${_CRYPTO_HOME}"

# Make the chroot directory
mkdir -p "${_CHROOT_DIR}"

# Mount :
# /
mkdir -p "${_CHROOT_DIR}"
mount /dev/mapper/"${_CRYPTO_ROOT}" "${_CHROOT_DIR}"
# /boot
mkdir -p "${_CHROOT_DIR}"/boot
mount "${_BOOT_DEV}" "${_CHROOT_DIR}"/boot
# /home
mkdir -p "${_CHROOT_DIR}"/home
mount /dev/mapper/"${_CRYPTO_HOME}" "${_CHROOT_DIR}"/home

# Debootstrap into the chroot
debootstrap                       \
--arch "${_ARCHITECTURE}"         \
--unpack-tarball="${_TAR_BALL}"   \
--include="${_INCLUDES}"          \
--exclude="${_EXCLUDES}"          \
--verbose                         \
"${_RELEASE}"                     \
"${_CHROOT_DIR}"                  \
"${_MIRROR}"


# Mount /dev, /sys and /proc
mount -o bind /dev  "${_CHROOT_DIR}"/dev                            
mount -o bind /sys  "${_CHROOT_DIR}"/sys                     
mount -o bind /proc "${_CHROOT_DIR}"/proc
 
############### Chroot stage 1
# Set root password
echo root:"${_ROOT_PASSWD}" > /home/passwd_root
cat /home/passwd_root | chroot "${_CHROOT_DIR}" /usr/sbin/chpasswd

# Set user password
chroot   "${_CHROOT_DIR}"         \
useradd  "${_USER_NAME}"          \
--shell  "${_USER_SHELL}"         \
--groups "${_USER_GROUPS}"        \
--create-home                     \
--user-group                         
echo "${_USER_NAME}":"${_USER_PASSWD}" > /home/passwd_user
cat /home/passwd_user | chroot "${_CHROOT_DIR}" /usr/sbin/chpasswd

# Install grub2
chroot "${_CHROOT_DIR}" grub-install "${_MAIN_DEV}"  

# Run update-grub
chroot "${_CHROOT_DIR}" update-grub

# Chroot's /etc/fstab 
chmod 755 "${_CHROOT_DIR}"/etc/fstab
echo /dev/mapper/"${_CRYPTO_ROOT}"   /      ext2  rw,errors=remount-ro  0 0     >> "${_CHROOT_DIR}"/etc/fstab
echo /dev/mapper/"${_CRYPTO_HOME}"   /home  ext2  defaults              0 0     >> "${_CHROOT_DIR}"/etc/fstab
echo "/dev/sda1                      /boot  ext2  rw                    0 0"    >> "${_CHROOT_DIR}"/etc/fstab
echo "proc                           /proc  proc  defaults              0 0"    >> "${_CHROOT_DIR}"/etc/fstab
 
# Chroot's /etc/crypttab
chmod 755 "${_CHROOT_DIR}"/etc/crypttab
echo "${_CRYPTO_ROOT}" /dev/sda2 none luks                                      >> "${_CHROOT_DIR}"/etc/crypttab
echo "${_CRYPTO_HOME}" /dev/sda3 none luks                                      >> "${_CHROOT_DIR}"/etc/crypttab

# Chroot's /etc/initramfs-tools/modules
chmod 755 "${_CHROOT_DIR}"/etc/initramfs-tools/modules
echo "dm_mod"                                                                   >> "${_CHROOT_DIR}"/etc/initramfs-tools/modules
chroot "${_CHROOT_DIR}" update-initramfs -u

# Make a build.log in the chroot
cp -r "${0}" /home/log"$(date)".log
echo "$(date)" > "${_CHROOT_DIR}"/build_date.garbage

############# End of chroot stage 1

# Umount /dev, /sys and /proc
umount "${_CHROOT_DIR}"/dev
umount "${_CHROOT_DIR}"/sys
umount "${_CHROOT_DIR}"/proc

# Umount everything
umount "${_BOOT_DEV}"
umount /dev/mapper/"${_CRYPTO_HOME}"
umount /dev/mapper/"${_CRYPTO_ROOT}"
cryptsetup luksClose /dev/mapper/"${_CRYPTO_HOME}"
cryptsetup luksClose /dev/mapper/"${_CRYPTO_ROOT}"
umount "${_ROOT_DEV}"

# Boot the resulting image
kvm "${_MAIN_DEV}"

