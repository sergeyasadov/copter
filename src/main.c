#define MAIN_MCU

#ifdef MAIN_MCU

#include "utils.h"
#include "flight/sbus.h"
#include "sys/uart_tx.h"

int main(void) {
    static uint8_t packet[5];
    packet[0] = 0xF8;

    UART_TX_Init();
    _delay_ms(10);

    SBUS_Init();
    _delay_ms(10);

    sei();

    while(1) {
        if(SBUS_Available()) {
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                SBUS_Filter();
                const int8_t roll = SBUS_ToPWM(SBUS_GetFilteredValue(0), 19, 200);
                const int8_t pitch = SBUS_ToPWM(SBUS_GetFilteredValue(1), 20, 201);
                const uint8_t throttle = SBUS_ToPWM(SBUS_GetFilteredValue(2), 19, 201);
                const int8_t yaw = SBUS_ToPWM(SBUS_GetFilteredValue(3), 20, 200);

                const int16_t m1 = (int16_t)throttle - pitch + roll + yaw;
                const int16_t m2 = (int16_t)throttle + pitch + roll - yaw;
                const int16_t m3 = (int16_t)throttle - pitch - roll - yaw;
                const int16_t m4 = (int16_t)throttle + pitch - roll + yaw;

                packet[1] = (uint8_t)CLAMP(m1, 0, 255);
                packet[2] = (uint8_t)CLAMP(m2, 0, 255);
                packet[3] = (uint8_t)CLAMP(m3, 0, 255);
                packet[4] = (uint8_t)CLAMP(m4, 0, 255);

                for(register uint8_t i = 0; i < 5; i++) {
                    UART_SendByte(packet[i]);
                }
                _delay_us(10);

                SBUS_Update();
            }
        }
    }

}

#else // DRIVER

#include "flight/motor.h"
#include "sys/uart_rx.h"

int main(void) {

    static uint8_t packet[5];

    Motor_Init();

    UART_RX_Init();

    sei();

    while(1) {
        if(UART_RX_GetPacket(packet)) {
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                MOTOR_SET(1, packet[1]);
                MOTOR_SET(2, packet[2]);
                MOTOR_SET(3, packet[3]);
                MOTOR_SET(4, packet[4]);
            }
        }

    }
}
#endif //
