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

void glcd_set_page(uint16_t lcdpage)
{
	/*
	 *lcdpage aufteilung von 16 bits auf 8 bit wenn pa4 gesetzt ist noch nicht gemacht 
	 * 
	 * 
	 * 
	 */
	
	
	
	
	glcd_write(CONTROL, 96+lcdpage);//set page adress 0 (vertical) 96 weil 0b0110xxxx
	
	if(lcdpage<15)
	{
		glcd_write(CONTROL, 0b01110000);
	}
	else//set PA4 when page higher 15
	{
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
	glcd_write(CONTROL, 0b10101101);	//set display enable , b/w mode
	
	glcd_write(CONTROL, 0x00);glcd_write(CONTROL, 0x00);glcd_write(CONTROL, 0x00);//set column to 0
	
	glcd_write(CONTROL, 0b10001001);//RAM adddres control /select vertical or horizontal write
	glcd_set_page(0);
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
	
	for(x=0;x<10;x++)
	{
		glcd_set_page(x);
		
		for(yy=0;yy<100;yy++)
		{
			glcd_write(DATA, 0xFF);
				//glcd_write(DATA, 0xFF);
			_delay_ms(20);
		}
		glcd_write(CONTROL, 0x00);glcd_write(CONTROL, 0x00);glcd_write(CONTROL, 0x00);//set column to 0
	}
	while(1)
	{
	
			
	
	
	
	
	
	
	
	
	}//end of while

}//end of main
