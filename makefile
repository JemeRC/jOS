# Directories
SRC_DIR = src
BUILD_DIR = build
KERNEL_DIR = $(SRC_DIR)/kernel
DRIVERS_DIR = $(SRC_DIR)/kernel/drivers
SHELL_DIR = $(SRC_DIR)/kernel/shell
LIBC_DIR = $(SRC_DIR)/libc

# Source Files
KERNEL_SOURCES = $(wildcard $(KERNEL_DIR)/*.c)
DRIVERS_SOURCES = $(wildcard $(DRIVERS_DIR)/*.c)
SHELL_SOURCES = $(wildcard $(SHELL_DIR)/*.c)
LIBC_SOURCES = $(wildcard $(LIBC_DIR)/*.c)

# Object Files
OBJ_FILES = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(KERNEL_SOURCES))) \
            $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(DRIVERS_SOURCES))) \
			$(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(SHELL_SOURCES))) \
            $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(LIBC_SOURCES)))


# Compiler Flags
CFLAGS = -ffreestanding -m32 -fno-stack-protector -I$(LIBC_DIR)/include -g

# Linker Flags
LDFLAGS = -T $(SRC_DIR)/linker.ld --oformat binary

Start: Directories Link

Directories:
	mkdir -p $(BUILD_DIR)

Link: $(OBJ_FILES) AssemblyObject
	i686-elf-ld -o $(BUILD_DIR)/kernel.bin $(LDFLAGS) $(OBJ_FILES)
	
	cat $(BUILD_DIR)/boot.bin $(BUILD_DIR)/kernel.bin > $(BUILD_DIR)/os-image.bin
	truncate -s +10k $(BUILD_DIR)/os-image.bin

# Kernel 
$(BUILD_DIR)/%.o: $(KERNEL_DIR)/%.c
	i686-elf-gcc $(CFLAGS) -c $< -o $@

# Drivers
$(BUILD_DIR)/%.o: $(DRIVERS_DIR)/%.c
	i686-elf-gcc $(CFLAGS) -c $< -o $@

# Shell
$(BUILD_DIR)/%.o: $(SHELL_DIR)/%.c
	i686-elf-gcc $(CFLAGS) -c $< -o $@

# LibC
$(BUILD_DIR)/%.o: $(LIBC_DIR)/%.c
	i686-elf-gcc $(CFLAGS) -c $< -o $@

# Bootloader
AssemblyObject: $(SRC_DIR)/boot.asm
	nasm -f bin $(SRC_DIR)/boot.asm -o $(BUILD_DIR)/boot.bin


clean:
	rm -rf $(BUILD_DIR)
clear: clean