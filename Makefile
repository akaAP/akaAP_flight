# Makefile for the compilation and linking of a c++ project for
# the STM32 microcontroller
#
# On command line:
#
# make all = Make software.
# make clean = Clean out built project files.
# make program = Upload load-image to the device
# make filename.s = Just compile filename.c into the assembler code only
# make filename.o = Create object filename.o from filename.c (using CFLAGS)
#
# To rebuild project do "make clean" then "make all".
#
# Changelog:


# Toolchain prefix (i.e arm-elf- -> arm-elf-gcc.exe)
#TCHAIN_PREFIX = arm-eabi-
#TCHAIN_PREFIX = arm-elf-
TCHAIN_PREFIX = arm-none-eabi-
#REMOVE_CMD=rm
REMOVE_CMD=cs-rm


# YES enables -mthumb option to flags for source-files listed 
# in SRC and CPPSRC and -mthumb-interwork option for all source
USE_THUMB_MODE = YES
#USE_THUMB_MODE = NO

# MCU name, submodel and board
# - MCU used for compiler-option (-mcpu)
# - SUBMDL used for linker-script name (-T) and passed as define
MCU      = cortex-m3
CHIP     = STM32F10x_512k_64k
F_XTAL   = 8000000
SYSCLOCK_CL = SYSCLK_FREQ_72MHz=72000000

# *** This example only supports "FLASH_RUN" ***
# RUN_MODE is passed as define and used for the linker-script filename,
# the user has to implement the necessary operations for 
# the used mode(s) (i.e. no copy of .data, remapping)
# Create FLASH-Image
RUN_MODE=FLASH_RUN
# Create RAM-Image
#RUN_MODE=RAM_RUN

# Directory for output files (lst, obj, dep, elf, sym, map, hex, bin etc.)
OUTPUT_DIRECTORY = ./bin

# Target file name (without extension).
TARGET = main

# define Paths
CODE_DIRECTORY = ./code

APPLICATIONCODE_DIRECTORY = $(CODE_DIRECTORY)/application/
HARDWARE_ABSTRACTION_CODE_DIRECTORY = ./code/application/HardwareAbstractionLayer
HARDWARE_ABSTRACTION_DRIVERS_CODE_DIRECTORY = ./code/application/HardwareAbstractionLayer/deviceDrivers

LIBRARIES_DIRECTORY = $(CODE_DIRECTORY)/libraries
CPP_LIB_DIRECTORY = $(LIBRARIES_DIRECTORY)/CPP
CPP_LIB_SRC_DIRECTORY = $(CPP_LIB_DIRECTORY)/src
CPP_LIB_INC_DIRECTORY = $(CPP_LIB_DIRECTORY)/inc
CMSIS_DIRECTORY  = $(LIBRARIES_DIRECTORY)/CMSIS/CM3/CoreSupport

# List C source files here. (C dependencies are automatically generated.)
# use file-extension c for "c-only"-files
SRC = syscalls.c 
## CMSIS for STM32
SRC += $(CMSIS_DIRECTORY)/core_cm3.c
SRC += $(APPLICATIONCODE_DIRECTORY)/src/startup_highDensity.c
SRC += $(HARDWARE_ABSTRACTION_CODE_DIRECTORY)/src/term_io.c
SRC += $(HARDWARE_ABSTRACTION_CODE_DIRECTORY)/src/comm.c

## -c.files of the of the stm32Library
#SRC += $(STM32_LIBRARY_SRC_DIRECTORY)/misc.c

# List C source files here which must be compiled in ARM-Mode (no -mthumb).
# use file-extension c for "c-only"-files
SRCARM = 

# List C++ source files here.
# use file-extension .cpp for C++-files (not .C)
# application .cpp sources
CPPSRC = $(APPLICATIONCODE_DIRECTORY)/src/main.cpp

#CPPSRC += $(APPLICATIONCODE_DIRECTORY)/src/stm32.cpp
CPPSRC += $(APPLICATIONCODE_DIRECTORY)/src/init.cpp
CPPSRC += $(APPLICATIONCODE_DIRECTORY)/src/test.cpp
CPPSRC += $(APPLICATIONCODE_DIRECTORY)/src/CANTestcase.cpp

#CPPSRC += $(APPLICATIONCODE_DIRECTORY)/src/startup.c
#CPPSRC += $(APPLICATIONCODE_DIRECTORY)/src/startup_stm32f10x_md_mthomas.cpp


