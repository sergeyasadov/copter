#include "drivers/crsf/CRSF.h"
#include "stm32f103xb.h"
#include "utils/clock_config.h"
#include "debug/debug.h"
#include "utils/delay.h"
#include "utils/TON.h"
#include "status.h"

#include <stdio.h>


static uint32_t soft_reboot __attribute__((section(".ccmram"))) = 1;


int main(void) {
    ClockConfig_72MHz_HSE();

    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG) | AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

    debug_init();

    struct CRSF_TypeDef crsf;
    CRSF_Init(&crsf);
    uint16_t crsf_data[64];
    char buf[32];
    debug_log(STATUS_OK, "CRSF Init");

    if(soft_reboot) {
        soft_reboot = 0;
        NVIC_SystemReset();
    }
    soft_reboot = 1;


    uint32_t got = 1;
    while (1) {
        if(CRSF_Receive(&crsf) == STATUS_CRSF_RECEIVED) {
            got = 1;
        }
        if(got) {
            CRSF_DecodeChannels(&crsf, crsf_data);
            snprintf(buf, sizeof(buf), "%u\t%u\t%u\t%u\t%u",
                crsf_data[0],
                crsf_data[1],
                crsf_data[2],
                crsf_data[3],
                crsf_data[4]
            );
            debug_log(STATUS_OK, buf);
            got = 0;
        }
    }
}
