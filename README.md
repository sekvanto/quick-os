A tiny operating system for i686

![quick-os](img/quick_os.png)

## Build

* configure: `./config.sh`
* install headers (optional): `./headers.sh`
* build (optional): `./build.sh`
* create an iso image: `./iso.sh`
* run: `./qemu.sh`
* clean: `./clean.sh`

## Development progress

Bare bones:
* boot
* initialize stack and the rest of the environment
* enter kernel

VGA terminal driver:
* support for newline
* terminal scrolling
* render ascii logo

Architecture:
* extensible libk and libc
* make build system support

## Credits

The skeleton structure of this operating system was taken from [the following guide](https://wiki.osdev.org/Hard_Build_System) on OSDev Wiki.