CPPSRC += $(HARDWARE_ABSTRACTION_DRIVERS_CODE_DIRECTORY)/src/deviceDriver_spektrumSatellite.cpp
CPPSRC += $(HARDWARE_ABSTRACTION_DRIVERS_CODE_DIRECTORY)/src/deviceDriver_XBee.cpp
#CPPSRC += $(HARDWARE_ABSTRACTION_DRIVERS_CODE_DIRECTORY)/src/deviceDriver_IMUchr6d.cpp
CPPSRC += $(HARDWARE_ABSTRACTION_DRIVERS_CODE_DIRECTORY)/src/deviceDriver_LED_CPP.cpp
CPPSRC += $(HARDWARE_ABSTRACTION_DRIVERS_CODE_DIRECTORY)/src/deviceDriver_pwmServoBank.cpp
#CPPSRC += $(HARDWARE_ABSTRACTION_DRIVERS_CODE_DIRECTORY)/src/deviceDriver_VoltageRegulator.cpp
CPPSRC += $(HARDWARE_ABSTRACTION_DRIVERS_CODE_DIRECTORY)/src/devices.cpp 

CPPSRC += $(HARDWARE_ABSTRACTION_CODE_DIRECTORY)/src/Modules.cpp 
CPPSRC += $(HARDWARE_ABSTRACTION_CODE_DIRECTORY)/src/SerialPort.cpp
CPPSRC += $(HARDWARE_ABSTRACTION_CODE_DIRECTORY)/src/GroundLink.cpp
CPPSRC += $(HARDWARE_ABSTRACTION_CODE_DIRECTORY)/src/UAVTalk.cpp
CPPSRC += $(HARDWARE_ABSTRACTION_CODE_DIRECTORY)/src/MAVLink.cpp
CPPSRC += $(HARDWARE_ABSTRACTION_CODE_DIRECTORY)/src/pios_crc.cpp
CPPSRC += $(HARDWARE_ABSTRACTION_CODE_DIRECTORY)/src/NodeLink.cpp
CPPSRC += $(HARDWARE_ABSTRACTION_CODE_DIRECTORY)/src/CanTest.cpp
CPPSRC += $(HARDWARE_ABSTRACTION_CODE_DIRECTORY)/src/TxMailbox.cpp
CPPSRC += $(HARDWARE_ABSTRACTION_CODE_DIRECTORY)/src/timebase.cpp 
CPPSRC += $(HARDWARE_ABSTRACTION_CODE_DIRECTORY)/src/InterruptManager.cpp 
##CPPSRC += $(APPLICATION_CODE_DIRECTORY)/src/serialPort_example.c 
CPPSRC += $(HARDWARE_ABSTRACTION_CODE_DIRECTORY)/src/serviceFunctions.cpp 
CPPSRC += $(HARDWARE_ABSTRACTION_CODE_DIRECTORY)/examples/src/SerialPort_example.cpp

CPPSRC += $(CPP_LIB_SRC_DIRECTORY)/mini_cpp.cpp

# List C++ source files here which must be compiled in ARM-Mode.
# use file-extension .cpp for C++-files (not .C)
#CPPSRCARM = $(TARGET).cpp

# List Assembler source files here.
# Make them always end in a capital .S. Files ending in a lowercase .s
# will not be considered source files but generated files (assembler
# output from the compiler), and will be deleted upon "make clean"!
# Even though the DOS/Win* filesystem matches both .s and .S the same,
# it will preserve the spelling of the filenames, and gcc itself does
# care about how the name is spelled on its command-line.
ASRC = 

# List Assembler source files here which must be assembled in ARM-Mode..
ASRCARM  =

# List any extra directories to look for include files here.
#    Each directory must be seperated by a space.
EXTRAINCDIRS  = $(STM32_LIBRARY_INC_DIRECTORY) $(CMSIS_DIRECTORY) $(FATSDDIR) $(MININIDIR) $(STMEEEMULINCDIR)
EXTRAINCDIRS += $(CODE_DIRECTORY) $(SWIMSRCDIR)

# Extra libraries
#    Each library-name must be seperated by a space.
#    i.e. to link with libxyz.a, libabc.a and libefsl.a: 
#    EXTRA_LIBS = xyz abc efsl
# for newlib-lpc (file: libnewlibc-lpc.a):
#    EXTRA_LIBS = newlib-lpc
EXTRA_LIBS = c gcc m STM32DriverLib

# Path to Linker-Scripts
LINKERSCRIPTPATH = ./linkerskripts
LINKERSCRIPTINC  = ./

