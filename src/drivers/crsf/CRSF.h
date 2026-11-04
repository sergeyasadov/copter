#ifndef CROSSFIRE_H
#define CROSSFIRE_H


#include <stdint.h>


struct CRSF_TypeDef {
    uint8_t data[64];
    uint_fast8_t len;
};

void CRSF_Init(struct CRSF_TypeDef*);

uint32_t CRSF_Receive(struct CRSF_TypeDef*) __attribute__((warn_unused_result));

void CRSF_DecodeChannels(const struct CRSF_TypeDef*, uint16_t*);


#endif //
