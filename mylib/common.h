#ifndef COMMON_H
#define COMMON_H

#include <avr/wdt.h>
// Converts a bit number into a byte value.
#define _BV(bit) \
                (1 << (bit)) \

// Converts a bit number into a byte value.
#define _BIT(num) \
                (1 << (num)) \

// Set single bit to "1"
#define _SET_1(port_reg, pin) \
                        (port_reg |= _BV(pin)) \

// Set single bit to "0"
#define _SET_0(port_reg, pin) \
                        (port_reg &= ~_BV(pin)) \

// Set PORT(PIN) to Value
#define _SET_PIN(port_reg, pin,b) \
                        ((b) == 0 ? _SET_0((port_reg),(pin)): \
                        _SET_1((port_reg),(pin))) \

// Read Status of PORT(PIN)
#define _GET_PIN(pin_reg, pin) \
                        (((pin_reg) >> (pin)) & 0x01) \

// Changes PORT(PIN) Value
#define _TOGGLE_PIN(pin_reg, port_reg, pin) \
                        ((((pin_reg) >> (pin)) & 0x01) == 0 ? \
                        _SET_0((port_reg),(pin)): \
                        _SET_1((port_reg),(pin))) \

// Config PORT(PIN) to Input
#define _DIR_IN(dir_reg,num) \
                    (_SET_0((dir_reg),(num))) \

// Config PORT(PIN) to Out
#define _DIR_OUT(dir_reg,num) \
                    (_SET_1((dir_reg),(num))) \

#define _soft_reset()        \
    do                          \
    {                           \
        wdt_enable(WDTO_15MS);  \
        for(;;)                 \
        {                       \
        }                       \
    } while(0)
//

// Convert Hex string to int
int StrHexToInt(char *str, int len);

// Convert Dec string to int
int StrDecToInt(char *str, int len);


#endif