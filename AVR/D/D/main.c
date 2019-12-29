#define F_CPU 16000000
#include <avr/io.h>
#include "util/delay.h"
#include <stdio.h>
#include <avr/interrupt.h>
void UART0_init(void);
void UART0_send(unsigned char Data, FILE* fp);
int num=0;
int main(void)
{
	DDRE=0x00;
	PORTD=0x00;
	DDRB=0x0F;
	DDRE=0x02;
	EIFR=0x00;
	EIMSK=(1<<INT0)|(1<<INT1);
	EICRA=(1<<ISC00)|(1<<ISC01)|(1<<ISC10)|(1<<ISC11);
	sei();
	while(1)
	{
		printf("%d", num);
		_delay_ms(100);
	}
}
void UART0_init(void)
{
	
	UCSR1A=0x20;
	UCSR1B=0x18;
	UCSR1C=0x06;
	
	UBRR1H=0x00;
	UBRR1L=0x67;
	
}
void UART0_send(unsigned char Data,FILE* fp)
{
	while((UCSR1A&0x20)==0);
	UDR1=Data;
}
ISR(INT0_vect)
{
	num++;
}
ISR(INT1_vect)
{
	num=0;
}