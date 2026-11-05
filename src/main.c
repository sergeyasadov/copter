#include "defines.h"
#include "drivers/crsf/CRSF.h"
#include "drivers/mpu9250/mpu9250.h"
#include "drivers/mpu9250/SPI1.h"
#include "hardfault.h"
#include "utils/clock_config.h"
#include "debug/debug.h"
#include "utils/delay.h"
#include "status.h"

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>


int main(void) {
    ClockConfig_72MHz_HSE();
    delay_ms(1500);

    DebugInit();

    // MPU9250_Init();

    SPI1_GPIO_Init();


    while (1) {
        // DebugLogf(STATUS_OK, "%X", MPU9250_ReadReg(0x75));
        delay_ms(2000);
    }
}



//
//
// // volatile uint32_t* __RESTRICT const SOFTREBOOT = (volatile uint32_t*)(0x20004FFC);
//
//
// int main(void) {
//     ClockConfig_72MHz_HSE();
//
//     delay_ms(2000);
//
//     RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
//     RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
//
//     AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG) | AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
//
//
//     DebugInit();
//     DebugLog(STATUS_EXCEPTION, "");
//     HardFault_Log();
//
//
//     // struct CRSF_TypeDef crsf;
//     // CRSF_Init(&crsf);
//     // uint16_t crsf_data[64];
//     // char buf[32];
//     // debug_log(STATUS_OK, "CRSF Init");
//
//     // MPU9250_Init();
//
//
//     // if(*SOFTREBOOT != 1) {
//     //     DebugLog(STATUS_EXCEPTION, "Software system reset");
//     //     delay_ms(1);
//     //     *SOFTREBOOT = 1;
//     //     NVIC_SystemReset();
//     // }
//     // *SOFTREBOOT = 0;
//
//
// //     DebugLogf(STATUS_OK, "ID = %x", MPU9250_Read(0x70));
// //     DebugLogf(STATUS_OK, "ID = %x", MPU9250_Read(0x6A));
//
// //     GPIOA->BSRR = (1UL << (7)) | (1UL << (5));
//     // GPIOA->BSRR = (1UL << (7 + 16)) | (1UL << (5 + 16));
//
//
//    // uint32_t got = 1;
//     while (1) {
//         DebugLog(STATUS_ERROR, "ERROR");
//         // DebugLogf(STATUS_OK, "%u", MPU9250_ReadReg(0x75));
//         // DebugLogf(STATUS_OK, "%u", MPU9250_ReadReg(0x6B));
//         delay_ms(1000);
//         DebugLog(STATUS_OK, "OK");
//         delay_ms(50);
//
//         // if(CRSF_Receive(&crsf) == STATUS_CRSF_RECEIVED) {
//         //     got = 1;
//         // }
//         // if(got) {
//         //     CRSF_DecodeChannels(&crsf, crsf_data);
//         //     snprintf(buf, sizeof(buf), "%u\t%u\t%u\t%u\t%u",
//         //         crsf_data[0],
//         //         crsf_data[1],
//         //         crsf_data[2],
//         //         crsf_data[3],
//         //         crsf_data[4]
//         //     );
//         //     debug_log(STATUS_OK, buf);
//         //     got = 0;
//         // }
//     }
// }
