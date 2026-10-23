#include "CRSF.h"

#include "../../utils/crc8.h"
#include "../../defines.h"
#include "../../status.h"

#include <string.h>

//========================================================================================
#define CRSF_SYNC_BYTE 0xC8
#define CRSF_TYPE_RC_CHANNELS 0x16
#define CRSF_BUFFER_SIZE 256u
#define CRSF_FRAME_SIZE 64
#define CRSF_MASK (CRSF_BUFFER_SIZE - 1u)
#define CRSF_RC_FRAME_LEN 24 // T + 22 payload + CRC
#define CRSF_OFFSET__SYNC_BYTE 0u
#define CRSF_OFFSET__FRAME_LENGTH 1u
#define CRSF_OFFSET__TYPE 2u
#define CRSF_OFFSET__PAYLOAD 3u
//========================================================================================
static volatile uint8_t crsf_rx_buffer[CRSF_BUFFER_SIZE];
static uint8_t crsf_frame[CRSF_FRAME_SIZE];
static uint_fast16_t rx_tail = 0;
static uint_fast8_t crsf_feed_pos = 0;
static uint_fast8_t crsf_feed_skip = 0;
//========================================================================================
__STATIC_INLINE int _CRSF_Feed(struct CRSF_TypeDef* crsf, uint8_t b) {
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
            && crc8(&crsf_frame[2], crsf_frame[1] - 1u) == crsf_frame[crsf_frame[1] + 1u]
        ) {
            memcpy(crsf->data, crsf_frame, CRSF_RC_FRAME_LEN + 2u);
            crsf->len = crsf_frame[1];
            return 1;
        }
    }
    return 0;
}
//========================================================================================
void CRSF_Init(struct CRSF_TypeDef* crsf) {
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    AFIO->MAPR |= AFIO_MAPR_USART1_REMAP;

    DMA1_Channel5->CCR &= ~DMA_CCR_EN;
    DMA1_Channel5->CCR |= DMA_CCR_CIRC | DMA_CCR_MINC;
    DMA1_Channel5->CPAR = (uint32_t)&(USART1->DR);
    DMA1_Channel5->CMAR = (uint32_t)crsf_rx_buffer;
    DMA1_Channel5->CNDTR = CRSF_BUFFER_SIZE;
    DMA1_Channel5->CCR |= DMA_CCR_EN;

    GPIOB->CRL &= ~((0xFUL << (4 * ELRS_TX)));
    GPIOB->CRL |= (0xBUL << (4 * ELRS_TX));

    GPIOB->CRL &= ~((0xFUL << (4 * ELRS_RX)));
    GPIOB->CRL |= (0x4UL << (4 * ELRS_RX));

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
uint32_t CRSF_Receive(struct CRSF_TypeDef* crsf) {
    uint_fast16_t head = (CRSF_BUFFER_SIZE - DMA1_Channel5->CNDTR) & CRSF_MASK;

    while(rx_tail != head) {
        const uint8_t b = crsf_rx_buffer[rx_tail];
        rx_tail = (rx_tail + 1u) & CRSF_MASK;
        if(_CRSF_Feed(crsf, b)) {
            return STATUS_CRSF_RECEIVED;
        }
    }
    return STATUS_CRSF_NOT_RECEIVED;
}
//----------------------------------------------------------------------------------------
void CRSF_DecodeChannels(const struct CRSF_TypeDef* crsf, uint16_t* channels) {
    const uint8_t* payload = &crsf->data[CRSF_OFFSET__PAYLOAD];
    channels[0]  = (payload[0]         | (payload[1]  << 8)) & 0x07FF;
    channels[1]  = ((payload[1]  >> 3) | (payload[2]  << 5)) & 0x07FF;
    channels[2]  = ((payload[2]  >> 6) | (payload[3]  << 2)  | (payload[4] << 10)) & 0x07FF;
    channels[3]  = ((payload[4]  >> 1) | (payload[5]  << 7)) & 0x07FF;
    channels[4]  = ((payload[5]  >> 4) | (payload[6]  << 4)) & 0x07FF;
    channels[5]  = ((payload[6]  >> 7) | (payload[7]  << 1)  | (payload[8] << 9)) & 0x07FF;
    channels[6]  = ((payload[8]  >> 2) | (payload[9]  << 6)) & 0x07FF;
    channels[7]  = ((payload[9]  >> 5) | (payload[10] << 3)) & 0x07FF;

    channels[8]  = (payload[11]        | (payload[12] << 8)) & 0x07FF;
    channels[9]  = ((payload[12] >> 3) | (payload[13] << 5)) & 0x07FF;
    channels[10] = ((payload[13] >> 6) | (payload[14] << 2)  | (payload[15] << 10)) & 0x07FF;
    channels[11] = ((payload[15] >> 1) | (payload[16] << 7)) & 0x07FF;
    channels[12] = ((payload[16] >> 4) | (payload[17] << 4)) & 0x07FF;
    channels[13] = ((payload[17] >> 7) | (payload[18] << 1)  | (payload[19] << 9)) & 0x07FF;
    channels[14] = ((payload[18] >> 2) | (payload[19] << 6)) & 0x07FF;
    channels[15] = ((payload[19] >> 5) | (payload[20] << 3)) & 0x07FF;
}
//========================================================================================
