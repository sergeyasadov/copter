#include "defines.h"
#include "sys/uart.h"
#include "flight/motor.h"
#include "flight/sbus.h"
#include "util/atomic.h"
#include "util/delay.h"


int main(void) {

    UART_Init();
    _delay_ms(10);

    Motor_Init();
    UART_Print("Init\n\r");
    _delay_ms(10);

    SBUS_Init();
    _delay_ms(10);
    sei();


    while (1) {
        if (__sbus_new_frame) {
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                SBUS_Filter();
                __sbus_new_frame = false;
                // UART_PrintDec(SBUS_ToPWM(SBUS_GetFilteredValue(0), 19, 200));
                // UART_PrintDec(SBUS_ToPWM(SBUS_GetFilteredValue(1), 20, 201));
                // UART_PrintDec(SBUS_ToPWM(SBUS_GetFilteredValue(2), 19, 201));
                // UART_PrintDec(SBUS_ToPWM(SBUS_GetFilteredValue(3), 20, 200));
                UART_Print("\n\r");
            }
        }
    }



    return 0;
}