# List any extra directories to look for library files here.
# Also add directories where the linker should search for
# includes from linker-script to the list
#     Each directory must be seperated by a space.
EXTRA_LIBDIRS = $(LINKERSCRIPTINC) $(LIBRARIES_DIRECTORY)

# Optimization level, can be [0, 1, 2, 3, s]. 
# 0 = turn off optimization. s = optimize for size.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
#OPT = s
OPT = 2
#OPT = 3

#OPT = 0

# Output format. (can be ihex or binary or both)
#  binary to create a load-image in raw-binary format i.e. for SAM-BA, 
#  ihex to create a load-image in Intel hex format i.e. for lpc21isp
#LOADFORMAT = ihex
#LOADFORMAT = binary
LOADFORMAT = both

# Using the Atmel AT91_lib produces warnings with
# the default warning-levels. 
#  yes - disable these warnings
#  no  - keep default settings
#AT91LIBNOWARN = yes
AT91LIBNOWARN = no

# Debugging format.
#DEBUG = stabs
DEBUG = dwarf-2

# Place project-specific -D (define) and/or 
# -U options for C here.
CDEFS = -DHSE_VALUE=$(F_XTAL)UL
CDEFS += -D$(SYSCLOCK_CL)
CDEFS += -DUSE_STDPERIPH_DRIVER
CDEFS += -DSTM32_SD_USE_DMA
CDEFS += -DSTARTUP_DELAY
# enable modifications in STM's libraries
CDEFS += -DMOD_MTHOMAS_STMLIB
# enable parameter-checking in STM's library
CDEFS += -DUSE_FULL_ASSERT

# Place project-specific -D and/or -U options for 
# Assembler with preprocessor here.
#ADEFS = -DUSE_IRQ_ASM_WRAPPER
ADEFS = -D__ASSEMBLY__

# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99

#-----

CDEFS += -D$(RUN_MODE) -D$(CHIP)
ADEFS += -D$(RUN_MODE) -D$(CHIP)


# Compiler flags.

ifeq ($(USE_THUMB_MODE),YES)
THUMB    = -mthumb
THUMB_IW = -mthumb-interwork
else 
THUMB    = 
THUMB_IW = 
endif

#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
#
# Flags for C and C++ (arm-elf-gcc/arm-elf-g++)
CFLAGS =  -g$(DEBUG)
CFLAGS += -O$(OPT)
CFLAGS += -mcpu=$(MCU) $(THUMB_IW) 
CFLAGS += $(CDEFS)
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS)) -I.
# when using ".ramfunc"s without longcall:
CFLAGS += -mlong-calls
# -mapcs-frame is important if gcc's interrupt attributes are used
# (at least from my eabi tests), not needed if assembler-wrapper is used 
#CFLAGS += -mapcs-frame 
#CFLAGS += -fomit-frame-pointer
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -fpromote-loop-indices
CFLAGS += -Wall -Wextra
CFLAGS += -msoft-float
CFLAGS += -Wimplicit -Wcast-align -Wpointer-arith
CFLAGS += -Wredundant-decls -Wshadow -Wcast-qual -Wcast-align
#CFLAGS += -pedantic
CFLAGS += -Wa,-adhlns=$(addprefix $(OUTPUT_DIRECTORY)/, $(notdir $(addsuffix .lst, $(basename $<))))
# Compiler flags to generate dependency files:
CFLAGS += -MD -MP -MF $(OUTPUT_DIRECTORY)/dep/$(@F).d

# flags only for C
CONLYFLAGS += -Wnested-externs 
CONLYFLAGS += $(CSTANDARD)

ifeq ($(AT91LIBNOWARN),yes)
# compiling the old single-file AT91-lib thows warnings with the followins 
# settings so they are enabled only if AT91LIBNOWARN is set to "yes"
CFLAGS += -Wno-cast-qual
CONLYFLAGS += -Wno-missing-prototypes 
CONLYFLAGS += -Wno-strict-prototypes
CONLYFLAGS += -Wno-missing-declarations
endif

# flags only for C++ (arm-*-g++)
CPPFLAGS = -fno-rtti -fno-exceptions -Wno-pmf-conversions -msoft-float

