aarch64_musl()
{
	export OM_ARCH="aarch64"
	export OM_TUPLEPRSFX="-pc-linux-"
	export OM_LIBC="musl"
	export OM_CONF=""
	export OM_LINUXARCH="arm64"
	export OM_BACKWARDCOMPAT="arm64"

}

aarch64_musl_test()
{
	qemu-system-aarch64 \
	-machine virt \
	-cpu cortex-a57 \
	-machine type=virt \
	-nographic -smp 1 \
	-m 2048 \
	-kernel libroot/boot/vmlinuz \
	-initrd backup.cpio.gz \
	-append "root=/dev/ram rdinit=/bin/sh console=ttyAMA0"
}

