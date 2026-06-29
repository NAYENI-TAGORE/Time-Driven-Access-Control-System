#include<lpc21xx.h>
#include"delay.h"
#include "lcd.h"
#include "lcd_defines.h"
extern int flag;

void INT1_ISR(void) __irq
{
	flag = 1;
	EXTINT = 1<<1; 
	VICVectAddr = 0;
}
void Init_Interrupt()
{
	VICIntEnable = 1<<15;
	VICVectCntl0 = (1<<5) | 15;
	VICVectAddr0 = (unsigned)INT1_ISR;
	
	
	PINSEL0 |= 3<<6;
	EXTMODE |= 1<<1; // 
	EXTPOLAR &= ~(1<<1); 
}
