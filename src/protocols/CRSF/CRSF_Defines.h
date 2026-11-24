#ifndef CRSF_DEFINES_H
#define CRSF_DEFINES_H

#include <stdint.h>


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


struct CRSF_TypeDef {
    uint8_t data[64];
    uint_fast8_t len;
};


#endif // CRSF_DEFINES_H
