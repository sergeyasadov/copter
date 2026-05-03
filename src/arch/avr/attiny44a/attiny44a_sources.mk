SRC_ARCH := \
	$(ARCH_MCU_DIR)/gpio.c \
	$(ARCH_MCU_DIR)/pwm.c \
	$(ARCH_MCU_DIR)/adc.c \
	$(ARCH_MCU_DIR)/uart.c \
	$(ARCH_MCU_DIR)/twi.c


INC_ARCH := \
	-I$(ARCH_MCU_DIR)