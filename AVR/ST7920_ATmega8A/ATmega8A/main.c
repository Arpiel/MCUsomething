/*
 * ATmega8A.c
 *
 * Created: 2019-02-27 오전 1:52:32
 * Author : 임경빈
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include<util/delay.h>
void spi_send(unsigned char b)
{
	SPDR = b;
	while (!(SPSR & 0x80))
	{
	}
}
void lcd_instruction(unsigned char ins)
{
	spi_send(0b11111000);
	spi_send(ins & 0xf0);
	spi_send(ins << 4);
	_delay_us(72);
}
void lcd_data(unsigned char data)
{
	spi_send(0b11111010);
	spi_send(data & 0xf0);
	spi_send(data << 4);
	_delay_us(72);
}
void lcd_set_cursor(unsigned char line, unsigned char col)
{
	unsigned char d = 0x80 + col;
	if (line & 1)
	{
		d |= 0x10;
	}
	if (line & 2)
	{
		d |= 0x8;
	}
	lcd_instruction(d);
}
void lcd_clear()
{
	lcd_instruction(0b00000001); 
	_delay_us(2);
}
void lcd_reset()
{
	PORTB &= ~0x01;
	_delay_ms(1);
	PORTB |= 0x01;
	_delay_us(10);
	lcd_instruction(0b00110000);
	lcd_instruction(0b00001100);
	lcd_clear();
	_delay_us(10);
	lcd_instruction(0b00000110); 
}
char string_1[] = { "Hello, World!"};
void lcd_send_str_p(char *str)
{
	unsigned char p;
	while (str[++p] != '\0')
	{
		lcd_data(str[p]);
		p++;
	}
}
int main(void)
{
	DDRB=0xff;
	SPCR = 0b01011101;
	SPSR = 0b00000001;
	lcd_reset();
	int c,i;
	
	while(1)
	{
	   lcd_clear();
	   lcd_instruction(0x80);
	   for (int atx=0x00;atx<=0xF8;atx++)
	   {
		   for(int i=0;i<=256;i++)
		   {
			   lcd_data(atx);
			   lcd_data(i);
			   _delay_ms(10);
		   }
		   	   _delay_ms(100);
	   }
	   
	}
}
	
	
