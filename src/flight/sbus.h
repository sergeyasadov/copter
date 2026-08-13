#ifndef __SBUS_H__
#define __SBUS_H__

#include "defines.h"
#include "sys/gpio.h"
#include "sys/utils.h"

#define SBUS_DDR DDRA
#define SBUS_PORT PORTA
#define SBUS_PIN PINA
#define SBUS_BIT PA1
#define SBUS_BIT_MASK (1 << SBUS_BIT)
#define SBUS_NUM_CHANNELS 16

#define SBUS_OCR_HALF_BIT  99
#define SBUS_OCR_FULL_BIT  199

#define SBUS_COUNT_CHANNELS 4

#define SBUS_TIMEOUT 412 // 25 * 11 (*1.5)

#define SBUS_FILTER_EMA 3 // 1..4


enum sbus_state_t {
    SBUS_STATE_WAIT_FALLING = 0,
    SBUS_STATE_SYNC_START,
    SBUS_STATE_RECEIVING
};


static volatile uint16_t __sbus_channels[SBUS_NUM_CHANNELS];
static volatile uint8_t __sbus_new_frame = 0;
static uint8_t __sbus_state;
static uint8_t __sbus_flags;
static uint8_t __sbus_current_byte;
static uint16_t __sbus_timeout_count;
static uint8_t __sbus_bit_pos;

static uint8_t __sbus_frame_buf[25];
static int8_t __sbus_frame_index = -1;

static uint8_t __sbus_debug_buf[25];

static uint16_t __sbus_filtered[SBUS_NUM_CHANNELS];


static __inline__ void SBUS_Init(void) {
    GPIO_SET_INPUT(SBUS_DDR, SBUS_BIT_MASK);
    GPIO_SET_HIGH(SBUS_PORT, SBUS_BIT_MASK);

    _delay_ms(10);

    SMBIT(GIFR, PCIF0);
    SMBIT(PCMSK0, PCINT1);
    SMBIT(GIMSK, PCIE0);

    __sbus_state       = SBUS_STATE_WAIT_FALLING;
    __sbus_frame_index = -1;
}


static __inline__ void SBUS_Decode(const uint8_t *buf) {
    __sbus_channels[0]  = ((uint16_t)buf[1]           | ((uint16_t)buf[2]  << 8))                                        & 0x07FF;
    __sbus_channels[1]  = (((uint16_t)buf[2]  >> 3)   | ((uint16_t)buf[3]  << 5))                                        & 0x07FF;
    __sbus_channels[2]  = (((uint16_t)buf[3]  >> 6)   | ((uint16_t)buf[4]  << 2)  | ((uint16_t)(buf[5]  & 0x01) << 10)) & 0x07FF;
    __sbus_channels[3]  = (((uint16_t)buf[5]  >> 1)   | ((uint16_t)buf[6]  << 7))                                        & 0x07FF;
    __sbus_channels[4]  = (((uint16_t)buf[6]  >> 4)   | ((uint16_t)buf[7]  << 4))                                        & 0x07FF;
    __sbus_channels[5]  = (((uint16_t)buf[7]  >> 7)   | ((uint16_t)buf[8]  << 1)  | ((uint16_t)(buf[9]  & 0x03) << 9))  & 0x07FF;
    __sbus_channels[6]  = (((uint16_t)buf[9]  >> 2)   | ((uint16_t)buf[10] << 6))                                        & 0x07FF;
    __sbus_channels[7]  = (((uint16_t)buf[10] >> 5)   | ((uint16_t)buf[11] << 3))                                        & 0x07FF;
    __sbus_channels[8]  = ((uint16_t)buf[12]           | ((uint16_t)buf[13] << 8))                                        & 0x07FF;
    __sbus_channels[9]  = (((uint16_t)buf[13] >> 3)   | ((uint16_t)buf[14] << 5))                                        & 0x07FF;
    __sbus_channels[10] = (((uint16_t)buf[14] >> 6)   | ((uint16_t)buf[15] << 2)  | ((uint16_t)(buf[16] & 0x01) << 10)) & 0x07FF;
    __sbus_channels[11] = (((uint16_t)buf[16] >> 1)   | ((uint16_t)buf[17] << 7))                                        & 0x07FF;
    __sbus_channels[12] = (((uint16_t)buf[17] >> 4)   | ((uint16_t)buf[18] << 4))                                        & 0x07FF;
    __sbus_channels[13] = (((uint16_t)buf[18] >> 7)   | ((uint16_t)buf[19] << 1)  | ((uint16_t)(buf[20] & 0x03) << 9))  & 0x07FF;
    __sbus_channels[14] = (((uint16_t)buf[20] >> 2)   | ((uint16_t)buf[21] << 6))                                        & 0x07FF;
    __sbus_channels[15] = (((uint16_t)buf[21] >> 5)   | ((uint16_t)buf[22] << 3))                                        & 0x07FF;
    __sbus_flags = buf[23];
}


