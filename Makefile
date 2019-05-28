# The name of your project (used to name the compiled .hex file)
TARGET = formula_dash_2019

# The teensy version to use, 30, 31, 32, 35, 36, or LC
TEENSY = 32

# The core speed in MHz to run the teensy at
TEENSY_CORE_SPEED_MHZ = 96

# configurable options
OPTIONS = -DUSB_SERIAL -DLAYOUT_US_ENGLISH -DUSING_MAKEFILE

# directory to build in
BUILDDIR = $(abspath $(CURDIR)/build)

# source directory
SRCPATH = src

# path location for Teensy 3 core
COREPATH = cores/teensy3

# path location for Arduino libraries
LIBRARYPATH = libraries

#************************************************************************
# Settings below this point usually do not need to be edited
#************************************************************************

# CPPFLAGS = compiler options for C and C++
CPPFLAGS = -Wall -g -Os -mthumb -ffunction-sections -fdata-sections -nostdlib -MMD $(OPTIONS) -DF_CPU=$(TEENSY_CORE_SPEED_MHZ)000000 -I$(SRCPATH) -I$(COREPATH)

# compiler options for C++ only
CXXFLAGS = -std=gnu++0x -felide-constructors -fno-exceptions -fno-rtti

# compiler options for C only
CFLAGS =

# linker options
LDFLAGS = -Os -Wl,--gc-sections -mthumb

# additional libraries to link
LIBS = -lm

# compiler options specific to teensy version
ifeq ($(TEENSY), 30)
	MCU = MK20DX128
	MCU_LOWER = mk20dx128
	CPPFLAGS += -D__$(MCU)__ -mcpu=cortex-m4
	LDSCRIPT = $(COREPATH)/$(MCU_LOWER).ld
	LDFLAGS += -mcpu=cortex-m4 -T$(LDSCRIPT)
else ifeq ($(TEENSY), 31)
	MCU = MK20DX256
	MCU_LOWER = mk20dx256
	CPPFLAGS += -D__$(MCU)__ -mcpu=cortex-m4
	LDSCRIPT = $(COREPATH)/$(MCU_LOWER).ld
	LDFLAGS += -mcpu=cortex-m4 -T$(LDSCRIPT)
else ifeq ($(TEENSY), 32)
	MCU = MK20DX256
	MCU_LOWER = mk20dx256
	CPPFLAGS += -D__$(MCU)__ -mcpu=cortex-m4
	LDSCRIPT = $(COREPATH)/$(MCU_LOWER).ld
	LDFLAGS += -mcpu=cortex-m4 -T$(LDSCRIPT)
else ifeq ($(TEENSY), LC)
	MCU = MKL26Z64
	MCU_LOWER = mkl26z64
	CPPFLAGS += -D__$(MCU)__ -mcpu=cortex-m0plus
	LDSCRIPT = $(COREPATH)/$(MCU_LOWER).ld
	LDFLAGS += -mcpu=cortex-m0plus -T$(LDSCRIPT) -L$(abspath $(CURDIR)/cortex)
	LIBS += -larm_cortexM0l_math
else ifeq ($(TEENSY), 35)
	MCU = MK64FX512
	MCU_LOWER = mk64fx512
	CPPFLAGS += -D__$(MCU)__ -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
	LDSCRIPT = $(COREPATH)/$(MCU_LOWER).ld
	LDFLAGS += -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -T$(LDSCRIPT) -L$(abspath $(CURDIR)/cortex)
	LIBS += -larm_cortexM4lf_math
else ifeq ($(TEENSY), 36)
	MCU = MK66FX1M0
	MCU_LOWER = mk66fx1m0
	CPPFLAGS += -D__$(MCU)__ -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
	LDSCRIPT = $(COREPATH)/$(MCU_LOWER).ld
	LDFLAGS += -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -T$(LDSCRIPT) -L$(abspath $(CURDIR)/cortex)
	LIBS += -larm_cortexM4lf_math
else
	$(error Invalid setting for TEENSY)
endif


# names for the compiler programs
CC      = arm-none-eabi-gcc
CXX     = arm-none-eabi-g++
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# automatically create lists of the sources and objects
LC_FILES   := $(wildcard $(LIBRARYPATH)/*/*.c)
LC_FILES   += $(wildcard $(LIBRARYPATH)/*/src/*.c)
LCPP_FILES := $(wildcard $(LIBRARYPATH)/*/*.cpp)
LCPP_FILES += $(wildcard $(LIBRARYPATH)/*/src/*.cpp)
TC_FILES   := $(wildcard $(COREPATH)/*.c)
TCPP_FILES := $(filter-out $(COREPATH)/main.cpp, $(wildcard $(COREPATH)/*.cpp))
C_FILES    := $(wildcard $(SRCPATH)/*.c)
CPP_FILES  := $(wildcard $(SRCPATH)/*.cpp)
INO_FILES  := $(wildcard $(SRCPATH)/*.ino)

# include paths for libraries
L_INC := $(foreach lib,$(filter %/, $(wildcard $(LIBRARYPATH)/*/)), -I$(lib))
L_INC += $(foreach lib,$(filter %/, $(wildcard $(LIBRARYPATH)/*/src/)), -I$(lib))

SOURCES := $(C_FILES:.c=.o) $(CPP_FILES:.cpp=.o) $(INO_FILES:.ino=.o) $(TC_FILES:.c=.o) $(TCPP_FILES:.cpp=.o) $(LC_FILES:.c=.o) $(LCPP_FILES:.cpp=.o)
OBJS    := $(foreach src,$(SOURCES), $(BUILDDIR)/$(src))

all: hex

build: $(BUILDDIR)/$(TARGET).elf

hex: $(BUILDDIR)/$(TARGET).hex

upload: $(BUILDDIR)/$(TARGET).hex
	@teensy_loader_cli -mmcu=$(MCU) -w -v $(BUILDDIR)/$(TARGET).hex

$(BUILDDIR)/%.o: %.c
	@echo -e "[CC]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(L_INC) -o "$@" -c "$<"

$(BUILDDIR)/%.o: %.cpp
	@echo -e "[CXX]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(L_INC) -o "$@" -c "$<"

$(BUILDDIR)/%.o: %.ino
	@echo -e "[CXX]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(L_INC) -o "$@" -x c++ -include Arduino.h -c "$<"

$(BUILDDIR)/$(TARGET).elf: $(OBJS) $(LDSCRIPT)
	@echo -e "[LD]\t$@"
	@$(CC) $(LDFLAGS) -o "$@" $(OBJS) $(LIBS)

%.hex: %.elf
	@echo -e "[HEX]\t$@"
	@$(SIZE) "$<"
	@$(OBJCOPY) -O ihex -R .eeprom "$<" "$@"

# compiler generated dependency info
-include $(OBJS:.o=.d)

clean:
	@rm -rf "$(BUILDDIR)"
