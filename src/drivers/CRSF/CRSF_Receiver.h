#ifndef CRSF_RECEIVER_DRIVER_H
#define CRSF_RECEIVER_DRIVER_H

#include <stdint.h>

struct CRSF_TypeDef;


void CRSF_Receiver_Init(struct CRSF_TypeDef*);

uint32_t CRSF_Receiver_Read(struct CRSF_TypeDef*);



#endif // CRSF_RECEIVER_DRIVER_H
