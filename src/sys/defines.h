#ifndef __DEFINES_H__
#define __DEFINES_H__

#define D_FREQ_MCU ((unsigned long)20e6)

#ifndef __AVR_ATtiny44A__
#   define __AVR_ATtiny44A__
#endif

#ifndef F_CPU
#   define F_CPU D_FREQ_MCU
#endif // F_CPU

#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
#include <stdbool.h>


#define SBIT(R, B) ((R) |= (B))
#define CBIT(R, B) ((R) &= ~(B))
#define TBIT(R, B) ((R) ^= (B))

#define SMBIT(R, B) (SBIT(R, ((1u) << (B))))
#define CMBIT(R, B) (CBIT(R, ((1u) << (B))))
#define TMBIT(R, B) (TBIT(R, ((1u) << (B))))

#define TWI_MASK_SDA (1 << PB1)
#define TWI_MASK_SCL (1 << PB0)
#define TWI_PORT_SDA PORTB
#define TWI_PORT_SCL PORTB
#define TWI_DDR_SDA DDRB
#define TWI_DDR_SCL DDRB




#endif // __DEFINES_H__
