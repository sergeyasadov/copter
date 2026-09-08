#include "CRSF.h"

#include "../defines.h"
#include "../utils/crc8.h"



#define CRSF_SYNC_BYTE 0xC8


__STATIC_INLINE void _USART1_SendByte(uint8_t byte) {
    while(!(USART1->SR & USART_SR_TXE));
    USART1->DR = byte;
}


__STATIC_INLINE void _USART1_SendString(const char* str) {
    while(*str)
        _USART1_SendByte((uint_fast8_t)*str++);
}


__STATIC_INLINE uint8_t _USART1_ReceiveByte(void) {
    while(!(USART1->SR & USART_SR_RXNE));
    return (uint8_t)(USART1->DR & 0xFF);
}


void CRSF_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    if(!(RCC->APB2ENR & RCC_APB2ENR_IOPBEN))
        RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;


    if(!(RCC->APB2ENR & RCC_APB2ENR_AFIOEN))
        RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    AFIO->MAPR |= AFIO_MAPR_USART1_REMAP;

    GPIOB->CRL &= ~((0b1111u << (4 * ELRS_TX)));
    GPIOB->CRL |= (0b1011u << (4 * ELRS_TX));

    GPIOB->CRL &= ~((0b1111u << (4 * ELRS_RX)));
    GPIOB->CRL |= (0b0100u << (4 * ELRS_RX));

    USART1->BRR = 0xAB;

    USART1->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}


int CRSF_Receive(struct CRSF_TypeDef* crsf) {
    if(_USART1_ReceiveByte() == CRSF_SYNC_BYTE) {
        crsf->data[0] = CRSF_SYNC_BYTE;

        const uint8_t frameLength = _USART1_ReceiveByte();
        crsf->data[CRSF_OFFSET__FRAME_LENGTH] = frameLength;

        if(frameLength > 62 || frameLength < 2) {
            return 0;
        }

        for(uint_fast8_t i = 0; i < frameLength; i++) {
            crsf->data[CRSF_OFFSET__TYPE + i] = _USART1_ReceiveByte();
        }

        uint8_t checkCRC8 = crc8(&crsf->data[CRSF_OFFSET__TYPE], frameLength - 1u);

        return (checkCRC8 == crsf->data[CRSF_OFFSET__TYPE + frameLength - 1u]);
    }
    return 0;
}


void CRSF_DecodeChannels(const struct CRSF_TypeDef* crsf, uint16_t* channels) {
    const uint8_t* payload = &crsf->data[CRSF_OFFSET__PAYLOAD];
    channels[0]  = (payload[0]        | (payload[1]  << 8)) & 0x07FF;
    channels[1]  = ((payload[1]  >> 3) | (payload[2]  << 5)) & 0x07FF;
    channels[2]  = ((payload[2]  >> 6) | (payload[3]  << 2) | (payload[4] << 10)) & 0x07FF;
    channels[3]  = ((payload[4]  >> 1) | (payload[5]  << 7)) & 0x07FF;
    channels[4]  = ((payload[5]  >> 4) | (payload[6]  << 4)) & 0x07FF;
    channels[5]  = ((payload[6]  >> 7) | (payload[7]  << 1) | (payload[8] << 9)) & 0x07FF;
    channels[6]  = ((payload[8]  >> 2) | (payload[9]  << 6)) & 0x07FF;
    channels[7]  = ((payload[9]  >> 5) | (payload[10] << 3)) & 0x07FF;

    channels[8]  = (payload[11]       | (payload[12] << 8)) & 0x07FF;
    channels[9]  = ((payload[12] >> 3) | (payload[13] << 5)) & 0x07FF;
    channels[10] = ((payload[13] >> 6) | (payload[14] << 2) | (payload[15] << 10)) & 0x07FF;
    channels[11] = ((payload[15] >> 1) | (payload[16] << 7)) & 0x07FF;
    channels[12] = ((payload[16] >> 4) | (payload[17] << 4)) & 0x07FF;
    channels[13] = ((payload[17] >> 7) | (payload[18] << 1) | (payload[19] << 9)) & 0x07FF;
    channels[14] = ((payload[18] >> 2) | (payload[19] << 6)) & 0x07FF;
    channels[15] = ((payload[19] >> 5) | (payload[20] << 3)) & 0x07FF;
}
