PROJECT ?= copter
ARCH    ?= avr
MCU     ?= attiny44a
F_CPU   ?= 4000000UL

include path_defs.mk

TARGET_DIR   := $(ARCH_DIR)/$(ARCH)/$(MCU)
ARCH_MCU_DIR := $(TARGET_DIR)

ifeq ($(wildcard $(TARGET_DIR)/$(MCU)_builder.mk),)
$(error Unsupported target "$(ARCH)/$(MCU)". File "$(TARGET_DIR)/$(MCU)_builder.mk" not found)
endif

include $(SRC_DIR)/sources.mk
include $(TARGET_DIR)/$(MCU)_sources.mk
include $(TARGET_DIR)/$(MCU)_tools.mk
include $(TARGET_DIR)/$(MCU)_builder.mk