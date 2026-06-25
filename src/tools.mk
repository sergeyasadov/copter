CC      := $(CC_PATH)/avr-gcc
OBJCOPY := $(CC_PATH)/avr-objcopy
SIZE    := $(CC_PATH)/avr-size
AVRDUDE := avrdude

PROGRAMMER   ?= usbasp
PORT         ?=
BAUD         ?=
AVRDUDE_PART ?= t44a

LFUSE ?= 0x6A
HFUSE ?= 0xFF

AVRDUDE_PORT_ARG := $(if $(PORT),-P $(PORT),)
AVRDUDE_BAUD_ARG := $(if $(BAUD),-b $(BAUD),)
