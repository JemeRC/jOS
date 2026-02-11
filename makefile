SourceCodeLocation = ./src
BuildCodeLocation = ./build

Binary: $(SourceCodeLocation)/boot.asm
	nasm $(SourceCodeLocation)/boot.asm -f bin -o $(BuildCodeLocation)/boot.bin

test: Binary
	./run.sh


