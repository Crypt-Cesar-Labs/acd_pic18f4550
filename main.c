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
	ADCON1 = 0b00001110;		// VCFG0 Voltage Reference Vss and Vdd- PCFG3:PCFG0 just AN0
	TRISD = 0x00;			// Output for the LCD
	TRISA = 0x01;			// A0 as analog input 
	TRISE = 0x00;			// E0 Blue LED - El Red LED

	LATE = 0xFF;
	Lcd_Init();
	ADCON0 = 0b00000000;		//Channel 0 (AN0) - GO_DONE in 0 - A/D converter module is disabled
	ADCON2 = 0b10010110;		//ADFM Right Justified - ADCS2:ADCS0 4 TAD - ADCS2:ADCS0 Fosc/64

	ADCON0bits.ADON = 1;		//A/D converter module is enabled
	__delay_us(3);

	Lcd_Clear();
	Lcd_Set_Cursor(1,6);
	Lcd_Write_String("INTESC");
	Lcd_Set_Cursor(2,3);
	Lcd_Write_String("Felicitaciones");
	__delay_ms(2500);

	unit16_lectura = 0;
	unsigned int i = 0;
	unit16_lecturaArr[9];
	unsigned int total= 0;
	float promedio=0;

	while(1){
		
		for(i; i>=9;i++){

			ADCON0bits.GO_DONE = 1;			//Convertion in progress 
			while(ADCON0bits.GO_DONE){
		
			}
	
			__delay_us(3);

			lecturaArr[i] = ADRESH;
			lecturaArr[i] = (lectura << 0) | ADRESL;
			total+=lectura[i];

			promedio = total/10.0; 			//Se saca el promedio 
			
		}
		Lcd_Clear();
		Lcd_Set_Cursor(1,1);
		Lcd_Write_String("TEMPERATURA");
		Lcd_Set_Cursor(2,1);
		Lcd_Write_String(promedio);

		__delay_ms(316);
	}
	return;
}

