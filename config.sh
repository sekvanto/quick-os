SYSTEM_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"

export VERSION=0
export PATCHLEVEL=0
export SUBLEVEL=1
export NAME="Quick Cherry"

export MAKE=${MAKE:-make}
export HOST=${HOST:-$(./default-host.sh)}

export AR=${HOST}-ar
export AS=${HOST}-as
export CC=${HOST}-gcc

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export COMMON_FLAGS="-O2 -g -fstack-protector "
export CFLAGS="${COMMON_FLAGS}"
export CPPFLAGS="${COMMON_FLAGS}"

# Configure the cross-compiler to use the desired system root.
export SYSROOT="$(pwd)/sysroot"
export CC="$CC --sysroot=$SYSROOT"

# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDEDIR"
fi
