// PIC18F4550 con crystal de 8Mhz -> 48Mhz
#pragma config PLLDIV = 2,
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


