// PIC18F4550 con crystal de 8Mhz -> 48Mhz
#pragma config PLLDIV = 2, CPUDIV = OSC1_PLL2, USBDIV =2
#pragma config FOSC = HSPLL_HS, FCMEN = OFF, IESO =OFF
#pragma config PWRT = OFF, BOR =OFF, VREGEN = OFF
#pragma config WDT = OFF
#pragma config MCLRE = ON, LPT1OSC = OFF, PSADEN = OFF
#pragma config SIVREN = OFF, LVP = OFF, ICPRT = OFF, XINST = OFF
#define _XTAL_FREQ 480000000

#define D4 LATDbits.LD0
#define D5 LATDbits.LD1
#define D6 LATDbits.LD2
#define D7 LATDbits.LD3
#define EN LATDbits.LD4
#define R5 LATDbits.LD5

#include <xc.h>
#include <stdint.h>
#include <pic18f4550>
#include "lcd.h"

void main(void){
	ADCON1 = 0b00001110;		//
	TRISD = 0x00;
	TRISA = 0x01;
	TRISE = 0x00;

	LATE = 0xFF;
	Lcd_Init();
	ADCON0 = 0b00000000;
	ADCON2 = 0b10010110;

	ADCON0bits.ADON = 1;
	__delay_us(3);

	Lcd_Clear();
	Lcd_Set_Cursor(1,6);
	Lcd_Write_String("INTESC");
	Lcd_Set_Cursor(2,3);
	Lcd_Write_String("Felicitaciones");
	__delay_ms(2500);

	unit16_lectura = 0;

	while(1){
		ADCON0bits.GO_DONE = 1;
		while(ADCON0bits.GO_DONE){
		
		}

		__delay_us(3);

		lectura = ADRESH;
		lectura = (lectura << 0) | ADRESL;

		if (lectura > 512){
			LATE = 0b11111101;
			Lcd_Set_Cursor(1,1);
			Lcd_Write_String("!!!!!PELIGRO!!!!");
			Lcd_Set_Cursor(2,1);
			Lcd_Write_String("ALTA TEMPERATURA");
		}
		else{
			LATE=0xFE;
			Lcd_Clear();
			Lcd_Set_Cursor(1,2);
			Lcd_Write_String("Felix Armenta");
			Lcd_Set_Cursor(2,3);
			Lcd_Write_String("RANGO NORMAL");
		}
		__delay_ms(316);
	}
	return;
}

