#include "crsf/CRSF.h"
#include "debug/logger.h"
#include "defines.h"
#include "debug/debug.h"
#include "stm32f103xb.h"
#include "utils/TON.h"
#include "utils/delay.h"
#include "utils/clock_config.h"


volatile uint32_t sys_ticks = 0;

__STATIC_INLINE void SysTick_Handler(void) {
    sys_ticks++;
}


__STATIC_INLINE uint32_t SysTick_Get(void) {
    return sys_ticks;
}


int main(void) {
    debug_init();

    ClockConfig_72MHz_HSE();

    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;

    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG) | AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
    GPIOB->ODR = 0;

    debug_log(LOG_LEVEL_OK, "Init OK");

    CRSF_Init();
    struct CRSF_TypeDef crsf;
    debug_log(LOG_LEVEL_OK, "CRSF Init");

    uint16_t rc_ticks[16];

    while(1) {
        if(CRSF_Receive(&crsf)) {
            CRSF_DecodeChannels(&crsf, rc_ticks);

        }
    }

    return 0;
}


// // #define MAIN_MCU

// #ifdef MAIN_MCU

// #include "utils.h"
// #include "flight/sbus.h"
// #include "sys/uart_tx.h"

// int main(void) {
//     static uint8_t packet[] = {
//         0xF8, 0x00, 0x00, 0x00, 0x00
//     };

//     UART_TX_Init();
//     _delay_ms(10);

//     SBUS_Init();
//     _delay_ms(10);

//     sei();

//     while(1) {
//         if(SBUS_Available()) {
//             ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
//                 SBUS_Filter();

//                 const int8_t roll = SBUS_ToPWM_Centered(SBUS_GetFilteredValue(0), 19, 200);
//                 const int8_t pitch = SBUS_ToPWM_Centered(SBUS_GetFilteredValue(1), 20, 201);
//                 const uint8_t throttle = SBUS_ToPWM_Uncentered(SBUS_GetFilteredValue(2), 20, 200);
//                 const int8_t yaw = SBUS_ToPWM_Centered(SBUS_GetFilteredValue(3), 20, 200);

//                 const int16_t m1 = (int16_t)throttle - pitch + roll + yaw;
//                 const int16_t m2 = (int16_t)throttle + pitch + roll - yaw;
//                 const int16_t m3 = (int16_t)throttle - pitch - roll - yaw;
//                 const int16_t m4 = (int16_t)throttle + pitch - roll + yaw;

//                 packet[1] = (uint8_t)CLAMP(m1, 0, 255);
//                 packet[2] = (uint8_t)CLAMP(m2, 0, 255);
//                 packet[3] = (uint8_t)CLAMP(m3, 0, 255);
//                 packet[4] = (uint8_t)CLAMP(m4, 0, 255);

//                 for(uint8_t i = 0; i < ARR_SIZE(packet); i++) {
//                     UART_SendByte(packet[i]);
//                 }

//                 SBUS_Update();
//             }
//         }
//     }

// }


// #else // DRIVE


// #include "flight/motor.h"
// #include "sys/uart_rx.h"

// int main(void) {

//     static uint8_t packet[5];

//     Motor_Init();

//     UART_RX_Init();


//     sei();


//     while(1) {
//         if(UART_RX_GetPacket(packet)) {
//             ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
//                 uint8_t m1, m2, m3, m4;

//                 m1 = packet[1];
//                 m2 = packet[2];
//                 m3 = packet[3];
//                 m4 = packet[4];

//                 MOTOR_SET(1, m3);
//                 MOTOR_SET(2, m1);
//                 MOTOR_SET(3, m2);
//                 MOTOR_SET(4, m4);
//             }

//         }
//     }
// }
// #endif //
