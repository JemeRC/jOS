SRC_DIR = src
BUILD_DIR = build
KERNEL_DIR = $(SRC_DIR)/kernel
DRIVERS_DIR = $(SRC_DIR)/kernel/drivers

C_SOURCES = $(wildcard $(KERNEL_DIR)/*.c $(DRIVERS_DIR)/*.c)
HEADERS = $(wildcard $(KERNEL_DIR)/include/*.h $(DRIVERS_DIR)/*.h)

OBJ_FILES = $(patsubst $(KERNEL_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SOURCES))

KERNEL_OBJS = $(OBJ_FILES)


Start: Directories Link

Directories:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/drivers

Link: Kernel Drivers AssemblyObject
	i686-elf-ld -o $(BUILD_DIR)/kernel.bin -Ttext 0x1000 -e kmain --oformat binary \
		$(BUILD_DIR)/kernel.o \
		$(filter-out $(BUILD_DIR)/kernel.o, $(OBJ_FILES))
	
	cat $(BUILD_DIR)/boot.bin $(BUILD_DIR)/kernel.bin > $(BUILD_DIR)/os-image.bin
	truncate -s +10k $(BUILD_DIR)/os-image.bin

Kernel: $(KERNEL_DIR)/kernel.c
	i686-elf-gcc -ffreestanding -m32 -fno-stack-protector -c $< -o $(BUILD_DIR)/kernel.o

Drivers: $(OBJ_FILES)
$(BUILD_DIR)/drivers/%.o: $(DRIVERS_DIR)/%.c
	i686-elf-gcc -ffreestanding -m32 -fno-stack-protector -c $< -o $@

AssemblyObject: $(SRC_DIR)/boot.asm
	nasm -f bin $(SRC_DIR)/boot.asm -o $(BUILD_DIR)/boot.bin



test: Start
	./run.sh

clear: clean

clean:
	rm -rf $(BUILD_DIR)