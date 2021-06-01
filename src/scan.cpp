/* scan */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

// Local libraries
#include "stdio_wrap.h"
#include "common.h"
#include "scan.h"



volatile int16_t t[EDGES_COUNT] = {0xff};
volatile unsigned char index = 0;
volatile unsigned char preambleCount = 0;
volatile unsigned char prevTime = 0;
volatile bool startCount = false;

ISR (INT0_vect){
// Rising edge interupt
    cli();
    t[index] = TCNT1;
    TCNT1 = 0;
    _SET_1(EIMSK, INT1); // enable INT1 (failing edge)
    if(index == 0){
        t[index] = 0;
    }
    sei();
}

ISR (INT1_vect){
// Failing edge interupt
    cli();
    t [index] = TCNT1;
    TCNT1 = 0;
    if (prevTime != 0)
    if (t[index-1]==t[index]){
        preambleCount++;
        index++;
    }else{
        preambleCount = 0;
    }

    if (index == EDGES_COUNT){
        index = 0;
    }
    sei();
}


// Configure timer 1
void setup_timer_1(void){
    // https://www.arxterra.com/9-atmega328p-timers/
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B
    _SET_1( TCCR1B, CS11); // prescaler = 8
    TCNT1 = 0;
}

// Setup
void setup(void){    
    usart_init();
    cli();                            // disable interupts globaly

    _DIR_IN(IN_DIR, IN_R);            // data input "in" rising edge
    _DIR_IN(IN_DIR, IN_F);            // data input "in" failing edge

    // Setting external interupts
    EICRA = 0;

    _SET_0(EICRA, ISC10);               
    _SET_1(EICRA, ISC11);               // enable interupt Failing edge on INT1 (D3)

    _SET_1(EICRA, ISC00);
    _SET_1(EICRA, ISC01);               // enable interupt for Rising edge on INT0 (D2)

    _SET_1(EIMSK, INT0);                // enable INT0 (rising edge)
    _SET_0(EIMSK, INT1);                // disable INT1 (failing edge) must beggin from rising edge

    setup_timer_1();
    sei();                               // enable interupts globaly

}

unsigned char inc_i(unsigned char inc){
    char i = 0;
    i = index + inc;
    if (i >= EDGES_COUNT){
        i = i - EDGES_COUNT;
    }
}

unsigned char dec_i(unsigned char dec){
    if (index == 0){
        index = EDGES_COUNT;
    }
    index--;

}

int main(void){

    setup();

    while(true){
        

        }

    }


}
