
//#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>

#define RD_LOW			PORTB &= ~(1<<PB0)
#define RD_HIGH			PORTB |= (1<<PB0)
#define WR_LOW			PORTB &= ~(1<<PB1)
#define WR_HIGH			PORTB |= (1<<PB1)
#define CONTROL_DATA	PORTB &= ~(1<<PB2)
#define DISPLAY_DATA	PORTB |= (1<<PB2)
#define RST_HIGH		PORTB |= (1<<PB3)
#define RST_LOW			PORTB &= ~(1<<PB3)
#define CS_HIGH 		PORTB |= (1<<PB4)
#define CS_LOW			PORTB &= ~(1<<PB4)
#define DATA_REGISTER 	PORTB

#define DATA 	0	
#define CONTROL 1



void glcd_rst(void)
{
	//reset glcd
	RST_LOW;
	_delay_ms(1);
	RST_HIGH;
}

//send Data / Control byte to graphic controller
//dc = 0 = data; dc = 1 = control
void glcd_wr_data(uint8_t dc, uint8_t data)
{
	CS_HIGH;	//chipselect on Display on
	WR_HIGH;
	RD_LOW;
	
	if(dc==0)DISPLAY_DATA;else CONTROL_DATA;//set dc pin according date to be sent
	DATA_REGISTER = data;	
	
	RD_HIGH;
	WR_HIGH; //latch data into controller	
}

int main(void)
{
	
	DDRD = 0xFF;//Port D Output => Data register
	PORTD =0x00;//Low
	
	DDRB |= ((1<<PB0) |(1<<PB1) | (1<<PB2)| (1<<PB3)| (1<<PB4)); //RD,WR,D/C,RST,CS = Output
	
	
	
	
	//init lcd
	CS_HIGH;	//cip select on
	glcd_rst();	//reset display
	
	
	while(1)
	{
	
	
	
	}//end of while

}//end of main
