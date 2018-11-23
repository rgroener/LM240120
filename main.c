#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>

#define RD_LOW			PORTC &= ~(1<<PC1)
#define RD_HIGH			PORTC |= (1<<PC1)
#define WR_LOW			PORTC &= ~(1<<PC2)
#define WR_HIGH			PORTC |= (1<<PC2)
#define DISPLAY_CONTROL	PORTC &= ~(1<<PC3)
#define DISPLAY_DATA	PORTC |= (1<<PC3)
#define RST_HIGH		PORTC |= (1<<PC4)
#define RST_LOW			PORTC &= ~(1<<PC4)
#define CS_HIGH 		PORTC |= (1<<PC5)
#define CS_LOW			PORTC &= ~(1<<PC5)
#define DATA_REGISTER 	PORTD

#define DATA 	1	
#define CONTROL 0
void glcd_rst(void)
{
	
	CS_HIGH;
	_delay_ms(3);
	RST_HIGH;
	_delay_ms(1);
	RST_LOW;
	_delay_ms(10);
	RST_HIGH;
	_delay_ms(10);
	CS_LOW;
}

//send Data / Control byte to graphic controller
//dc =1 = data; dc = 0 = control
void glcd_wr_data(int dc, int data)
{
	if(dc==CONTROL)DISPLAY_CONTROL; else DISPLAY_DATA;//set dc pin according date to be sent
	PORTD = data;	//set date to be sent
	CS_HIGH;		//enable lcd
	RD_HIGH;		//write data; RD_LOW=read data
	WR_HIGH; 		//latch data into controller	
	WR_LOW;
	CS_LOW;			//disable lcd
}
void glcd_init(void)
{
	glcd_rst();	//reset lcd
	WR_LOW;		//default value for WR /ready to latch data
	glcd_wr_data(CONTROL, 0b10000001);glcd_wr_data(CONTROL, 0b11110000);	//set elec Volume PM / double command
	glcd_wr_data(CONTROL, 0b10101111);	//set display enable , grey mode
	glcd_wr_data(CONTROL, 0b10100101);//set all pixel on
}


int main(void)
{
	
	DDRD = 0xFF;//Port D Output => Data register
	PORTD =0x00;//Low
	
	DDRC |= ((1<<PC1) |(1<<PC2) | (1<<PC3)| (1<<PC4)| (1<<PC5)); //RD,WR,D/C,RST,CS = Output
	PORTC &= ~((1<<PC1) |(1<<PC2) | (1<<PC3)| (1<<PC4)| (1<<PC5)); //RD,WR,D/C,RST,CS = Low
	
	DDRB |= (1<<PB0);
	PORTB |= (1<<PB0);
	//_delay_ms(5);	//delay for lcd to be stable
	glcd_rst();		//reset lcd
	glcd_init();	//initialise lcd
	
	while(1)
	{
	
	
	
	
	
	}//end of while

}//end of main
