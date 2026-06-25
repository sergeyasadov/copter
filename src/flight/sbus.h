#ifndef __SBUS_H__
#define __SBUS_H__

#include "defines.h"
#include "sys/gpio.h"

#define SBUS_DDR DDRA
#define SBUS_PORT PORTA
#define SBUS_PIN PINA
#define SBUS_BIT PA1
#define SBUS_PIN_MASK (1 << SBUS_BIT)
#define SBUS_NUM_CHANNELS 16
#define SBUS_OCR_HALF_BIT 99
#define SBUS_OCR_FULL_BIT 199
#define SBUS_TIMOUT 360 // 12 * 30

enum sbus_state_t {
    SBUS_STATE_WAIT_FALLING = 0,
    SBUS_STATE_SYNC_START,
    SBUS_STATE_RECEIVING
};

static uint16_t __sbus_channels[SBUS_NUM_CHANNELS];
volatile bool __sbus_new_frame = false;
static uint8_t __sbus_state;
static uint8_t __sbus_flags;
static uint8_t __sbus_current_byte;
static uint16_t __sbus_sample_count;
static uint16_t __sbus_timeout_count;
static uint8_t __sbus_bit_pos;

static uint8_t __sbus_frame_buf[25];
static int8_t __sbus_frame_index = -1;


static __inline__ void SBUS_Init(void) {
    SBUS_DDR &= ~(1 << SBUS_BIT);
    SBUS_PORT |= (1 << SBUS_BIT);

    PCMSK0 |= (1 << PCINT1);
    GIMSK  |= (1 << PCIE0);
}

static __inline__ uint8_t SBUS_Available(void) {
    return __sbus_new_frame;
}

static __inline__ void SBUS_Decode(const uint8_t *buf) {
    __sbus_channels[0]  = ((buf[1]       | buf[2] << 8)                     ) & 0x07FF;
    __sbus_channels[1]  = ((buf[2] >> 3  | buf[3] << 5)                     ) & 0x07FF;
    __sbus_channels[2]  = ((buf[3] >> 6  | buf[4] << 2 | buf[5] << 10)     ) & 0x07FF;
    __sbus_channels[3]  = ((buf[5] >> 1  | buf[6] << 7)                     ) & 0x07FF;
    __sbus_channels[4]  = ((buf[6] >> 4  | buf[7] << 4)                     ) & 0x07FF;
    __sbus_channels[5]  = ((buf[7] >> 7  | buf[8] << 1 | buf[9] << 9)      ) & 0x07FF;
    __sbus_channels[6]  = ((buf[9] >> 2  | buf[10] << 6)                    ) & 0x07FF;
    __sbus_channels[7]  = ((buf[10] >> 5 | buf[11] << 3)                    ) & 0x07FF;
    __sbus_channels[8]  = ((buf[12]      | buf[13] << 8)                    ) & 0x07FF;
    __sbus_channels[9]  = ((buf[13] >> 3 | buf[14] << 5)                    ) & 0x07FF;
    __sbus_channels[10] = ((buf[14] >> 6 | buf[15] << 2 | buf[16] << 10)    ) & 0x07FF;
    __sbus_channels[11] = ((buf[16] >> 1 | buf[17] << 7)                    ) & 0x07FF;
    __sbus_channels[12] = ((buf[17] >> 4 | buf[18] << 4)                    ) & 0x07FF;
    __sbus_channels[13] = ((buf[18] >> 7 | buf[19] << 1 | buf[20] << 9)     ) & 0x07FF;
    __sbus_channels[14] = ((buf[20] >> 2 | buf[21] << 6)                    ) & 0x07FF;
    __sbus_channels[15] = ((buf[21] >> 5 | buf[22] << 3)                    ) & 0x07FF;

    __sbus_flags = buf[23];
}


static __inline__ void SBUS_Reset(void) {
    TCCR1B = 0;
    CBIT(TIMSK1, OCIE1A);
    SBIT(PCMSK0, PCINT1);
    SBIT(GIFR, PCIF0);
    __sbus_state = SBUS_STATE_WAIT_FALLING;
    __sbus_frame_index = -1;
}


static __inline__ uint8_t SBUS_ToPWM(uint16_t sbus) {
    if(sbus < 172) sbus = 172;
    if(sbus > 1850) sbus = 1850;
    if(sbus < 200) return 0;
    return (uint8_t)((uint32_t)(sbus - 172) * 255 / (1811 - 172));
}


static __inline__ uint16_t SBUS_GetValue(uint8_t ch) {
    return __sbus_channels[ch];
}


static __inline__ void SBUS_ProcessReceivedByte(uint8_t b) {
    if(__sbus_frame_index == -1) {
        if(b == 0x0F) {
            __sbus_frame_buf[0] = b;
            __sbus_frame_index = 1;
        }
    } else {
        __sbus_frame_buf[__sbus_frame_index++] = b;
        if(__sbus_frame_index == 25) {
            __sbus_frame_index = -1;
            if(__sbus_frame_buf[0] == 0x0F && __sbus_frame_buf[24] == 0x00) {
                SBUS_Decode(__sbus_frame_buf);
                __sbus_new_frame = true;
            }
            SBUS_Reset();
        }
    }
}

ISR(PCINT0_vect) {
    if(__sbus_state != SBUS_STATE_WAIT_FALLING) {
        return;
    }

    uint8_t pin = (SBUS_PIN >> SBUS_BIT) & 1;

    if(pin == 0) {
        CBIT(PCMSK0, PCINT1);

        TCCR1B = 0;
        TCNT1 = 0;
        TCCR1A = 0;

        OCR1A = SBUS_OCR_HALF_BIT;

        SBIT(TIFR1, OCF1A);
        SBIT(TIMSK1, OCIE1A);
        SBIT(TCCR1B, WGM12);
        SBIT(TCCR1B, CS10);

        __sbus_state = SBUS_STATE_SYNC_START;

        __sbus_sample_count = 0;
        __sbus_timeout_count = 0;
        __sbus_current_byte = 0;
        __sbus_bit_pos = 0;
    }
}


ISR(TIM1_COMPA_vect) {
    uint8_t pin = (SBUS_PIN >> SBUS_BIT) & 1;

    if(__sbus_state == SBUS_STATE_SYNC_START) {
        if(pin != 0) {
            SBUS_Reset();
            return;
        }

        OCR1A = SBUS_OCR_FULL_BIT;

        __sbus_state = SBUS_STATE_RECEIVING;
        __sbus_bit_pos = 0;
        __sbus_current_byte = 0;
        return;
    }

    if(__sbus_state != SBUS_STATE_RECEIVING) {
        SBUS_Reset();
        return;
    }

    switch(__sbus_bit_pos) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            __sbus_current_byte >>= 1;
            if(pin) {
                __sbus_current_byte |= 0x80;
            }
            if(__sbus_bit_pos == 7) {
                SBUS_ProcessReceivedByte(__sbus_current_byte);
                __sbus_current_byte = 0;
            }
            break;
        case 8:
        case 9:
            break;

        case 10:
            __sbus_bit_pos = 0;
            __sbus_current_byte = 0;
            __sbus_timeout_count++;
            if(__sbus_timeout_count >= SBUS_TIMOUT) {
                SBUS_Reset();
            }
            return;
    }

    __sbus_bit_pos++;
    __sbus_timeout_count++;
    if(__sbus_timeout_count >= SBUS_TIMOUT) {
        SBUS_Reset();
    }
}



#endif // __SBUS_H__
