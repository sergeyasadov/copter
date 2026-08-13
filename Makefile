PROJECT ?= copter
ARCH    ?= avr
MCU     ?= attiny44a
F_CPU   ?=
TYPE 	?= rx

ifeq ($(TYPE), tx)
	F_CPU = 20000000UL
else
	F_CPU = 8000000UL
endif

SRC_DIR   := src

BIN_DIR   := bin
BUILD_DIR := build
OBJ_DIR   := $(BUILD_DIR)/obj

// WARNING:
ROOT_DIR  := /Users/cogitary/Desktop/Devs/COMPILERS/avr8-toolchain
CC_PATH   := $(ROOT_DIR)/bin
STD_PATH  := $(ROOT_DIR)/avr/include

include ${SRC_DIR}/sources.mk
include ${SRC_DIR}/tools.mk
include ${SRC_DIR}/builder.mk
