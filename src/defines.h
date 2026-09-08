#ifndef DEFINES_H
#define DEFINES_H

#include <stm32f1xx.h>

//========================================================================================
// DEBUG LED
#define DL0_POWER 3u //PB3
#define DL1_SIGNAL 4u //PB4
#define DL2_EXCEPTION 5u //PB5
//========================================================================================
// ELRS [CRSF] (UART1) [Not sync]
// Async 420'000 bits/s ~ 420'000 baud
// 8 bits, no parity, 1 stop bit
// Interrupt-driven
#define ELRS_TX 6u //PB6
#define ELRS_RX 7u //PB7
//========================================================================================
// MPU-9560/6500 (SPI1)
#define MPU_SCK 5u //PA5
#define MPU_MOSI 7u //PA7
#define MPU_MISO 6u //PA6
#define MPU_NSS 4u //PA4
#define MPU_INT 0u //PB0
//========================================================================================
// UART_DEBUG (UART2) [Not sync]
#define UART_DEBUG_TX 2u //PA2
#define UART_DEBUG_RX 3u //PA3
//========================================================================================


#endif // DEFINES_H
