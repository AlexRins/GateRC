/* scan */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

// Local libraries
#include "stdio_wrap.h"
#include "common.h"
#include "scan.h"

volatile int16_t t1;


ISR (INT0_vect){
// Rising edge interupt
    cli();
    t1 = TCNT0;
    TCNT0 = 0;    
    sei();
}

ISR (INT1_vect){
// Failing edge interupt

}

int main(void){
    
    usart_init();
    // setting timer 1
    

    printf("test");

    _DIR_IN(IN_DIR, IN_R);            // data input "in" rising edge
    _DIR_IN(IN_DIR, IN_F);            // data input "in" failing edge

    cli();                              // disable interupts globaly
    
    EICRA = 0;

    _SET_0(EICRA, ISC10);               
    _SET_1(EICRA, ISC11);               // enable interupt Failing edge on INT1 (D3)

    _SET_1(EICRA, ISC00);
    _SET_1(EICRA, ISC01);               // enable interupt for Rising edge on INT0 (D2)

    _SET_1(EIMSK, INT0);
    _SET_1(EIMSK, INT1);                // enable INT0 and INT1


    // https://www.arxterra.com/9-atmega328p-timers/
}
