.DEFAULT_GOAL := error
OUTPUT = ksboard.elf

GCC = arm-none-eabi-gcc
GCC_SOURCES = ./system/ksb_boot.s ./system/ksb_base.c ./system/ksb_board_loader.c
GCC_ARGS = -Wall -mthumb -Wextra -ffreestanding -O2 -nostartfiles -static -I./include -I./src/include \
	-mcpu=cortex-m3 -T link.ld -DSELECTED_BOARD=0xA1

GCC_SOURCES_PROGRAM = $(wildcard ./program/*.c)

OBJCOPY = arm-none-eabi-objcopy
OBJCOPY_ARGS = -O binary

build :
	$(GCC) $(GCC_ARGS) $(GCC_SOURCES) $(GCC_SOURCES_PROGRAM) -o $(OUTPUT)

bin:
	$(OBJCOPY) $(OBJCOPY_ARGS) $(OUTPUT) $(OUTPUT).bin

clean :
	del $(OUTPUT) $(OUTPUT).bin

error:
	@echo Usage: make [target]