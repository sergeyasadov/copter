#include "CRSF_Receiver.h"

#include "../../protocols/CRSF/CRSF_Defines.h"
#include "../../protocols/CRSF/CRSF.h"
#include "../../defines.h"
#include "../../iodefs.h"
#include "../../status.h"

#include <string.h>

//========================================================================================
static volatile uint8_t crsf_rx_buffer[CRSF_BUFFER_SIZE];
static uint8_t crsf_frame[CRSF_FRAME_SIZE];
static uint_fast16_t rx_tail = 0;
static uint_fast8_t crsf_feed_pos = 0;
static uint_fast8_t crsf_feed_skip = 0;
//========================================================================================
__STATIC_INLINE int p_CRSF_Receiver_Feed(struct CRSF_TypeDef* crsf, uint8_t b) {
    if(crsf_feed_skip) {
        crsf_feed_skip--;
        return 0;
    }

    if(crsf_feed_pos == 0) {
        if(b == CRSF_SYNC_BYTE) {
            crsf_frame[crsf_feed_pos++] = b;
        }
        return 0;
    }

    crsf_frame[crsf_feed_pos++] = b;

    if(crsf_feed_pos == 2) {
        if(b < 2 || b > 62){
            crsf_feed_pos = 0;
        }
        else if(b != CRSF_RC_FRAME_LEN) {
            crsf_feed_skip = b;
            crsf_feed_pos = 0;
        }
        return 0;
    }

    if(crsf_feed_pos == crsf_frame[1] + 2u) {
        crsf_feed_pos = 0;
        if(crsf_frame[2] == CRSF_TYPE_RC_CHANNELS
            && CRSF_CRC8_Get(&crsf_frame[2], crsf_frame[1] - 1u) == crsf_frame[crsf_frame[1] + 1u]
        ) {
            memcpy(crsf->data, crsf_frame, CRSF_RC_FRAME_LEN + 2u);
            crsf->len = crsf_frame[1];
            return 1;
        }
    }
    return 0;
}
//========================================================================================
void CRSF_Receiver_Init(struct CRSF_TypeDef* crsf) {
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;

    AFIO->MAPR |= AFIO_MAPR_USART1_REMAP;

    DMA1_Channel5->CCR &= ~DMA_CCR_EN;
    DMA1_Channel5->CCR |= DMA_CCR_CIRC | DMA_CCR_MINC;
    DMA1_Channel5->CPAR = (uint32_t)&(USART1->DR);
    DMA1_Channel5->CMAR = (uint32_t)crsf_rx_buffer;
    DMA1_Channel5->CNDTR = CRSF_BUFFER_SIZE;
    DMA1_Channel5->CCR |= DMA_CCR_EN;

    GPIOB->CRL = (GPIOB->CRL & ~((GPIO_CRL_CNF6 | GPIO_CRL_MODE6) | (GPIO_CRL_CNF7 | GPIO_CRL_MODE7)))
                | (GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6) | (GPIO_CRL_CNF7_0);

    USART1->BRR = 0xAB;

    USART1->CR1 |= USART_CR1_UE | USART_CR1_RE;
    USART1->CR3 |= USART_CR3_DMAR;

    crsf->len = 0;

    for(uint_fast8_t i = 0; i < CRSF_FRAME_SIZE; i++) {
        crsf->data[i] = 0;
    }

    rx_tail = 0;
    crsf_feed_pos = 0;
    crsf_feed_skip = 0;
}
//----------------------------------------------------------------------------------------
uint32_t CRSF_Receiver_Read(struct CRSF_TypeDef* crsf) {
    uint_fast16_t head = (CRSF_BUFFER_SIZE - DMA1_Channel5->CNDTR) & CRSF_MASK;

    while(rx_tail != head) {
        const uint8_t b = crsf_rx_buffer[rx_tail];
        rx_tail = (rx_tail + 1u) & CRSF_MASK;
        if(p_CRSF_Receiver_Feed(crsf, b)) {
            return 1;
        }
    }
    return 0;
}
//========================================================================================
