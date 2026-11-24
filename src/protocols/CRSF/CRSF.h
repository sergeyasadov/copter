#ifndef CRSF_PROTOCOL_H
#define CRSF_PROTOCOL_H


#include "CRSF_Defines.h"


void CRSF_DecodeChannels(const struct CRSF_TypeDef*, uint16_t*);

uint8_t CRSF_CRC8_Get(const uint8_t*, const uint_fast8_t);


#endif // CRSF_PROTOCOL_H
