SourceCodeLocation = ./src
BuildCodeLocation = ./build
KernelCompiledFiles = $(BuildCodeLocation)/kernel

Start: Directories Link

Directories:
	mkdir -p $(BuildCodeLocation)
	mkdir -p $(KernelCompiledFiles)

Link: BootSector Kernel
	i686-elf-ld -T $(SourceCodeLocation)/linker.ld --oformat binary -o $(BuildCodeLocation)/os.bin $(BuildCodeLocation)/boot.o $(KernelCompiledFiles)/kernel.o

BootSector: $(SourceCodeLocation)/boot.asm
	nasm -f elf32 $(SourceCodeLocation)/boot.asm -o $(BuildCodeLocation)/boot.o

Kernel: $(SourceCodeLocation)/kernel.c 
	i686-elf-gcc -ffreestanding -m32 -fno-stack-protector -c $(SourceCodeLocation)/kernel.c -o $(KernelCompiledFiles)/kernel.o

test: Start
	./run.sh

clean:
	rm -rf $(BuildCodeLocation)