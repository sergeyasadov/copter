PROJECT ?= copter
ARCH    ?= avr
MCU     ?= attiny44a
F_CPU   ?= 1000000UL

SRC_DIR   := src

BIN_DIR   := bin
BUILD_DIR := build
OBJ_DIR   := $(BUILD_DIR)/obj

include ${SRC_DIR}/sources.mk
include ${SRC_DIR}/tools.mk
include ${SRC_DIR}/builder.mk