# Assembler flags.
#  -Wa,...:    tell GCC to pass this to the assembler.
#  -ahlns:     create listing
#  -g$(DEBUG): have the assembler create line number information
ASFLAGS  = -mcpu=$(MCU) $(THUMB_IW) -I. -x assembler-with-cpp
ASFLAGS += $(ADEFS)
ASFLAGS += -Wa,-adhlns=$(addprefix $(OUTPUT_DIRECTORY)/, $(notdir $(addsuffix .lst, $(basename $<))))
ASFLAGS += -Wa,-g$(DEBUG)
ASFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))

MATH_LIB = -lm

# Link with the GNU C++ stdlib.
CPLUSPLUS_LIB = -lstdc++
#CPLUSPLUS_LIB += -lsupc++

# Linker flags.
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS = -Wl,-Map=$(OUTPUT_DIRECTORY)/$(TARGET).map,--cref,--gc-sections
#not in CPP
#LDFLAGS += -nostartfiles
LDFLAGS += -lc
LDFLAGS += $(MATH_LIB)
LDFLAGS += -lc -lgcc
LDFLAGS += $(CPLUSPLUS_LIB)
LDFLAGS += $(patsubst %,-L%,$(EXTRA_LIBDIRS))
LDFLAGS += $(patsubst %,-l%,$(EXTRA_LIBS)) 

# Set linker-script name depending on selected run-mode and submodel name
ifeq ($(RUN_MODE),RAM_RUN)
##LDFLAGS +=-T$(LINKERSCRIPTPATH)/$(CHIP)_ram.ld
##LDFLAGS +=-T$(LINKERSCRIPTPATH)/sram.lds
else 
LDFLAGS +=-T$(LINKERSCRIPTPATH)/$(CHIP)_flash.ld
##LDFLAGS +=-T$(LINKERSCRIPTPATH)/flash.lds
endif


# Define programs and commands.
CC      = $(TCHAIN_PREFIX)gcc
CPP     = $(TCHAIN_PREFIX)g++
AR      = $(TCHAIN_PREFIX)ar
OBJCOPY = $(TCHAIN_PREFIX)objcopy
OBJDUMP = $(TCHAIN_PREFIX)objdump
SIZE    = $(TCHAIN_PREFIX)size
NM      = $(TCHAIN_PREFIX)nm
REMOVE  = $(REMOVE_CMD) -f
SHELL   = sh
###COPY    = cp
ifneq ($(or $(COMSPEC), $(ComSpec)),)
$(info COMSPEC detected $(COMSPEC) $(ComSpec))
ifeq ($(findstring cygdrive,$(shell env)),)
SHELL:=$(or $(COMSPEC),$(ComSpec))
SHELL_IS_WIN32=1
else
$(info cygwin detected)
endif
endif
$(info SHELL is $(SHELL))

# Define Messages
# English
MSG_ERRORS_NONE = Errors: none
MSG_BEGIN = --------  begin, mode: $(RUN_MODE)  --------
MSG_END = --------  end  --------
MSG_SIZE_BEFORE = Size before: 
MSG_SIZE_AFTER = Size after build:
MSG_LOAD_FILE = Creating load file:
MSG_EXTENDED_LISTING = Creating Extended Listing/Disassembly:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = ---- Linking :
MSG_COMPILING = ---- Compiling C :
MSG_COMPILING_ARM = ---- Compiling C ARM-only:
MSG_COMPILINGCPP = ---- Compiling C++ :
MSG_COMPILINGCPP_ARM = ---- Compiling C++ ARM-only:
MSG_ASSEMBLING = ---- Assembling:
MSG_ASSEMBLING_ARM = ---- Assembling ARM-only:
MSG_CLEANING = Cleaning project:
MSG_FORMATERROR = Can not handle output-format
MSG_LPC21_RESETREMINDER = You may have to bring the target in bootloader-mode now.
MSG_ASMFROMC = "Creating asm-File from C-Source:"
MSG_ASMFROMC_ARM = "Creating asm-File from C-Source (ARM-only):"

# List of all source files.
ALLSRC     = $(ASRCARM) $(ASRC) $(SRCARM) $(SRC) $(CPPSRCARM) $(CPPSRC)
# List of all source files without directory and file-extension.
ALLSRCBASE = $(notdir $(basename $(ALLSRC)))

# Define all object files.
ALLOBJ     = $(addprefix $(OUTPUT_DIRECTORY)/, $(addsuffix .o, $(ALLSRCBASE)))

# Define all listing files (used for make clean).
LSTFILES   = $(addprefix $(OUTPUT_DIRECTORY)/, $(addsuffix .lst, $(ALLSRCBASE)))
# Define all depedency-files (used for make clean).
DEPFILES   = $(addprefix $(OUTPUT_DIRECTORY)/dep/, $(addsuffix .o.d, $(ALLSRCBASE)))

