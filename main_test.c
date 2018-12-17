/*
 * 
 * Library to graphic LCD Display
 * Resolution:	240 x 120
 * LCD:			 240120H
 * Controller:	UC1618T
 * 
 * RGroener
 * Compiler avr-gcc 
 * 
 * 
 * 
 * 
 * */
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
void glcd_write(int dc, int data)
{
	if(dc==CONTROL)DISPLAY_CONTROL; else DISPLAY_DATA;//set dc pin according date to be sent
	PORTD = data;	//set date to be sent
	CS_HIGH;		//enable lcd
	RD_HIGH;		//write data; RD_LOW=read data
	WR_HIGH; 		//latch data into controller	
	WR_LOW;
	CS_LOW;			//disable lcd
}

void glcd_clear_screen(void)
{
	uint32_t x=0;
	
	for(x=0;x<8200;x++)
	{
		glcd_write(DATA, 0x00);
		//_delay_ms(1);
	}
	
}
void glcd_set_column(uint16_t lcdcol)
{
	/*set column (1 bit wide) to write data
	 * 0 ~ 267
	 */
	glcd_write(CONTROL, 0x00);//set column address command
	if(lcdcol<255)
	{
		glcd_write(CONTROL, lcdcol+14);//last 8 bits  14=offset column
		glcd_write(CONTROL, 0);//highest bit of colums value
	}else
	{
		glcd_write(CONTROL, lcdcol-255);//last 8 bits
		glcd_write(CONTROL, 1);//highest bit of colums value
	}
	
}
void glcd_set_page(uint16_t lcdpage)
{
	/*set page (8 bit high) to write data
	 * 0 ~ 31?
	 */
	if(lcdpage<16)
	{
		glcd_write(CONTROL, 96+lcdpage);//set page adress 0 (vertical) 96 weil 0b0110xxxx
		glcd_write(CONTROL, 0b01110000);//PA4 not set
	}
	else//set PA4 when page higher 15
	{
		glcd_write(CONTROL, 96+lcdpage-16);//set page adress 0 (vertical) 96 weil 0b0110xxxx / -16 weil MSB (PA4) in next bit
		glcd_write(CONTROL, 0b01110001);//set PA4 when page higher 15
	}
}

void glcd_init(void)
{
	glcd_rst();	//reset lcd
	WR_LOW;		//default value for WR /ready to latch data
	glcd_write(CONTROL, 0b00100100);//set temp compensation -0.5% /grad C
	glcd_write(CONTROL, 0b00101101);//set pump control internal 10x
	glcd_write(CONTROL, 0b10000100);//partial display control disabled
	glcd_write(CONTROL, 0b10000110);//interlace scan
	glcd_write(CONTROL, 0b11101011);//set bias ratio 11
	glcd_write(CONTROL, 0b10000001);glcd_write(CONTROL, 170);	//set elec Volume PM / double command
	glcd_write(CONTROL, 0b10001001);//RAM adddres control /select vertical or horizontal write
	glcd_write(CONTROL, 0b10101101);	//set display enable , b/w mode
	
	
	/*glcd_write(CONTROL, 0b11111001);//window program enable
	
	glcd_write(CONTROL, 0b11110100);//set window program staring column address
	glcd_write(CONTROL, 14);//window starting at column 0
	glcd_write(CONTROL, 0);//last bit of column data
	
	
	
	glcd_write(CONTROL, 0b11110101);//set window program starting page address
	glcd_write(CONTROL, 0);//window starting at page 0
	
	glcd_write(CONTROL, 0b11110110);//set window program ending column address
	glcd_write(CONTROL, 254);//window ending at column
	glcd_write(CONTROL, 0);//last bit of column data
	
	glcd_write(CONTROL, 0b11110111);//set window program ending page address
	glcd_write(CONTROL, 31);//window ending at page 31
	* 
	* */
	
	//glcd_write(CONTROL, 0b11000010);//
	
	
	
	
	
	glcd_set_page(0);
	glcd_set_column(0);
	glcd_clear_screen();
}


uint16_t yy,x;

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
	
	
	
	
	glcd_clear_screen();
	
	
	glcd_set_page(0);
	glcd_set_column(200);
	for(x=0;x<1000;x++)
	{
		glcd_write(DATA, 200);
	}		

		
		
	
	
	
	
	
	
	
	while(1)
	{
	
			
	
	
	
	
	
	
	
	
	}//end of while

}//end of main
