PROJECT ?= copter
ARCH    ?= avr
MCU     ?= attiny44a
F_CPU   ?= 4000000UL

include path_defs.mk

TARGET_DIR   := $(ARCH_DIR)/$(ARCH)
ARCH_MCU_DIR := $(TARGET_DIR)/$(MCU)

ifeq ($(wildcard $(TARGET_DIR)/$(ARCH)_builder.mk),)
$(error Unsupported target "$(ARCH)/$(MCU)". File "$(TARGET_DIR)/$(ARCH)_builder.mk" not found)
endif

include $(SRC_DIR)/sources.mk
include $(TARGET_DIR)/$(MCU)/$(MCU)_sources.mk
include $(TARGET_DIR)/$(ARCH)_tools.mk
include $(TARGET_DIR)/$(ARCH)_builder.mk