# Default target.
#all: begin gccversion sizebefore build sizeafter finished end
all: begin createdirs gccversion g++version build sizeafter finished end

elf: $(OUTPUT_DIRECTORY)/$(TARGET).elf
lss: $(OUTPUT_DIRECTORY)/$(TARGET).lss 
sym: $(OUTPUT_DIRECTORY)/$(TARGET).sym
hex: $(OUTPUT_DIRECTORY)/$(TARGET).hex
bin: $(OUTPUT_DIRECTORY)/$(TARGET).bin


ifeq ($(LOADFORMAT),ihex)
build: elf hex lss sym
else 
ifeq ($(LOADFORMAT),binary)
build: elf bin lss sym
else 
ifeq ($(LOADFORMAT),both)
build: elf hex bin lss sym
else 
$(error "$(MSG_FORMATERROR) $(FORMAT)")
endif
endif
endif

# Create output directories.
ifdef SHELL_IS_WIN32
createdirs:
	-@md $(OUTPUT_DIRECTORY) >NUL 2>&1 || echo "" >NUL
	-@md $(OUTPUT_DIRECTORY)\dep >NUL 2>&1 || echo "" >NUL
else
createdirs:
	-@mkdir $(OUTPUT_DIRECTORY) 2>/dev/null || echo "" >/dev/null
	-@mkdir $(OUTPUT_DIRECTORY)/dep 2>/dev/null || echo "" >/dev/null
endif

# Eye candy.
begin:
	@echo $(MSG_BEGIN)

finished:
##	@echo $(MSG_ERRORS_NONE)

end:
	@echo $(MSG_END)

# Display sizes of sections.
ELFSIZE = $(SIZE) -A  $(OUTPUT_DIRECTORY)/$(TARGET).elf
##ELFSIZE = $(SIZE) --format=Berkeley --common $(OUTPUT_DIRECTORY)/$(TARGET).elf
sizebefore:
#	@if [ -f  $(OUTPUT_DIRECTORY)/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(ELFSIZE); echo; fi

sizeafter:
#	@if [ -f  $(OUTPUT_DIRECTORY)/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_AFTER); $(ELFSIZE); echo; fi
	@echo $(MSG_SIZE_AFTER)
	$(ELFSIZE)
	
# Display gcc compiler version information.
gccversion : 
	@$(CC) --version
#	@echo $(ALLOBJ)

# Display g++ compiler version information.
g++version : 
	@$(CPP) --version
#	@echo $(ALLOBJ)


# Create final output file (.hex) from ELF output file.
%.hex: %.elf
	@echo $(MSG_LOAD_FILE) $@
	$(OBJCOPY) -O ihex $< $@
	
# Create final output file (.bin) from ELF output file.
%.bin: %.elf
	@echo $(MSG_LOAD_FILE) $@
	$(OBJCOPY) -O binary $< $@

# Create extended listing file/disassambly from ELF output file.
# using objdump testing: option -C
%.lss: %.elf
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S -C -r $< > $@
#	$(OBJDUMP) -x -S $< > $@

# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo $(MSG_SYMBOL_TABLE) $@
	$(NM) -n $< > $@

# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(ALLOBJ)
%.elf:  $(ALLOBJ)
	@echo $(MSG_LINKING) $@
# use $(CC) for C-only projects or $(CPP) for C++-projects:
ifeq "$(strip $(CPPSRC)$(CPPARM))" ""
	$(CC) $(THUMB) $(CFLAGS) $(ALLOBJ) --output $@ -nostartfiles $(LDFLAGS)
else
	$(CPP) $(THUMB) $(CFLAGS) $(ALLOBJ) --output $@ $(LDFLAGS)
endif


# Assemble: create object files from assembler source files.
define ASSEMBLE_TEMPLATE
$(OUTPUT_DIRECTORY)/$(notdir $(basename $(1))).o : $(1)
	@echo "hallo"
	@echo $(MSG_ASSEMBLING) $$< to $$@
	$(CC) -c $(THUMB) $$(ASFLAGS) $$< -o $$@ 
endef
$(foreach src, $(ASRC), $(eval $(call ASSEMBLE_TEMPLATE, $(src)))) 

