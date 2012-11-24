#
# Freertos empty project Makefile
# Written by Cristóvão Rufino <cristovaozr@gmail.com>
#
# Based on freertos_demo Makefile from Stellaris
#

CROSS_COMPILE=/opt/arm-2012.03/bin
CROSS_PREFIX=arm-none-eabi-

CC=$(CROSS_COMPILE)/$(CROSS_PREFIX)gcc
LD=$(CROSS_COMPILE)/$(CROSS_PREFIX)ld
OBJCOPY=${CROSS_COMPILE}/${CROSS_PREFIX}objcopy

# Special variables for Cortex-M4F
CPU=-mcpu=cortex-m4
FPU=-mfpu=fpv4-sp-d16 -mfloat-abi=softfp

# Assembler flags
AFLAGS=-mthumb \
       $(CPU)  \
       $(FPU)  \
       -MD

# Include path
IPATH+=-I.
IPATH+=-I./FreeRTOS/Source/portable/GCC/ARM_CM4F
IPATH+=-I./FreeRTOS/Source/include

# GCC C Flags
CFLAGS := -mthumb			\
		$(CPU)				\
		$(FPU)				\
		-Os					\
		-ffunction-sections	\
		-fdata-sections		\
		-MD					\
		-std=c99            \
		-Wall               \
		-pedantic           \
		-DPART_LM4F120H5QR	\
		-c					\
		-DTARGET_IS_BLIZZARD_RA1 \
		$(IPATH)

# Linker flags
LDFLAGS := --gc-sections

LIBGCC := ${shell ${CC} $(CFLAGS) -print-libgcc-file-name}
LIBC := ${shell ${CC} $(CFLAGS) -print-file-name=libc.a}
LIBM := ${shell ${CC} $(CFLAGS) -print-file-name=libm.a}

# Path for pre-built library
# LIBRARY=driverlib/gcc-cm4f/libdriver-cm4f.a
LIB_OBJ := $(shell ls driverlib/*.c | sed -e 's/\.c/\.o/g')

# Object files. Can be added manually or automagically
UTILS_OBJ := $(shell ls utils/*.c | sed -e 's/\.c/\.o/g')

OBJ :=	FreeRTOS/Source/list.o	\
		FreeRTOS/Source/tasks.o	\
		FreeRTOS/Source/queue.o	\
		FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o	\
		FreeRTOS/Source/portable/MemMang/heap_2.o	\
		startup.o	\
		main.o	\
		tinyshell/TinyShell.o	\
		tinyshell/tinyshell_task.o	\
		stellaris_drivers/rgb.o \
		tinyshell/commands/about.o \
		tinyshell/commands/rgbled.o \
		tinyshell/commands/regrw.o \
		tinyshell/commands/memop.o

PROJECT := project

all: $(OBJ) $(UTILS_OBJ) $(LIB_OBJ)
	@echo "Done building object files"
	@echo
	@echo "Linking..."
	${LD} $(LDFLAGS) -T freertos_empty.ld --entry ResetISR \
	$(UTILS_OBJ) $(OBJ) $(LIB_OBJ) '$(LIBM)' '$(LIBC)' '$(LIBGCC)' \
	-o $(PROJECT).axf
	@echo "Done. Generating bin file..."
	${OBJCOPY} -O binary $(PROJECT).axf $(PROJECT).bin
	@echo "Done"

clean:
	@echo "Cleaning object files..."
	@rm -rfv $(OBJ) $(UTILS_OBJ) $(LIB_OBJ)
	@rm -rfv $(shell find . -type f -iname "*.d")
	@rm -rfv $(PROJECT).axf $(PROJECT).bin
	@echo "Done"

