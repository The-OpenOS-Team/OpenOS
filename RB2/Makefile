all: OpenOSKernel apps
OpenOSKernel:
	mkdir kernel/bin
	as --32 kernel/boot.s -o kernel/bin/boot.o
	gcc -m32 -c kernel/kernel.c -o kernel/bin/kernel.o -I"apps" -std=gnu99 -ffreestanding -O2
	gcc -m32 -c kernel/utils.c -o kernel/bin/utils.o -std=gnu99 -ffreestanding -O2
	gcc -m32 -c kernel/char.c -o kernel/bin/char.o -std=gnu99 -ffreestanding -O2
	gcc -m32 -c apps/terminal.c -o kernel/bin/terminal.o -I"kernel" -std=gnu99 -ffreestanding -O2
	gcc -m32 -c apps/oows.c -o kernel/bin/oows.o -I"kernel" -std=gnu99 -ffreestanding -O2
	ld -m elf_i386 -T kernel/linker.ld kernel/bin/kernel.o kernel/bin/utils.o kernel/bin/char.o kernel/bin/boot.o kernel/bin/terminal.o kernel/bin/oows.o -o kernel/bin/OpenOS.bin -nostdlib
apps:
	echo "TODO: Write the app subsystem as well as some test apps"
krnltst:
	qemu-system-x86_64 -kernel kernel/bin/OpenOS.bin
mkiso:
	mkdir -p temp/boot/grub
	cp kernel/bin/OpenOS.bin temp/boot/OpenOS.bin
	cp kernel/grub.cfg temp/boot/grub/grub.cfg
	grub-mkrescue -o OpenOS.iso temp
	rm -r temp
clean:
	rm -r kernel/bin
