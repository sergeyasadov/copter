#ifndef CROSSFIRE_H
#define CROSSFIRE_H

#include <stdint.h>

#define CRSF_OFFSET__SYNC_BYTE 0u
#define CRSF_OFFSET__FRAME_LENGTH 1u
#define CRSF_OFFSET__TYPE 2u
#define CRSF_OFFSET__PAYLOAD 3u



struct CRSF_TypeDef {
    uint8_t data[64];
    uint_fast8_t len;
};


void CRSF_Init(struct CRSF_TypeDef*);

uint32_t CRSF_Receive(struct CRSF_TypeDef*) __attribute__((warn_unused_result));

void CRSF_DecodeChannels(const struct CRSF_TypeDef*, uint16_t*);


#endif //
