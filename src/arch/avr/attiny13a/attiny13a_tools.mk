CC      := avr-gcc
OBJCOPY := avr-objcopy
SIZE    := avr-size
AVRDUDE := avrdude

PROGRAMMER   ?= usbasp
PORT         ?= 
BAUD         ?=
AVRDUDE_PART ?= t13

LFUSE ?= 0x6A
HFUSE ?= 0xFF

AVRDUDE_PORT_ARG := $(if $(PORT),-P $(PORT),)
AVRDUDE_BAUD_ARG := $(if $(BAUD),-b $(BAUD),)