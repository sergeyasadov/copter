#ifndef DEFINES_H
#define DEFINES_H

#include <stm32f1xx.h>

//========================================================================================
// DEBUG LED
#define DL0_POWER 3 //PB3
#define DL1_SIGNAL 4 //PB4
#define DL2_EXCEPTION 5 //PB5
//========================================================================================
// ELRS (UART1) [Not sync]
// Async 420'000 bits/s ~ 420'000 baud
// 8 bits, no parity, 1 stop bit
// Interrupt-driven
#define ELRS_TX 6 //PB6
#define ELRS_RX 7 //PB7
//========================================================================================
// MPU-9560/6500 (SPI1)
#define MPU_SCK 5 //PA5s
#define MPU_MOSI 7 //PA7
#define MPU_MISO 6 //PA6
#define MPU_NSS 4 //PA4
#define MPU_INT 0 //PB0
//========================================================================================
// UART_DEBUG (UART2) [Not sync]
#define UART_DEBUG_TX 2 //PA2
#define UART_DEBUG_RX 3 //PA3
//========================================================================================


#endif // DEFINES_H
