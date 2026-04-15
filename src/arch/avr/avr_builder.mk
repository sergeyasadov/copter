.DEFAULT_GOAL := all

SOURCES := $(SRC_COMMON) $(SRC_ARCH)

OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
DEPS    := $(OBJECTS:.o=.d)

TARGET_ELF := $(BIN_DIR)/$(PROJECT)_$(MCU).elf
TARGET_HEX := $(BIN_DIR)/$(PROJECT)_$(MCU).hex
TARGET_MAP := $(BIN_DIR)/$(PROJECT)_$(MCU).map


ifeq ($(OS),Windows_NT)
	SHELL := cmd.exe
	.SHELLFLAGS := /C

	fixpath   = $(subst /,\,$(1))
	make_dir  = if not exist "$(call fixpath,$(1))" mkdir "$(call fixpath,$(1))"
	remove_dir = if exist "$(call fixpath,$(1))" rmdir /S /Q "$(call fixpath,$(1))"
else
	make_dir   = mkdir -p "$(1)"
	remove_dir = rm -rf "$(1)"
endif


CPPFLAGS += \
	$(INC_COMMON) \
	$(INC_ARCH) \
	-DF_CPU=$(F_CPU)

CFLAGS += \
	-mmcu=$(MCU) \
	-std=c99 \
	-Os \
	-Wall \
	-Wextra \
	-Wpedantic \
	-ffunction-sections \
	-fdata-sections \
	-MMD \
	-MP

LDFLAGS += \
	-mmcu=$(MCU) \
	-Wl,--gc-sections \
	-Wl,-Map=$(TARGET_MAP)

.PHONY: all clean flash fuses size print-config

all: $(TARGET_HEX)

$(TARGET_HEX): $(TARGET_ELF)
	@$(call make_dir,$(dir $@))
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	$(SIZE) $<

$(TARGET_ELF): $(OBJECTS)
	@$(call make_dir,$(dir $@))
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(call make_dir,$(dir $@))
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

flash: $(TARGET_HEX)
	$(AVRDUDE) -c $(PROGRAMMER) -p $(AVRDUDE_PART) $(AVRDUDE_PORT_ARG) $(AVRDUDE_BAUD_ARG) \
		-U flash:w:$(TARGET_HEX):i

fuses:
	$(AVRDUDE) -c $(PROGRAMMER) -p $(AVRDUDE_PART) $(AVRDUDE_PORT_ARG) \
		-U lfuse:w:$(LFUSE):m \
		-U hfuse:w:$(HFUSE):m

size: $(TARGET_ELF)
	$(SIZE) $(TARGET_ELF)

clean:
	@$(call remove_dir,$(BUILD_DIR))
	@$(call remove_dir,$(BIN_DIR))

print-config:
	@echo PROJECT      = $(PROJECT)
	@echo ARCH         = $(ARCH)
	@echo MCU          = $(MCU)
	@echo F_CPU        = $(F_CPU)
	@echo TARGET_DIR   = $(TARGET_DIR)
	@echo SOURCES      = $(SOURCES)
	@echo OBJECTS      = $(OBJECTS)
	@echo CC           = $(CC)
	@echo PROGRAMMER   = $(PROGRAMMER)
	@echo AVRDUDE_PART = $(AVRDUDE_PART)
	@echo OS           = $(OS)

-include $(DEPS)