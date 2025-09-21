.DEFAULT_GOAL := error
OUTPUT = ksboard.elf

GCC = arm-none-eabi-gcc
GCC_SOURCES_DEFAULT = ./src/system/ksb_boot.s ./src/system/ksb_base.c
GCC_ARGS_DEFAULT = -Wall -mthumb -Wextra -ffreestanding -nostartfiles -static -I./include -I./src/include

GCC_SOURCES_PROGRAM = $(wildcard ./program/*.c)

GCC_ARGS_A1 = -mcpu=cortex-m3 -T ./src/boards/a1/ksb_link_a1.ld -DSELECTED_BOARD=0xA1
GCC_SOURCES_A1 = ./src/boards/a1/ksb_a1.c

OBJCOPY = arm-none-eabi-objcopy
OBJCOPY_ARGS = -O binary

a1 :
	$(GCC) $(GCC_ARGS_DEFAULT) $(GCC_ARGS_A1) $(GCC_SOURCES_DEFAULT) $(GCC_SOURCES_A1) $(GCC_SOURCES_PROGRAM) -o $(OUTPUT)

bin:
	$(OBJCOPY) $(OBJCOPY_ARGS) $(OUTPUT) $(OUTPUT).bin

clean :
	del $(OUTPUT) $(OUTPUT).bin

error:
	@echo Usage: make [target]