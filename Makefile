.DEFAULT_GOAL := error
OUTPUT = ksboard.elf

GCC = arm-none-eabi-gcc
GCC_SOURCES = ./system/ksb_boot.s ./system/ksb_board_loader.c ./system/ksb_delay.c ./system/ksb_ports.c ./system/ksb_uart.c
GCC_ARGS = -Wall -mthumb -Wextra -ffreestanding -O2 -nostartfiles -static -I./include -I./library \
	-mcpu=cortex-m3 -T link.ld -DSELECTED_BOARD=0xA1

GCC_SOURCES_PROGRAM = $(wildcard ./program/*.c ./program/*.s)

RWILDCARD = $(foreach d,$(wildcard $(1:=/*)),$(call RWILDCARD,$d,$2) $(filter $(subst *,%,$2),$d))
GCC_LIBRARY_PROGRAM = $(call RWILDCARD,library,*.s *.c)

OBJCOPY = arm-none-eabi-objcopy
OBJCOPY_ARGS = -O binary

ifeq ($(OS), Windows_NT)
	CLEAN_COMMAND = del
else
	CLEAN_COMMAND = rm
endif

build :
	$(GCC) $(GCC_ARGS) $(GCC_SOURCES) $(GCC_SOURCES_PROGRAM) $(GCC_LIBRARY_PROGRAM) -o $(OUTPUT)

bin:
	$(OBJCOPY) $(OBJCOPY_ARGS) $(OUTPUT) $(OUTPUT).bin

clean :
	$(CLEAN_COMMAND) $(OUTPUT) $(OUTPUT).bin

error:
	@echo Usage: make [target]