static __inline__ void SBUS_Reset(void) {
    TCCR1B = 0;
    CMBIT(TIMSK1, OCIE1A);

    __sbus_state       = SBUS_STATE_WAIT_FALLING;
    __sbus_frame_index = -1;
    __sbus_bit_pos     = 0;
    __sbus_current_byte = 0;

    SMBIT(GIFR, PCIF0);
    SMBIT(PCMSK0, PCINT1);
}


static __inline__ void SBUS_Filter(void) {
    for(uint8_t i = 0; i < SBUS_COUNT_CHANNELS; i++) {
        const uint16_t raw = __sbus_channels[i];
        __sbus_filtered[i] = (int16_t)(raw - __sbus_filtered[i]) >> SBUS_FILTER_EMA;
    }
}


static __inline__ __attribute__((always_inline)) uint16_t SBUS_GetFilteredValue(uint8_t ch) {
    return __sbus_filtered[ch];
}


static __inline__ __attribute__((always_inline)) uint8_t SBUS_Available(void) {
    return __sbus_new_frame;
}


static __inline__ __attribute__((always_inline)) void SBUS_Update(void) {
    __sbus_new_frame = 0;
}


static __inline__ __attribute__((always_inline)) uint16_t SBUS_GetValue(uint8_t ch) {
    return __sbus_channels[ch];
}


static __inline__ int8_t SBUS_ToPWM_Centered(uint16_t sbus, const uint8_t min, const uint16_t max) {
    sbus = CLAMP(sbus, min, max);
    return (uint8_t)(((uint32_t)(sbus - min) * 255 / (max - min)) - 128);
}


static __inline__ uint8_t SBUS_ToPWM_Uncentered(uint16_t sbus, const uint8_t min, const uint16_t max) {
    sbus = CLAMP(sbus, min, max);
    return (uint8_t)(((uint32_t)(sbus - min) * 255 / (max - min)));
}


ISR(PCINT0_vect) {
    if (!(PCMSK0 & (1 << PCINT1))) return;
    if (__sbus_state != SBUS_STATE_WAIT_FALLING) return;

    const uint8_t pin = (SBUS_PIN >> SBUS_BIT) & 1;
    if (pin != 0) return;

    PCMSK0 &= ~(1 << PCINT1);

    TCCR1B = 0;
    TCCR1A = 0;
    TCNT1  = 0;
    OCR1A  = SBUS_OCR_HALF_BIT;
    TIFR1  = (1 << OCF1A);
    TIMSK1 |= (1 << OCIE1A);
    TCCR1B = (1 << WGM12) | (1 << CS10);

    __sbus_state         = SBUS_STATE_SYNC_START;
    __sbus_timeout_count = 0;
    __sbus_current_byte  = 0;
    __sbus_bit_pos       = 0;
}


ISR(TIM1_COMPA_vect) {
    uint8_t pin = (SBUS_PIN >> SBUS_BIT) & 1;

    if (__sbus_state == SBUS_STATE_SYNC_START) {
        if (pin != 0) {
            SBUS_Reset();
            return;
        }
        OCR1A = SBUS_OCR_FULL_BIT;
        __sbus_state    = SBUS_STATE_RECEIVING;
        __sbus_bit_pos  = 1;
        __sbus_timeout_count++;
        return;
    }

    if (__sbus_state != SBUS_STATE_RECEIVING) {
        SBUS_Reset();
        return;
    }

    uint8_t bp = __sbus_bit_pos;

    if (bp >= 1 && bp <= 8) {
        __sbus_current_byte >>= 1;
        if (pin) {
            __sbus_current_byte |= 0x80;
        }

        if (bp == 8) {
            uint8_t b = __sbus_current_byte;
            __sbus_current_byte = 0;

            if (__sbus_frame_index == -1) {
                if (b == 0x0F) {
                    __sbus_frame_buf[0] = b;
                    __sbus_frame_index  = 1;
                }
            } else {
                __sbus_frame_buf[__sbus_frame_index++] = b;

                if (__sbus_frame_index == 25) {
                    if (__sbus_frame_buf[0] == 0x0F) {
                        SBUS_Decode(__sbus_frame_buf);
                        __sbus_new_frame = 1;
                    }
                    SBUS_Reset();
                    return;
                }
            }
        }

    }

    if (bp == 0) {
        if (pin != 0) {
            SBUS_Reset();
            return;
        }
        __sbus_current_byte = 0;
        __sbus_bit_pos = 1;
        __sbus_timeout_count++;
        if (__sbus_timeout_count >= SBUS_TIMEOUT) {
            SBUS_Reset();
        }
        return;
    }

    if (bp == 11) {
        __sbus_bit_pos = 0;
        __sbus_timeout_count++;
        if (__sbus_timeout_count >= SBUS_TIMEOUT) {
            SBUS_Reset();
        }
        return;
    }

    __sbus_bit_pos++;
    __sbus_timeout_count++;
    if (__sbus_timeout_count >= SBUS_TIMEOUT) {
        SBUS_Reset();
    }
}


#endif // __SBUS_H__
