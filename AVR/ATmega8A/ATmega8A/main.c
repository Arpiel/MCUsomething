/*
 * ATmega8A.c
 *
 * Created: 2019-02-27 오전 1:52:32
 * Author : 임경빈
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include<util/delay.h>
#include<util/twi.h>
int main(void)
{
    /* Replace with your application code */
	DDRB=0xff;
	DDRC=0xff;
	int counter;
    while (1) 
    {
		_delay_ms(1000);
		counter++;
		BSEG(counter%10);
		CSEG(counter/10);
		if(counter>=99)
			counter=0;
    }
}
int BSEG(int num)
{
	switch (num)
	{
	case 1:
		PORTB=01100000;
	case 2:
		PORTB=11011100;
	case 3:
		PORTB=11110100;
	case 4:
		PORTB=01100110;
	case 5:
		PORTB=10110110;
	case 6:
		PORTB=10111110;
	case 7:
		PORTB=11100010;
	case 8:
		PORTB=11111110;
	case 9:
		PORTB=11100110;
	case 0:
		PORTB=11111010;
	break;
	}
}
int CSEG(int num)
{
	switch (num)
	{
		case 1:
			PORTC=01100000;
		case 2:
			PORTC=11011100;
		case 3:
			PORTC=11110100;
		case 4:
			PORTC=01100110;
		case 5:
			PORTC=10110110;
		case 6:
			PORTC=10111110;
		case 7:
			PORTC=11100010;
		case 8:
			PORTC=11111110;
		case 9:
			PORTC=11100110;
		case 0:
			PORTC=11111010;
		break;
	}
	
}
	
	
	
