#!/bin/sh
set -e
. ./build.sh $@ # pass arguments to build script

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/quick-os.kernel isodir/boot/quick-os.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "quick-os" {
	multiboot /boot/quick-os.kernel
}
EOF
grub-mkrescue -o quick-os.iso isodir
