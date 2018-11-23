
//#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>

#define RD_LOW			PORTC &= ~(1<<PC1)
#define RD_HIGH			PORTC |= (1<<PC1)
#define WR_LOW			PORTC &= ~(1<<PC2)
#define WR_HIGH			PORTC |= (1<<PC2)
#define CONTROL_DATA	PORTC &= ~(1<<PC3)
#define DISPLAY_DATA	PORTC |= (1<<PC3)
#define RST_HIGH		PORTC |= (1<<PC4)
#define RST_LOW			PORTC &= ~(1<<PC4)
#define CS_HIGH 		PORTC |= (1<<PC5)
#define CS_LOW			PORTC &= ~(1<<PC5)
#define DATA_REGISTER 	PORTD

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
//dc =1 = data; dc = 0 = control
void glcd_wr_data(uint8_t dc, uint8_t data)
{
	
	
	PORTC &= ~(1<<PC3);//if(dc==1)DISPLAY_DATA;else CONTROL_DATA;//set dc pin according date to be sent
	PORTD = data;	
	CS_HIGH;
	RD_HIGH;
	WR_LOW;
	WR_HIGH; //latch data into controller	
	CS_LOW;
}

int main(void)
{
	
	DDRD = 0xFF;//Port D Output => Data register
	PORTD =0x00;//Low
	
	DDRC |= ((1<<PC1) |(1<<PC2) | (1<<PC3)| (1<<PC4)| (1<<PC5)); //RD,WR,D/C,RST,CS = Output
	PORTC &= ~((1<<PC1) |(1<<PC2) | (1<<PC3)| (1<<PC4)| (1<<PC5)); //RD,WR,D/C,RST,CS = Low
	
	DDRB |= (1<<PB0);
	PORTB |= (1<<PB0);
	
	RST_HIGH;
	CS_HIGH;//lcd enable
	
	_delay_ms(10);
	RST_LOW;
	_delay_ms(10);
	RST_HIGH;
	_delay_ms(10);
	
	
	glcd_wr_data(CONTROL,0b11101011);//Bias Ratio default
	_delay_ms(10);
	glcd_wr_data(CONTROL,0b10000001);//V-Biassetting default
	_delay_ms(10);
	glcd_wr_data(CONTROL,0b00101101);//Pump Control default
	_delay_ms(10);
	glcd_wr_data(CONTROL,0b10101101);//Display Enable
	_delay_ms(10);
	glcd_wr_data(CONTROL,0b10100100);//set all pixel on
	_delay_ms(10);
	/*
	 RESET_LOW; delayms(2);      // hardware reset
  RESET_HIGH; delayms(800);    //ždelay after more than 800ms time
  ContrastLevel=0x91;      //
  SdCmd(0x26);                                // set the temperature compensation factor -0.15% / C
  SdCmd(0x2b);                                // drive the load
  SdCmd(0x2d);                                // internal Vlcd

  SdCmd(0xc4);                                // LCD image MY = 0, MX = 1, LC0 = 0 c2
  SdCmd(0xc8); SdCmd(0x00);                   // set M signal to frame flip
  SdCmd(0xeb);                                // Set the bias ratio 1/11


  SdCmd(0x81); SdCmd(ContrastLevel);          // set the contrast
  SdCmd(0x84);                                // set the local display is invalid
  SdCmd(0x86);                                // interlaced
  SdCmd(0x89);                // address increment rule setting
  SdCmd(0x95);                                // monochrome data format, the display RAM points to the first page 95

  SdCmd(0xf1);SdCmd(0x77);          //End line CEN, 127
  SdCmd(0xf2);SdCmd(0x00);          //start DST
  SdCmd(0xf3);SdCmd(0x77);          //end DEN

  SdCmd(0xa1);                                // Set the line scan frequency fr = 69.44hz
  SdCmd(0xa4);                                // normal display
  SdCmd(0xa6);                                // positive display
  SdCmd(0xad);   delayms(100);                // show ad
	
	
	*/
	//init lcd
	//CS_HIGH;	//cip select on
	//glcd_rst();	//reset display
	
	//DDRC |= (1<<PC1);
//	PORTC |= (1<<PC1);
	//CS_HIGH;
//WR_LOW;


	
	while(1)
	{
	
	
	
	}//end of while

}//end of main
