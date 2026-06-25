#include "defines.h"
#include "sys/uart.h"
#include "flight/motor.h"
#include "flight/sbus.h"


int main(void) {
    UART_Init();
    _delay_ms(400);
    UART_Print("UART Init\r\n");

    SBUS_Init();
    UART_Print("SBUS Init\r\n");

    Motor_Init();
    UART_Print("Motor Init\r\n");

    sei();


    while (1) {
        if (SBUS_Available()) {
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                uint16_t sbus_ch_copy[SBUS_NUM_CHANNELS];
                for (uint8_t i = 0; i < SBUS_NUM_CHANNELS; i++) {
                    sbus_ch_copy[i] = __sbus_channels[i];
                }
                uint8_t flags_copy = __sbus_flags;
                SBUS_Reset();

                MOTOR_SET(1, SBUS_ToPWM(sbus_ch_copy[2]));
                MOTOR_SET(2, SBUS_ToPWM(sbus_ch_copy[1]));
            }
        }
    }

    return 0;
}
