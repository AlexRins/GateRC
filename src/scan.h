#ifndef SCAN_H
#define SCAN_H

#include <avr/io.h>

#define IN_PORT PORTD
#define IN_DIR DDRD
#define IN_PIN PIND
#define IN_R PIND2
#define IN_F PIND3

#define EDGES_COUNT 50

#define T1_EN _SET_1(TIMSK1,OCIE1A) // enable interupt on timer 1 compare match
#define T1_DIS _SET_0(TIMSK1,OCIE1A) // disable interupt on timer 1 compare match

#endif

// tetst line
