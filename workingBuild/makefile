kernel: 
	i386-elf-gcc -ffreestanding -m32 -g -c "code/kernel.cpp" -o "bin/kernel.o"
	nasm "code/kernel_entry.asm" -f elf -o "bin/kernel_entry.o"
	# order of linking is important if code is being wrongfully executed it might be because the main loop is below it
	i386-elf-ld -o "bin/full_kernel.bin" -Ttext 0x1000 "bin/kernel_entry.o"  "bin/kernel.o"    --oformat binary
	nasm "code/boot.asm" -f bin -o "bin/boot.bin"
	nasm "code/zeros.asm" -f bin -o "bin/empty.bin"
	cat "bin/boot.bin" "bin/full_kernel.bin"  "bin/empty.bin" > "bin/everything.bin"

run:
	qemu-system-x86_64 -drive format=raw,file="bin/everything.bin",index=0,if=floppy, -m 128M

test:
	gcc "kernel.cpp" -o "testCode/a.bin"