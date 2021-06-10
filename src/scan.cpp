/* scan */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

// Local libraries
#include "stdio_wrap.h"
#include "common.h"
#include "scan.h"



volatile int16_t t1[EDGES_COUNT] = {0xff}; // timing of high phase
volatile int16_t t0[EDGES_COUNT] = {0xff}; // timing of low phase
volatile unsigned char index = 0; // current counter index
volatile unsigned char preambleCount = 0;
volatile bool stopCount = false;


// Rising edge interupt
ISR (INT0_vect){

    cli();
    t0[index] = TCNT1;
    TCNT1 = 0;
    //_SET_1(EIMSK, INT1); // enable INT1 (failing edge)
    if(index != 0 ){
        if(preambleCount < 11){
            if(t0[index] == t0[index-1]){
                preambleCount++;
                index++;
            }
            else{
                preambleCount = 0;
                index = 0;
            }
        }
        else{
            if(index < EDGES_COUNT){
                index++;
            }
        }
    }
    else{
        index++;
    }
 
    sei();
}

// Failing edge interupt
ISR (INT1_vect){
    cli();
    t1 [index] = TCNT1;
    TCNT1 = 0;
     if (t1[index]==t0[index]){
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


int main(void){

    setup();

    while(true){
        if(index == EDGES_COUNT){
            _SET_0(EIMSK, INT0); // disable rising edge interupt
            for (unsigned char i=0; i<=EDGES_COUNT; i++){
                printf("%d, ",t0[i]);
            }
            index == 0;
            _SET_1(EIMSK, INT0);                // enable INT0 (rising edge)
        }
    }

}


