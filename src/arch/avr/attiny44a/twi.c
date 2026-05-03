#include "twi.h"

#define PRIVATE_FUNC(__FUNC) \
    static __ATTR_ALWAYS_INLINE__ __FUNC(void)


static TWI_t TWI0;
static uint8_t TWI0_ACK;
static uint8_t TWI0_WRITE_BIT;


void PRIVATE_FUNC(twi_delay) {
    delayUs(5);
}


void PRIVATE_FUNC(twi_sda_low) {
    GPIO_SetLow(&TWI0.sda);
    GPIO_SetDir(&TWI0.sda, GPIO_DIR_OUTPUT);
}


void PRIVATE_FUNC(twi_sda_release) {
    GPIO_SetDir(&TWI0.sda, GPIO_DIR_INPUT);
}


uint8_t PRIVATE_FUNC(twi_sda_read) {
    return GPIO_Read(&TWI0.sda);
}


void PRIVATE_FUNC(twi_scl_low) {
    GPIO_SetLow(&TWI0.scl);
    GPIO_SetDir(&TWI0.scl, GPIO_DIR_OUTPUT);
}


void PRIVATE_FUNC(twi_scl_release) {
    GPIO_SetDir(&TWI0.scl, GPIO_DIR_INPUT);
}


uint8_t PRIVATE_FUNC(twi_scl_read) {
    return GPIO_Read(&TWI0.scl);
}


void PRIVATE_FUNC(twi_start) {
    twi_sda_release();
    twi_scl_release();
    twi_delay();
    twi_sda_low();
    twi_delay();
    twi_scl_low();
}


void PRIVATE_FUNC(twi_stop) {
    twi_sda_low();
    twi_delay();
    twi_scl_release();
    twi_delay();
    twi_sda_release();
    twi_delay();
}


void PRIVATE_FUNC(twi_write_bit) {
    if(TWI0_WRITE_BIT) {
        twi_sda_release();
    }
    else {
        twi_sda_low();
    }
    TWI0_WRITE_BIT = 0;

    twi_delay();
    twi_scl_release();
    twi_delay();
    twi_scl_low();
    twi_delay();
}


uint8_t PRIVATE_FUNC(twi_read_bit) {
    register uint8_t bit;

    twi_sda_release();
    twi_delay();
    twi_scl_release();
    twi_delay();
    bit = twi_sda_read();
    twi_scl_low();
    twi_delay();

    return bit;
}



void TWI_Init(TWI_t* twi) {
    twi->sda.dir = GPIO_DIR_INPUT;
    twi->scl.dir = GPIO_DIR_OUTPUT;
    TWI0.scl = twi->scl;
    TWI0.sda = twi->sda;

    twi_sda_release();
    twi_sda_release();

    twi_delay();
}


void TWI_WriteByte(const uint8_t byte) {
    for(register uint8_t mask = 0x80; mask; mask >>= 1) {
        TWI0_WRITE_BIT = byte & mask;
        twi_write_bit();
    }
    TWI0_ACK = twi_read_bit();

    // return (TWI0_ACK == 0); 
    // ACK == 1
    // NACK == 0
}


uint8_t TWI_ReadByte(const uint8_t ack) {
    uint8_t byte = 0;
    
    for(uint8_t i = 0; i < 8; i++) {
        byte <<= 1;

        if(twi_read_bit()) {
            byte |= 1;
        }
    }

   if(ack) {
        TWI0_WRITE_BIT = ack;
        twi_write_bit();
   } 
   else {
        TWI0_WRITE_BIT = ack;
        twi_write_bit();
   }

   return byte;
}