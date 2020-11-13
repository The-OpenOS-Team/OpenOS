all: OpenOSKernel apps
OpenOSKernel:
	mkdir kernel/bin
	as --32 kernel/boot.s -o kernel/bin/boot.o
	gcc -m32 -c kernel/kernel.c -o kernel/bin/kernel.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra
	gcc -m32 -c kernel/utils.c -o kernel/bin/utils.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra
	gcc -m32 -c kernel/char.c -o kernel/bin/char.o -std=gnu99 -ffreestanding -O1 -Wall -Wextra
	ld -m elf_i386 -T kernel/linker.ld kernel/bin/kernel.o kernel/bin/utils.o kernel/bin/char.o kernel/bin/boot.o -o kernel/bin/OpenOS.bin -nostdlib
apps:
	echo "TODO: Write the app subsystem as well as some test apps"
krnltst:
	qemu-system-x86_64 -kernel kernel/bin/OpenOS.bin
clean:
	rm -r kernel/bin
