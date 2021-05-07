
#include <stdio.h>
#include <avr/io.h>
#include "stdio_wrap.h"

//static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);
static FILE* usart_stream;


// Initiate UART and redirect standart stream to it
int usart_init (int baud,int bitCount,parity par,stopbit stopbit){
  /* Reset register */
    UCSR0A = 0x0;
    UCSR0B = 0x0;
    UCSR0C = 0x0;

  /* Set mode Asynchronous USART */
    //BIT_CLR(UCSR0C,UMSEL00);
    //BIT_CLR(UCSR0C,UMSEL01);

  /* Set parity */
    switch (par)
    {
      case NO_PARITY:
        BIT_CLR(UCSR0C,UPM00);
        BIT_CLR(UCSR0C,UPM01);
        break;
      
      case EVEN_PARITY:
        BIT_CLR(UCSR0C,UPM00);
        BIT_SET(UCSR0C,UPM01);
        break;
      
      case ODD_PARITY:
        BIT_SET(UCSR0C,UPM00);
        BIT_SET(UCSR0C,UPM01);
        break;
      
      default: // NO_PARITY
        BIT_CLR(UCSR0C,UPM00);
        BIT_CLR(UCSR0C,UPM01);
        break;
    }
  
  /* Set stop bit */
    if(stopbit == ONE_STOPBIT){
      BIT_CLR(UCSR0C,USBS0);
    }else{
      BIT_SET(UCSR0C,USBS0);
    }
    
  /* Set Speed*/
    BIT_SET(UCSR0A,U2X0);
    unsigned int prescaler = (unsigned int)(F_CPU / (((UCSR0A & (1<<U2X0)) ? 8UL : 16UL) * baud)) - 1;
    UBRR0H = prescaler >> 8;
    UBRR0L = prescaler;
    //UBRR0 = (F_CPU / ( 16 * baud)) - 1;
  /* Set bit count*/
    switch (bitCount){
      case 5:
        /* code */
        BIT_CLR(UCSR0C,UCSZ00);
        BIT_CLR(UCSR0C,UCSZ01);
        BIT_CLR(UCSR0B,UCSZ02);
        break;
      case 6:
        /* code */
        BIT_CLR(UCSR0C,UCSZ00);
        BIT_CLR(UCSR0C,UCSZ01);
        BIT_SET(UCSR0B,UCSZ02);
        break;
      case 7:
        /* code */
        BIT_CLR(UCSR0C,UCSZ00);
        BIT_SET(UCSR0C,UCSZ01);
        BIT_CLR(UCSR0B,UCSZ02);
        break;
      case 8:
        /* code */
        BIT_SET(UCSR0C,UCSZ00);
        BIT_SET(UCSR0C,UCSZ01);
        BIT_CLR(UCSR0B,UCSZ02);
        break;
      case 9:
        /* code */
        BIT_SET(UCSR0C,UCSZ00);
        BIT_SET(UCSR0C,UCSZ01);
        BIT_SET(UCSR0B,UCSZ02);
        break;
      default: // 8 bit
        /* code */
        BIT_SET(UCSR0C,UCSZ00);
        BIT_SET(UCSR0C,UCSZ01);
        BIT_CLR(UCSR0B,UCSZ02);
        break;
    }

  /* Enable Tx and RX */
    BIT_SET(UCSR0B,RXEN0);
    BIT_SET(UCSR0B,TXEN0);

  /* Redirect stdout to uart */
    usart_redirectStdIOE();
  return 0;
}

int usart_putchar (char data,FILE *t){
    // Wait for empty transmit buffer
    loop_until_bit_is_set(UCSR0A, UDRE0);
    // Start transmission
    UDR0 = data;    
    return 0;
}

int  usart_getchar(FILE *t)
{
    while( !(UCSR0A & (1<<RXC0)) );
    return(UDR0);
}

void usart_redirectStdIOE(){
  // Redirect stdout to uart
  usart_stream = fdevopen(&usart_putchar, &usart_getchar);
  stdin  = usart_stream;
  stdout = usart_stream;
  stderr = usart_stream;
}

int scan(char *inString,const char endline){
    int i=0;
    char currentChar='\0';  
    while((i <= SCAN_BUFF_SIZE-2)){
        currentChar = usart_getchar(NULL);
        if (currentChar == endline){
            inString[i] = '\0';
            break;
        }
        else{
            if(currentChar >= 32 && currentChar < 127 ){
                inString[i++] = currentChar;
            }
        }
    }
    inString[SCAN_BUFF_SIZE-1] = '\0';
    if( i == SCAN_BUFF_SIZE-2 && 
        inString[SCAN_BUFF_SIZE-2] != endline )
        {
            return -1;
    }else{
        return i;
    }
}