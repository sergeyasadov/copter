#ifndef IODEFINES_H
#define IODEFINES_H


//========================================================================================
// DEBUG LED
#define GPIO_DL0_POWER_Bit       (8UL) //PB8
#define GPIO_DL0_POWER_Msk        (1UL << GPIO_DL0_POWER_Bit)
#define GPIO_DL0_POWER           GPIO_DL0_POWER_Msk

#define GPIO_DL1_SIGNAL_Bit      (9UL) //PB9
#define GPIO_DL1_SIGNAL_Msk      (1UL << GPIO_DL1_SIGNAL_Bit)
#define GPIO_DL1_SIGNAL          GPIO_DL1_SIGNAL_Msk

#define GPIO_DL2_EXCEPTION_Bit   (5UL) //PB5
#define GPIO_DL2_EXCEPTION_Msk   (1UL << GPIO_DL2_EXCEPTION_Bit)
#define GPIO_DL2_EXCEPTION       GPIO_DL2_EXCEPTION_Msk
//========================================================================================
// D-Motor
#define GPIO_MOTOR_CH1_Bit      (8UL)
#define GPIO_MOTOR_CH1_Msk      (1UL << GPIO_MOTOR_CH1_Bit)
#define GPIO_MOTOR_CH1          GPIO_MOTOR_CH1_Msk

#define GPIO_MOTOR_CH2_Bit      (9UL)
#define GPIO_MOTOR_CH2_Msk      (1UL << GPIO_MOTOR_CH2_Bit)
#define GPIO_MOTOR_CH2          GPIO_MOTOR_CH2_Msk

#define GPIO_MOTOR_CH3_Bit      (10UL)
#define GPIO_MOTOR_CH3_Msk      (1UL << GPIO_MOTOR_CH3_Bit)
#define GPIO_MOTOR_CH3          GPIO_MOTOR_CH3_Msk

#define GPIO_MOTOR_CH4_Bit      (11UL)
#define GPIO_MOTOR_CH4_Msk      (1UL << GPIO_MOTOR_CH4_Bit)
#define GPIO_MOTOR_CH4          GPIO_MOTOR_CH4_Msk
//========================================================================================
// ELRS [CRSF] (UART1) [Not sync]
// Async 420'000 bits/s ~ 420'000 baud
// 8 bits, no parity, 1 stop bit
// Interrupt-driven
#define GPIO_ELRS_TX_Bit        (6UL) //PB6
#define GPIO_ELRS_TX_Msk        (1UL << GPIO_ELRS_TX_Bit)
#define GPIO_ELRS_TX            GPIO_ELRS_TX_Msk

#define GPIO_ELRS_RX_Bit        (7UL) //PB7
#define GPIO_ELRS_RX_Msk        (1UL << GPIO_ELRS_RX_Bit)
#define GPIO_ELRS_RX            GPIO_ELRS_RX_Msk
//========================================================================================
// MPU-9560/6500 (SPI1)
#define GPIO_MPU_SCK_Bit        (5UL) //PA5
#define GPIO_MPU_SCK_Msk        (1UL << GPIO_MPU_SCK_Bit)
#define GPIO_MPU_SCK            GPIO_MPU_SCK_Msk

#define GPIO_MPU_MOSI_Bit       (7UL) //PA7
#define GPIO_MPU_MOSI_Msk       (1UL << GPIO_MPU_MOSI_Bit)
#define GPIO_MPU_MOSI           GPIO_MPU_MOSI_Msk

#define GPIO_MPU_MISO_Bit       (6UL) //PA6
#define GPIO_MPU_MISO_Msk       (1UL << GPIO_MPU_MISO_Bit)
#define GPIO_MPU_MISO           GPIO_MPU_MISO_Msk

#define GPIO_MPU_NSS_Bit        (4UL) //PA4
#define GPIO_MPU_NSS_Msk        (1UL << GPIO_MPU_NSS_Bit)
#define GPIO_MPU_NSS            GPIO_MPU_NSS_Msk

#define GPIO_MPU_INT_Bit        (0UL) //PB0
#define GPIO_MPU_INT_Msk        (1UL << GPIO_MPU_INT_Bit)
#define GPIO_MPU_INT            GPIO_MPU_INT_Msk
//========================================================================================
// UART_DEBUG (UART2) [Not sync]
#define GPIO_UART_DEBUG_TX_Bit      (2u) //PA2
#define GPIO_UART_DEBUG_TX_Msk      (1UL << GPIO_UART_DEBUG_TX_Bit)
#define GPIO_UART_DEBUG_TX          GPIO_UART_DEBUG_TX_Msk

#define GPIO_UART_DEBUG_RX_Bit      (3u) //PA3
#define GPIO_UART_DEBUG_RX_Msk      (1UL << GPIO_UART_DEBUG_RX_Bit)
#define GPIO_UART_DEBUG_RX          GPIO_UART_DEBUG_RX_Msk
//========================================================================================


#endif // IODEFINES_H
