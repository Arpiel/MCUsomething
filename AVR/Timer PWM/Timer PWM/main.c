/*
 * Timer PWM.c
 *
 * Created: 2019-12-27 오후 3:41:16
 * Author : 임경빈
 * ADC를 이용해서 PWM듀티사이클을 제어하는 코드.
 */ 

#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	int duty=0;
    ADMUX=(1<<REFS0)|(1<<ADLAR)|(1<<MUX0);
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADIE);
	DDRB=0x10;
	PORTB=0x10;
	TCCR0=(1<<CS00)|(1<<CS01)|(1<<CS02)|(1<<WGM01)|(1<<WGM00)|(1<<COM00)|(1<<COM01);
    while (1) 
    {
		ADCSRA|=0x40;
		ADCSRA|=0x10;
		while((ADCSRA&ADIF)==0);
		duty=ADC/4;
		OCR0=duty;
    }
}