# Assemble: create object files from assembler source files. ARM-only
define ASSEMBLE_ARM_TEMPLATE
$(OUTPUT_DIRECTORY)/$(notdir $(basename $(1))).o : $(1)
	@echo $(MSG_ASSEMBLING_ARM) $$< to $$@
	$(CC) -c $$(ASFLAGS) $$< -o $$@ 
endef
$(foreach src, $(ASRCARM), $(eval $(call ASSEMBLE_ARM_TEMPLATE, $(src)))) 


# Compile: create object files from C source files.
define COMPILE_C_TEMPLATE
$(OUTPUT_DIRECTORY)/$(notdir $(basename $(1))).o : $(1)
	@echo $(MSG_COMPILING) $$< to $$@
	$(info using gcc)
	$(CC) -c $(THUMB) $$(CFLAGS) $$(CONLYFLAGS) $$< -o $$@ 
endef
$(foreach src, $(SRC), $(eval $(call COMPILE_C_TEMPLATE, $(src)))) 

# Compile: create object files from C source files. ARM-only
define COMPILE_C_ARM_TEMPLATE
$(OUTPUT_DIRECTORY)/$(notdir $(basename $(1))).o : $(1)
	@echo $(MSG_COMPILING_ARM) $$< to $$@
	$(info using gcc ARM-only)	
	$(CC) -c $$(CFLAGS) $$(CONLYFLAGS) $$< -o $$@ 
endef
$(foreach src, $(SRCARM), $(eval $(call COMPILE_C_ARM_TEMPLATE, $(src)))) 


# Compile: create object files from C++ source files.
define COMPILE_CPP_TEMPLATE
$(OUTPUT_DIRECTORY)/$(notdir $(basename $(1))).o : $(1)
	$(info using g++)
	@echo $(MSG_COMPILINGCPP) $$< to $$@
	$(CPP) -c $(THUMB) $$(CFLAGS) $$(CPPFLAGS) $$< -o $$@ 
endef
$(foreach src, $(CPPSRC), $(eval $(call COMPILE_CPP_TEMPLATE, $(src)))) 

# Compile: create object files from C++ source files. ARM-only
define COMPILE_CPP_ARM_TEMPLATE
$(OUTPUT_DIRECTORY)/$(notdir $(basename $(1))).o : $(1)
	@echo $(MSG_COMPILINGCPP_ARM) $$< to $$@
	$(CC) -c $$(CFLAGS) $$(CPPFLAGS) $$< -o $$@ 
endef
$(foreach src, $(CPPSRCARM), $(eval $(call COMPILE_CPP_ARM_TEMPLATE, $(src)))) 


# Compile: create assembler files from C source files. ARM/Thumb
$(SRC:.c=.s) : %.s : %.c
	@echo $(MSG_ASMFROMC) $< to $@
	$(CC) $(THUMB) -S $(CFLAGS) $(CONLYFLAGS) $< -o $@

# Compile: create assembler files from C source files. ARM only
$(SRCARM:.c=.s) : %.s : %.c
	@echo $(MSG_ASMFROMC_ARM) $< to $@
	$(CC) -S $(CFLAGS) $(CONLYFLAGS) $< -o $@

# Target: clean project.
clean: begin clean_list finished end

clean_list :
	@echo $(MSG_CLEANING)
	$(REMOVE) $(OUTPUT_DIRECTORY)/$(TARGET).map
	$(REMOVE) $(OUTPUT_DIRECTORY)/$(TARGET).elf
	$(REMOVE) $(OUTPUT_DIRECTORY)/$(TARGET).hex
	$(REMOVE) $(OUTPUT_DIRECTORY)/$(TARGET).bin
	$(REMOVE) $(OUTPUT_DIRECTORY)/$(TARGET).sym
	$(REMOVE) $(OUTPUT_DIRECTORY)/$(TARGET).lss
	$(REMOVE) $(ALLOBJ)
	$(REMOVE) $(LSTFILES)
	$(REMOVE) $(DEPFILES)
	#$(REMOVE) $(SRC:.c=.s)			//before commenting this line startup.c was removed by 'make clean'
	$(REMOVE) $(SRCARM:.c=.s)
	$(REMOVE) $(CPPSRC:.cpp=.s)
	$(REMOVE) $(CPPSRCARM:.cpp=.s)

## Create object files directory - now done if special make target
##$(shell mkdir $(OBJDIR) 2>/dev/null)

# Include the dependency files.
##-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)
-include $(wildcard dep/*)

# Listing of phony targets.
.PHONY : all begin finish end sizebefore sizeafter gccversion \
build elf hex bin lss sym clean clean_list program createdirs

