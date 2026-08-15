PROJECT = stm32f103
DEPS_PATH := libs
SOURCE_PATH := src
BUILD_PATH := build
BIN_PATH := bin
MCU := STM32F103xB
MAIN_FILE := main

CMSIS_CORE_PATH := $(DEPS_PATH)/cmsisCore/CMSIS/Core/Include
CMSIS_DRIVER_PATH := $(DEPS_PATH)/cmsisCore/CMSIS/Driver/Include
STM32F1_CMSIS_PATH := $(DEPS_PATH)/cmsisDevice/Include

CC := arm-none-eabi-gcc
CXX := arm-none-eabi-c++
OBJCOPY := arm-none-eabi-objcopy

# DEFINES
DEFINES := -D$(MCU)

# NEEDED FILES
SRC_SYSTEM_FILE := $(DEPS_PATH)/cmsisDevice/Source/Templates/system_stm32f1xx.c
OBJ_SYSTEM_FILE := system_stm32f1xx.o

SRC_STARTUP_FILE := $(DEPS_PATH)/cmsisDevice/Source/Templates/gcc/startup_stm32f103xb.s
OBJ_STARTUP_FILE := startup_stm32f103xb.o

NEEDED_SRC_FILES := $(SRC_STARTUP_FILE) $(SRC_SYSTEM_FILE)
NEEDED_OBJ_FILES := $(BUILD_PATH)/$(OBJ_STARTUP_FILE) $(BUILD_PATH)/$(OBJ_SYSTEM_FILE)

# LINKED
LDSCRIPT := $(DEPS_PATH)/cmsisDevice/Source/Templates/gcc/linker/STM32F103XB_FLASH.ld

# FLAGS
INCLUDE_FLAGS := -I$(CMSIS_CORE_PATH)
INCLUDE_FLAGS += -I$(CMSIS_DRIVER_PATH)
INCLUDE_FLAGS += -I$(STM32F1_CMSIS_PATH)

#ARCH FLAGS
ARCH_FLAGS := -mcpu=cortex-m3
ARCH_FLAGS += -mthumb
# ARCH_FLAGS += -mfloat-abi=softfp
# ARCH_FLAGS += -mfpu=fpv4-sp-d16

DEPFLAGS := -MMD -MP

CXXFLAGS := -std=c++23
CXXFLAGS += $(ARCH_FLAGS)
CXXFLAGS += -O3
CXXFLAGS += -Wall
CXXFLAGS += -Wextra
# CXXFLAGS += -Werror
CXXFLAGS += -fno-exceptions
CXXFLAGS += -fno-rtti
CXXFLAGS += $(DEFINES)
CXXFLAGS += $(DEPFLAGS)
CXXFLAGS += $(INCLUDE_FLAGS)

CFLAGS := -std=c99
CFLAGS += $(ARCH_FLAGS)
CFLAGS += -O3
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += $(DEFINES)
CFLAGS += $(DEPFLAGS)
CFLAGS += $(INCLUDE_FLAGS)

LDFLAGS := -T $(LDSCRIPT)
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -specs=nosys.specs
LDFLAGS += -specs=nano.specs

# FILES
SOURCES := $(wildcard $(SOURCE_PATH)/*.cpp)
OBJECTS := $(patsubst $(SOURCE_PATH)/%.cpp, $(BUILD_PATH)/%.o, $(SOURCES))
DEPS := $(OBJECTS:.o=.d) $(OBJ_SYSTEM_FILE:.o=.d)

$(BIN_PATH)/$(MAIN_FILE).bin: $(BUILD_PATH)/$(MAIN_FILE).elf
	@mkdir -p $(BIN_PATH)
	$(OBJCOPY) -O binary $< $@

$(BUILD_PATH)/$(MAIN_FILE).elf: $(NEEDED_OBJ_FILES) $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(BUILD_PATH)/$(OBJ_STARTUP_FILE): $(SRC_STARTUP_FILE)
	@mkdir -p $(BUILD_PATH)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_PATH)/$(OBJ_SYSTEM_FILE): $(SRC_SYSTEM_FILE)
	@mkdir -p $(BUILD_PATH)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_PATH)/%.o: $(SOURCE_PATH)/%.cpp
	@mkdir -p $(BUILD_PATH)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

-include $(DEPS)

.PHONY: flash
flash: $(BIN_PATH)/$(MAIN_FILE).bin
	st-flash write $< 0x08000000

.PHONY: clean
clean:
	rm -rf $(BIN_PATH)/* $(BUILD_PATH)/*
