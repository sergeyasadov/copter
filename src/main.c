#include "drivers/crsf/CRSF.h"
#include "utils/clock_config.h"
#include "debug/debug.h"
#include "utils/delay.h"
#include "utils/TON.h"
#include "status.h"
#include "drivers/mpu9250/mpu9250.h"

#include <stdint.h>
#include <stdio.h>


// volatile uint32_t* const SOFTREBOOT = (volatile uint32_t*)(0x20004FFC);


int main(void) {
    ClockConfig_72MHz_HSE();

    delay_ms(1500);

    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG) | AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

    DebugInit();

    // struct CRSF_TypeDef crsf;
    // CRSF_Init(&crsf);
    // uint16_t crsf_data[64];
    // char buf[32];
    // debug_log(STATUS_OK, "CRSF Init");

    MPU9250_Init();

    // if(!soft_reboot) {
    //     debug_log(STATUS_EXCEPTION, "Software system reset");
    //     soft_reboot = 1;
    //     NVIC_SystemReset();
    // }
    // soft_reboot = 0;

    MPU9250_Write(0x6b, 0x80);
    delay_ms(100);
    MPU9250_Write(0x6b, 0x01);
    MPU9250_Write(0x6a, 0x10);

    DebugLogf(STATUS_OK, "ID = %x", MPU9250_Read(0x75));
    DebugLogf(STATUS_OK, "ID = %x", MPU9250_Read(0x6A));

    // uint32_t got = 1;
    while (1) {
        DebugLog(STATUS_ERROR, "ERROR");
        delay_ms(1000);
        DebugLog(STATUS_OK, "OK");
        delay_ms(50);

        // if(CRSF_Receive(&crsf) == STATUS_CRSF_RECEIVED) {
        //     got = 1;
        // }
        // if(got) {
        //     CRSF_DecodeChannels(&crsf, crsf_data);
        //     snprintf(buf, sizeof(buf), "%u\t%u\t%u\t%u\t%u",
        //         crsf_data[0],
        //         crsf_data[1],
        //         crsf_data[2],
        //         crsf_data[3],
        //         crsf_data[4]
        //     );
        //     debug_log(STATUS_OK, buf);
        //     got = 0;
        // }
    }
}
