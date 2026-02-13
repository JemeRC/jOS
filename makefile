# ==============================================================================
# BUILD CONFIGURATION
# ==============================================================================

# Compiler
CC = i686-elf-gcc
CCFLAGS = -g -ffreestanding -m32 -fno-stack-protector -I$(LIBC_DIR)/include -I$(KERNEL_DIR)/include

# Linker
LD = i686-elf-ld
LDFLAGS = -T $(SRC_DIR)/linker.ld --oformat binary

# Source Directories
SRC_DIR 	= src
KERNEL_DIR 	= $(SRC_DIR)/kernel
DRIVERS_DIR = $(SRC_DIR)/kernel/drivers
SHELL_DIR 	= $(SRC_DIR)/kernel/shell
LIBC_DIR 	= $(SRC_DIR)/libc

# Build Directories
BUILD_DIR 			= build
BUILD_KERNEL_DIR	= $(BUILD_DIR)/kernel
BUILD_DRIVERS_DIR	= $(BUILD_DIR)/drivers
BUILD_SHELL_DIR 	= $(BUILD_DIR)/shell
BUILD_LIBC_DIR 		= $(BUILD_DIR)/libc

# ==============================================================================
# SOURCE LOCATIONS
# ==============================================================================

# Source Files
KERNEL_SOURCES 	= $(wildcard $(KERNEL_DIR)/*.c  )
DRIVERS_SOURCES = $(wildcard $(DRIVERS_DIR)/*.c )
SHELL_SOURCES 	= $(wildcard $(SHELL_DIR)/*.c	)
LIBC_SOURCES 	= $(wildcard $(LIBC_DIR)/*.c    )

# Object Files
KERNEL_OBJS 	= $(KERNEL_SOURCES:$(KERNEL_DIR)/%.c=$(BUILD_KERNEL_DIR)/%.o)
DRIVERS_OBJS	= $(DRIVERS_SOURCES:$(DRIVERS_DIR)/%.c=$(BUILD_DRIVERS_DIR)/%.o)
SHELL_OBJS 		= $(SHELL_SOURCES:$(SHELL_DIR)/%.c=$(BUILD_SHELL_DIR)/%.o)
LIBC_OBJS 		= $(LIBC_SOURCES:$(LIBC_DIR)/%.c=$(BUILD_LIBC_DIR)/%.o)

KERNEL_ENTRY_OBJ = $(BUILD_KERNEL_DIR)/kernel.o

ALL_OBJS = $(KERNEL_OBJS) $(DRIVERS_OBJS) $(LIBC_OBJS) $(SHELL_OBJS)

# ==============================================================================
# REGULI DE BUILD
# ==============================================================================

Start: Directories $(BUILD_DIR)/os-image.img

debug:
	@echo "SHELL SOURCES: $(SHELL_SOURCES)"
	@echo "SHELL OBJS:    $(SHELL_OBJS)"

Directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_KERNEL_DIR)
	@mkdir -p $(BUILD_DRIVERS_DIR)
	@mkdir -p $(BUILD_SHELL_DIR)
	@mkdir -p $(BUILD_LIBC_DIR)

# OS Image
$(BUILD_DIR)/os-image.img: $(BUILD_DIR)/boot.bin $(BUILD_DIR)/kernel.bin
	cat $^ > $@
	truncate -s +10k $@

# Link
$(BUILD_DIR)/kernel.bin: $(KERNEL_ENTRY_OBJ) $(ALL_OBJS)
	$(LD) -o $@ -Ttext 0x1000 -e kmain --oformat binary $^

# BootLoader
$(BUILD_DIR)/boot.bin: $(SRC_DIR)/boot/boot.asm
	nasm -f bin $< -o $@



# Kernel 
$(BUILD_KERNEL_DIR)/%.o: $(KERNEL_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Drivers
$(BUILD_DRIVERS_DIR)/%.o: $(DRIVERS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Shell
$(BUILD_SHELL_DIR)/%.o: $(SHELL_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# LibC
$(BUILD_LIBC_DIR)/%.o: $(LIBC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


# ==============================================================================
# UTILITIES
# ==============================================================================

debug:
	@echo "KERNEL SOURCES: $(KERNEL_SOURCES)"
	@echo "KERNEL OBJS:    $(KERNEL_OBJS)"
	@echo "ALL OBJS:       $(ALL_OBJS)"

clean:
	rm -rf $(BUILD_DIR)
clear: clean

run: Start
	qemu-system-i386 -fda $(BUILD_DIR)/os-image.img