#ifndef DEFINES_H
#define DEFINES_H

#include <stm32f1xx.h>

//========================================================================================
#define ARR_SIZE(__arr) (sizeof(__arr) / sizeof(__arr[0]))
//========================================================================================
#define CLAMP(__val, __min, __max) \
    ((__val) < (__min) ? (__min) : (__val) > (__max) ? (__max) : (__val) )
//========================================================================================
#define ARR_FOREACH(__arr, __i) \
    for(uint_fast8_t __i = 0, __s = ARR_SIZE(__arr); __i < __s; __i++)
//========================================================================================
#define LINTERP(x, x1, x2, y1, y2) \
    ( (y1) + ( (uint32_t)((x) - (x1)) * ((y2) - (y1)) ) / ((x2) - (x1)) )
//========================================================================================
#define TICKS_TO_US(x)  (((x) - 992) * 5 / 8 + 1500)
#define US_TO_TICKS(x)  (((x) - 1500) * 8 / 5 + 992)
//========================================================================================
// DEBUG LED
#define DL0_POWER       8UL //PB8
#define DL1_SIGNAL      9UL //PB9
#define DL2_EXCEPTION   5UL //PB5
//========================================================================================
// D-Motor
#define MOTOR_CH1   8UL
#define MOTOR_CH2   9UL
#define MOTOR_CH3   10UL
#define MOTOR_CH4   11UL
//========================================================================================
// ELRS [CRSF] (UART1) [Not sync]
// Async 420'000 bits/s ~ 420'000 baud
// 8 bits, no parity, 1 stop bit
// Interrupt-driven
#define ELRS_TX     6UL //PB6
#define ELRS_RX     7UL //PB7
//========================================================================================
// MPU-9560/6500 (SPI1)
#define MPU_SCK     5UL //PA5
#define MPU_MOSI    7UL //PA7
#define MPU_MISO    6UL //PA6
#define MPU_NSS     4UL //PA4
#define MPU_INT     0UL //PB0
//========================================================================================
// UART_DEBUG (UART2) [Not sync]
#define UART_DEBUG_TX   2u //PA2
#define UART_DEBUG_RX   3u //PA3
//========================================================================================


#endif // DEFINES_H
