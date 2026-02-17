# ==============================================================================
# BUILD CONFIGURATION
# ==============================================================================

# --- i386 (32-bit Protected Mode) ---
COMPILER_i386      	= i686-elf-gcc
LINKER_i386      	= i686-elf-ld
ASSEMBLER_i386    	= nasm

COMPILER_FLAGS_i386 	= -g -ffreestanding -m32 -fno-stack-protector -fno-pie
LINKER_FLAGS_i386 		= -m elf_i386 -Ttext 0x1000 --oformat binary
ASSEMBLER_FLAGS_i386 	= -f elf32

# --- x86_64 (64-bit Long Mode) ---
COMPILER_x64       	= x86_64-elf-gcc
LINKER_x64       	= x86_64-elf-ld
ASSEMBLER_x64       = nasm

COMPILER_FLAGS_x64   	= -g -ffreestanding -m64 -mno-red-zone -mno-mmx -mno-sse -mno-sse2
LINKER_FLAGS_x64  		= -m elf_x86_64 -Ttext 0x1000 --oformat binary
ASSEMBLER_FLAGS_x64  	= -f elf64

# --- ARM (AArch64) ---
COMPILER_ARM	= aarch64-elf-gcc
LINKER_ARM		= aarch64-elf-ld
ASSEMBLER_ARM	= aarch64-elf-as 

COMPILER_FLAGS_ARM	= -g -ffreestanding -mcpu=cortex-a53 -mgeneral-regs-only
LINKER_FLAGS_ARM  	= -T $(SOURCE_DIR)/linker_arm.ld 

# ==============================================================================
# DIRECTORIES
# ==============================================================================

SOURCE_DIR 		= src
BUILD_DIR 		= build

# Include Paths
INCLUDE_FLAGS 	= -I$(SOURCE_DIR)/libc/include -I$(SOURCE_DIR)/kernel/include

# --- Source Directories ---
SOURCE_KERNEL_DIR 			= $(SOURCE_DIR)/kernel
SOURCE_KERNEL_i386_DIR 		= $(SOURCE_DIR)/kernel/arch/i386
SOURCE_KERNEL_x86_64_DIR	= $(SOURCE_DIR)/kernel/arch/x86_64
SOURCE_KERNEL_ARM_DIR		= $(SOURCE_DIR)/kernel/arch/arm

SOURCE_DRIVERS_DIR 			= $(SOURCE_DIR)/kernel/drivers
SOURCE_SHELL_DIR 			= $(SOURCE_DIR)/kernel/shell

SOURCE_LIBC_DIR 			= $(SOURCE_DIR)/libc
SOURCE_LIBC_i386_DIR		= $(SOURCE_DIR)/libc/arch/i386
SOURCE_LIBC_x86_64_DIR		= $(SOURCE_DIR)/libc/arch/x86_64
SOURCE_LIBC_ARM_DIR			= $(SOURCE_DIR)/libc/arch/arm

# --- Build Directories ---
BUILD_KERNEL_DIR		= $(BUILD_DIR)/kernel
BUILD_KERNEL_i386_DIR   = $(BUILD_DIR)/kernel/arch/i386
BUILD_KERNEL_x86_64_DIR = $(BUILD_DIR)/kernel/arch/x86_64
BUILD_KERNEL_ARM_DIR	= $(BUILD_DIR)/kernel/arch/arm

BUILD_DRIVERS_DIR		= $(BUILD_DIR)/drivers
BUILD_SHELL_DIR 		= $(BUILD_DIR)/shell

BUILD_LIBC_DIR 			= $(BUILD_DIR)/libc
BUILD_LIBC_i386_DIR		= $(BUILD_DIR)/libc/arch/i386
BUILD_LIBC_x86_64_DIR	= $(BUILD_DIR)/libc/arch/x86_64
BUILD_LIBC_ARM_DIR		= $(BUILD_DIR)/libc/arch/arm

# ==============================================================================
# FILES & OBJECTS
# ==============================================================================

