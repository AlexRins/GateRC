#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H


#include <stdio.h>

#define SCAN_BUFF_SIZE 20
#define SCAN_END_LINE '\n'

#define BIT_SET(reg,bit_num) ((reg) |= (1 << bit_num))
#define BIT_CLR(reg,bit_num) ((reg) &= (~(1<<bit_num)))

enum parity {NO_PARITY=0,ODD_PARITY=3,EVEN_PARITY=2};
enum stopbit {ONE_STOPBIT=1,TWO_STOPBIT=2};

int scan(char *inString, const char endline=SCAN_END_LINE);
int usart_init (int baud=9600,int bitCount=8,parity par=NO_PARITY,stopbit stopbit=ONE_STOPBIT);
int usart_putchar (char data, FILE *t);
int usart_getchar(FILE *t);
void usart_redirectStdIOE(void);

#endif
