.DEFAULT_GOAL := all

SOURCES := $(SRC_COMMON) $(SRC_ARCH)

OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
DEPS    := $(OBJECTS:.o=.d)

TARGET_ELF := $(BIN_DIR)/$(PROJECT)_$(MCU).elf
TARGET_HEX := $(BIN_DIR)/$(PROJECT)_$(MCU).hex
TARGET_MAP := $(BIN_DIR)/$(PROJECT)_$(MCU).map

CPPFLAGS += \
	$(INC_COMMON) \
	$(INC_ARCH) \
	-DF_CPU=$(F_CPU)

CFLAGS += \
	-mmcu=$(MCU) \
	-std=c11 \
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
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O ihex -R .eeprom $< $@
	$(SIZE) $<

$(TARGET_ELF): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
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
	rm -rf $(BUILD_DIR) $(BIN_DIR)

print-config:
	@echo "PROJECT      = $(PROJECT)"
	@echo "ARCH         = $(ARCH)"
	@echo "MCU          = $(MCU)"
	@echo "F_CPU        = $(F_CPU)"
	@echo "TARGET_DIR   = $(TARGET_DIR)"
	@echo "SOURCES      = $(SOURCES)"
	@echo "OBJECTS      = $(OBJECTS)"
	@echo "CC           = $(CC)"
	@echo "PROGRAMMER   = $(PROGRAMMER)"
	@echo "AVRDUDE_PART = $(AVRDUDE_PART)"

-include $(DEPS)