# --- GENERIC SOURCES (Universal) ---
KERNEL_FILES 	= $(wildcard $(SOURCE_KERNEL_DIR)/*.c)
SHELL_FILES 	= $(wildcard $(SOURCE_SHELL_DIR)/*.c)
DRIVERS_FILES	= $(wildcard $(SOURCE_DRIVERS_DIR)/*.c)
LIBC_FILES	 	= $(wildcard $(SOURCE_LIBC_DIR)/*.c)

# --- ARCHITECTURE SPECIFIC SOURCES ---

# i386
KERNEL_i386_C 	= $(wildcard $(SOURCE_KERNEL_i386_DIR)/*.c)
KERNEL_i386_ASM	= $(wildcard $(SOURCE_KERNEL_i386_DIR)/*.asm)
# Excludem kernel_entry din lista generala ASM pentru a nu-l linka de doua ori sau gresit
KERNEL_i386_ASM := $(filter-out %kernel_entry.asm, $(KERNEL_i386_ASM))

LIBC_i386_C 	= $(wildcard $(SOURCE_LIBC_i386_DIR)/*.c)
LIBC_i386_ASM	= $(wildcard $(SOURCE_LIBC_i386_DIR)/*.asm)

# x86_64
KERNEL_x86_64_C	= $(wildcard $(SOURCE_KERNEL_x86_64_DIR)/*.c)
KERNEL_x86_64_ASM = $(wildcard $(SOURCE_KERNEL_x86_64_DIR)/*.asm)
# Excludem kernel_entry din lista generala ASM pentru a nu-l linka de doua ori sau gresit
KERNEL_x86_64_ASM := $(filter-out %kernel_entry.asm, $(KERNEL_x86_64_ASM))

LIBC_x86_64_C 	= $(wildcard $(SOURCE_LIBC_x86_64_DIR)/*.c)
LIBC_x86_64_ASM	= $(wildcard $(SOURCE_LIBC_x86_64_DIR)/*.asm)

# ARM
KERNEL_ARM_C	= $(wildcard $(SOURCE_KERNEL_ARM_DIR)/*.c)
KERNEL_ARM_ASM	= $(wildcard $(SOURCE_KERNEL_ARM_DIR)/*.s)
LIBC_ARM_C		= $(wildcard $(SOURCE_LIBC_ARM_DIR)/*.c)
LIBC_ARM_ASM	= $(wildcard $(SOURCE_LIBC_ARM_DIR)/*.s)

# --- OBJECT GENERATION ---

# Generic Objects
UNIVERSAL_OBJS 	= $(KERNEL_FILES:$(SOURCE_KERNEL_DIR)/%.c=$(BUILD_KERNEL_DIR)/%.o) \
                  $(DRIVERS_FILES:$(SOURCE_DRIVERS_DIR)/%.c=$(BUILD_DRIVERS_DIR)/%.o) \
                  $(SHELL_FILES:$(SOURCE_SHELL_DIR)/%.c=$(BUILD_SHELL_DIR)/%.o) \
                  $(LIBC_FILES:$(SOURCE_LIBC_DIR)/%.c=$(BUILD_LIBC_DIR)/%.o)

# Architecture Specific Objects
i386_OBJS 		= $(KERNEL_i386_C:$(SOURCE_KERNEL_i386_DIR)/%.c=$(BUILD_KERNEL_i386_DIR)/%.o) \
                  $(KERNEL_i386_ASM:$(SOURCE_KERNEL_i386_DIR)/%.asm=$(BUILD_KERNEL_i386_DIR)/%.o) \
                  $(LIBC_i386_C:$(SOURCE_LIBC_i386_DIR)/%.c=$(BUILD_LIBC_i386_DIR)/%.o) \
                  $(LIBC_i386_ASM:$(SOURCE_LIBC_i386_DIR)/%.asm=$(BUILD_LIBC_i386_DIR)/%.o)

x86_64_OBJS 	= $(KERNEL_x86_64_C:$(SOURCE_KERNEL_x86_64_DIR)/%.c=$(BUILD_KERNEL_x86_64_DIR)/%.o) \
                  $(KERNEL_x86_64_ASM:$(SOURCE_KERNEL_x86_64_DIR)/%.asm=$(BUILD_KERNEL_x86_64_DIR)/%.o) \
                  $(LIBC_x86_64_C:$(SOURCE_LIBC_x86_64_DIR)/%.c=$(BUILD_LIBC_x86_64_DIR)/%.o) \
                  $(LIBC_x86_64_ASM:$(SOURCE_LIBC_x86_64_DIR)/%.asm=$(BUILD_LIBC_x86_64_DIR)/%.o)

ARM_OBJS 		= $(KERNEL_ARM_C:$(SOURCE_KERNEL_ARM_DIR)/%.c=$(BUILD_KERNEL_ARM_DIR)/%.o) \
                  $(KERNEL_ARM_ASM:$(SOURCE_KERNEL_ARM_DIR)/%.s=$(BUILD_KERNEL_ARM_DIR)/%.o) \
                  $(LIBC_ARM_C:$(SOURCE_LIBC_ARM_DIR)/%.c=$(BUILD_LIBC_ARM_DIR)/%.o) \
                  $(LIBC_ARM_ASM:$(SOURCE_LIBC_ARM_DIR)/%.s=$(BUILD_LIBC_ARM_DIR)/%.o)

# Entry Points (Specific locations)
ENTRY_OBJ_i386 = $(BUILD_KERNEL_i386_DIR)/kernel_entry.o
ENTRY_OBJ_x64  = $(BUILD_KERNEL_x86_64_DIR)/kernel_entry.o
ENTRY_OBJ_ARM  = $(BUILD_KERNEL_ARM_DIR)/kernel_entry.o

# ==============================================================================
# MAIN TARGETS
# ==============================================================================

.PHONY: all i386 x86_64 ARM clean

all:
	@echo "Usage: make [i386 | x86_64 | ARM]"

# --- i386 ---
i386: TARGET_COMPILER = $(COMPILER_i386)
i386: TARGET_COMPILER_FLAGS = $(COMPILER_FLAGS_i386)
i386: TARGET_LINKER = $(LINKER_i386)
i386: TARGET_LINKER_FLAGS = $(LINKER_FLAGS_i386)
i386: TARGET_ASSEMBLER = $(ASSEMBLER_i386)
i386: TARGET_ASSEMBLER_FLAGS = $(ASSEMBLER_FLAGS_i386)
i386: i386_Directories $(BUILD_DIR)/os-image_i386.img

# --- x86_64 ---
x86_64: TARGET_COMPILER = $(COMPILER_x64)
x86_64: TARGET_COMPILER_FLAGS = $(COMPILER_FLAGS_x64)
x86_64: TARGET_LINKER = $(LINKER_x64)
x86_64: TARGET_LINKER_FLAGS = $(LINKER_FLAGS_x64)
x86_64: TARGET_ASSEMBLER = $(ASSEMBLER_x64)
x86_64: TARGET_ASSEMBLER_FLAGS = $(ASSEMBLER_FLAGS_x64)
x86_64: x86_64_Directories $(BUILD_DIR)/os-image_x64.img

# --- ARM ---
ARM: TARGET_COMPILER = $(COMPILER_ARM)
ARM: TARGET_COMPILER_FLAGS = $(COMPILER_FLAGS_ARM)
ARM: TARGET_LINKER = $(LINKER_ARM)
ARM: TARGET_LINKER_FLAGS = $(LINKER_FLAGS_ARM)
ARM: ARM_Directories $(BUILD_DIR)/kernel_arm.bin

# ==============================================================================
# LINKING
# ==============================================================================

$(BUILD_DIR)/os-image_i386.img: $(BUILD_DIR)/boot.bin $(BUILD_DIR)/kernel_i386.bin
	cat $^ > $@
	truncate -s +10k $@

$(BUILD_DIR)/kernel_i386.bin: $(ENTRY_OBJ_i386) $(UNIVERSAL_OBJS) $(i386_OBJS)
	$(TARGET_LINKER) $(TARGET_LINKER_FLAGS) -o $@ $^

$(BUILD_DIR)/os-image_x64.img: $(BUILD_DIR)/boot.bin $(BUILD_DIR)/kernel_x64.bin
	cat $^ > $@
	truncate -s +10k $@

$(BUILD_DIR)/kernel_x64.bin: $(ENTRY_OBJ_x64) $(UNIVERSAL_OBJS) $(x86_64_OBJS)
	$(TARGET_LINKER) $(TARGET_LINKER_FLAGS) -o $@ $^

$(BUILD_DIR)/kernel_arm.bin: $(ENTRY_OBJ_ARM) $(UNIVERSAL_OBJS) $(ARM_OBJS)
	$(TARGET_LINKER) $(TARGET_LINKER_FLAGS) -o $@ $^

$(BUILD_DIR)/boot.bin: $(SOURCE_DIR)/boot/boot.asm
	nasm -f bin $< -o $@

# ==============================================================================
# COMPILATION RULES
# ==============================================================================

# --- KERNEL ENTRY ---
$(BUILD_KERNEL_i386_DIR)/kernel_entry.o: $(SOURCE_KERNEL_i386_DIR)/kernel_entry.asm
	$(ASSEMBLER_i386) $(ASSEMBLER_FLAGS_i386) $< -o $@

$(BUILD_KERNEL_x86_64_DIR)/kernel_entry.o: $(SOURCE_KERNEL_x86_64_DIR)/kernel_entry.asm
	$(ASSEMBLER_x64) $(ASSEMBLER_FLAGS_x64) $< -o $@

$(BUILD_KERNEL_ARM_DIR)/kernel_entry.o: $(SOURCE_KERNEL_ARM_DIR)/kernel_entry.s
	aarch64-elf-as $< -o $@

# --- GENERIC C ---
$(BUILD_KERNEL_DIR)/%.o: $(SOURCE_KERNEL_DIR)/%.c
	$(TARGET_COMPILER) $(TARGET_COMPILER_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@
$(BUILD_DRIVERS_DIR)/%.o: $(SOURCE_DRIVERS_DIR)/%.c
	$(TARGET_COMPILER) $(TARGET_COMPILER_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@
$(BUILD_SHELL_DIR)/%.o: $(SOURCE_SHELL_DIR)/%.c
	$(TARGET_COMPILER) $(TARGET_COMPILER_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@
$(BUILD_LIBC_DIR)/%.o: $(SOURCE_LIBC_DIR)/%.c
	$(TARGET_COMPILER) $(TARGET_COMPILER_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

# --- KERNEL ARCH C ---
$(BUILD_KERNEL_i386_DIR)/%.o: $(SOURCE_KERNEL_i386_DIR)/%.c
	$(COMPILER_i386) $(COMPILER_FLAGS_i386) $(INCLUDE_FLAGS) -c $< -o $@
$(BUILD_KERNEL_x86_64_DIR)/%.o: $(SOURCE_KERNEL_x86_64_DIR)/%.c
	$(COMPILER_x64) $(COMPILER_FLAGS_x64) $(INCLUDE_FLAGS) -c $< -o $@
$(BUILD_KERNEL_ARM_DIR)/%.o: $(SOURCE_KERNEL_ARM_DIR)/%.c
	$(COMPILER_ARM) $(COMPILER_FLAGS_ARM) $(INCLUDE_FLAGS) -c $< -o $@

# --- KERNEL ARCH ASM ---
$(BUILD_KERNEL_i386_DIR)/%.o: $(SOURCE_KERNEL_i386_DIR)/%.asm
	$(ASSEMBLER_i386) $(ASSEMBLER_FLAGS_i386) $< -o $@
$(BUILD_KERNEL_x86_64_DIR)/%.o: $(SOURCE_KERNEL_x86_64_DIR)/%.asm
	$(ASSEMBLER_x64) $(ASSEMBLER_FLAGS_x64) $< -o $@
$(BUILD_KERNEL_ARM_DIR)/%.o: $(SOURCE_KERNEL_ARM_DIR)/%.s
	$(ASSEMBLER_ARM) $< -o $@

# --- LIBC ARCH C ---
$(BUILD_LIBC_i386_DIR)/%.o: $(SOURCE_LIBC_i386_DIR)/%.c
	$(COMPILER_i386) $(COMPILER_FLAGS_i386) $(INCLUDE_FLAGS) -c $< -o $@
$(BUILD_LIBC_x86_64_DIR)/%.o: $(SOURCE_LIBC_x86_64_DIR)/%.c
	$(COMPILER_x64) $(COMPILER_FLAGS_x64) $(INCLUDE_FLAGS) -c $< -o $@
$(BUILD_LIBC_ARM_DIR)/%.o: $(SOURCE_LIBC_ARM_DIR)/%.c
	$(COMPILER_ARM) $(COMPILER_FLAGS_ARM) $(INCLUDE_FLAGS) -c $< -o $@

# --- LIBC ARCH ASM ---
$(BUILD_LIBC_i386_DIR)/%.o: $(SOURCE_LIBC_i386_DIR)/%.asm
	$(ASSEMBLER_i386) $(ASSEMBLER_FLAGS_i386) $< -o $@
$(BUILD_LIBC_x86_64_DIR)/%.o: $(SOURCE_LIBC_x86_64_DIR)/%.asm
	$(ASSEMBLER_x64) $(ASSEMBLER_FLAGS_x64) $< -o $@
$(BUILD_LIBC_ARM_DIR)/%.o: $(SOURCE_LIBC_ARM_DIR)/%.s
	$(ASSEMBLER_ARM) $< -o $@

# ==============================================================================
# DIRECTORIES
# ==============================================================================

Universal_Directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_KERNEL_DIR)
	@mkdir -p $(BUILD_DRIVERS_DIR)
	@mkdir -p $(BUILD_SHELL_DIR)
	@mkdir -p $(BUILD_LIBC_DIR)

i386_Directories: Universal_Directories
	@mkdir -p $(BUILD_KERNEL_i386_DIR)
	@mkdir -p $(BUILD_LIBC_i386_DIR)

x86_64_Directories: Universal_Directories
	@mkdir -p $(BUILD_KERNEL_x86_64_DIR)
	@mkdir -p $(BUILD_LIBC_x86_64_DIR)

ARM_Directories: Universal_Directories
	@mkdir -p $(BUILD_KERNEL_ARM_DIR)
	@mkdir -p $(BUILD_LIBC_ARM_DIR)

clean:
	rm -rf $(BUILD_DIR)
clear: clean