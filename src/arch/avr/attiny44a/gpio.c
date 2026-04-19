#include "gpio.h"


#define getReg(port, a, b) (((port == PORTA) ? (a) : (b)))
#define getRegPort(port) getReg(port, PORTA, PORTB)
#define getRegPin(port) getReg(port, PINA, PINB)
#define getRegDir(port) getReg(port, DDRA, DDRB)


/// INTERNAL

static inline 
__ATTR_ALWAYS_INLINE__ 
void setBit(volatile uint8_t* r, uint8_t v) {
    *r |= _BV(v);
}


// static inline 
// __ATTR_ALWAYS_INLINE__
// void clearBit(uint8_t r, uint8_t v) {
//     _SFR_IO8(r) &= ~_BV(v);
// }


/// EXTERNAL

void GPIO_Init(GPIO_t* gpio) {
    GPIO_SetDir(gpio, gpio->dir);
    // GPIO_Write(gpio, GPIO_LEVEL__LOW);
}


// void GPIO_Write(GPIO_t* gpio, GPIO_Level_t level) {
//     if(level == GPIO_LEVEL__HIGH) {
//         setBit(getRegPort(gpio->port), gpio->pin);
//     } 
//     else {
//         clearBit(getRegPort(gpio->port), gpio->pin);
//     }
// }


// GPIO_Level_t GPIO_Read(const GPIO_t* gpio) {
//     return getRegPin(gpio->port) & _BV(gpio->pin);
// }


void GPIO_SetDir(GPIO_t* gpio, GPIO_Dir_t ndir) {
    gpio->dir = ndir;
    if(gpio->dir == GPIO_DIR__OUTPUT) {
        setBit((volatile uint8_t*)getRegDir(gpio->port), gpio->pin);
    }
    // else {
    //     clearBit(getRegDir(gpio->port), gpio->pin);
    // }
}


// void GPIO_SetHigh(GPIO_t* gpio) {
//     setBit(getRegPort(gpio->port), gpio->pin);
// }


// void GPIO_SetLow(GPIO_t* gpio) {
//     clearBit(getRegPort(gpio->port), gpio->pin);
// }


// void GPIO_SetToggle(GPIO_t* gpio) {
//     GPIO_Write(gpio, GPIO_Read(gpio) == GPIO_LEVEL__LOW);
// }