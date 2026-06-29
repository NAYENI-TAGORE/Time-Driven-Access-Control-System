//rtc.c
#include<lpc21xx.h>
#include "types.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "lcd_defines.h"
#include "lcd.h"
#include "delay.h"
#include "kpm.h"


char week[][10] = {"SUN","MON","TUE","WED","THU","FRIDAY","SAT"};

// RTC Initialization: Configures and enables the RTC
void RTC_Init(void) 
{
  // Disable and reset the RTC
	CCR = RTC_RESET;
  
#ifdef _LPC2148
  // Enable the RTC & select the clock source
	CCR = RTC_ENABLE | RTC_CLKSRC;  
#else
  // Set prescaler integer and fractional parts
	PREINT = PREINT_VAL;
	PREFRAC= PREFRAC_VAL;
  
  // Enable the RTC
	CCR = RTC_ENABLE;  
	
#endif

}

// RTC_SetTime: Sets the time and date on the RTC
void SetRTCTimeInfo(u32 hour, u32 min, u32 sec) 
{

    // Set hours
	 HOUR = hour;
	  
    // Set minutes
	 MIN = min;
	
	// Set seconds
	 SEC = sec;

}


void GetRTCTime(s32 *hr,s32 *mi,s32 *se)
{
	*hr = HOUR;
	*mi = MIN;
	*se = SEC;
}
void DisplayRTCTime(u32 hour,u32 min,u32 sec)
{
//	CmdLCD(GOTO_LINE1_POS0);
	CharLCD((hour/10)+48);
	CharLCD((hour%10)+48);
	CharLCD(':');
	CharLCD((min/10)+48);
	CharLCD((min%10)+48);
	CharLCD(':');
	CharLCD((sec/10)+48);
	CharLCD((sec%10)+48);
}

void GetRTCDate(s32 *day,s32 *month,s32 *year)
{
	*day = DOM;
	*month = MONTH;
	*year = YEAR;
	
}
void DisplayRTCDate(u32 d,u32 m,u32 y)
{
//	CmdLCD(GOTO_LINE2_POS0);
	CharLCD((d/10)+48);
	CharLCD((d%10)+48);
	CharLCD(':');
	CharLCD((m/10)+48);
	CharLCD((m%10)+48);
	CharLCD(':');
	U32LCD(y);
}

void SetRTCDateInfo(u32 d,u32 m,u32 y)
{
	DOM = d;
	MONTH = m;
	YEAR = y;
}

void GetRTCDay(s32 *day)
{
	*day = DOW;
}

void DisplayRTCDay(u32 day)
{
//	CmdLCD(GOTO_LINE3_POS0);
	U32LCD(day);
}

/*void SetRTCDay(u32 day)
{
	DOW=day;
}*/

void SetRTCHour()
{
	s32 key;
//	CmdLCD(CLEAR_LCD);
//	StrLCD("HOUR:");
	while(my_ColScan()==0);
	key=my_ReadData();
		 

	if(key>=0 && key<=23)
	{
//		CmdLCD(GOTO_LINE2_POS0);
//		StrLCD("valid");
		HOUR = key;
	}
//	else
//	{
//	    CmdLCD(GOTO_LINE2_POS0);
//		StrLCD("Invalid");
//	}
	 delay_ms(1000);
}
void SetRTCMin(void)
{
	s32 key;
//	CmdLCD(CLEAR_LCD);
//	StrLCD("MIN:");
	while(my_ColScan()==0);
	key=my_ReadData();
		 

	if(key>=0 && key<=59)
	{
//		CmdLCD(GOTO_LINE2_POS0);
//		StrLCD("valid");
		MIN = key;
	}
//	else
//	{
//		CmdLCD(GOTO_LINE2_POS0);
//		StrLCD("Invalid");
//	}
	 delay_ms(1000);
}
void SetRTCSec(void)
{
	s32 key;
//	CmdLCD(CLEAR_LCD);
//	StrLCD("SEC:");
	while(my_ColScan()==0);
	key = my_ReadData();
		 

	if(key>=0 && key<=59)
	{
//		CmdLCD(GOTO_LINE2_POS0);
//		StrLCD("valid");
		SEC = key;
	}
//	else
//	{
//		CmdLCD(GOTO_LINE2_POS0);
//		StrLCD("Invalid");
//	}
	 delay_ms(1000);
}
void SetRTCDay(u32 day)
{
	s32 key;
//	CmdLCD(CLEAR_LCD);
//	StrLCD("Day:");
	while(my_ColScan()==0);
	key = my_ReadData();
		 
	
	if(key>=0 && key<=6)
	{
//		CmdLCD(GOTO_LINE2_POS0);
		S32LCD(key);
		DOW = key;
	}
//	else
//	{
//		CmdLCD(GOTO_LINE2_POS0);
//		StrLCD("Invalid");
//	}
	 delay_ms(1000);
}
void SetRTCDa(void)
{
	s32 key;
	CmdLCD(CLEAR_LCD);
	StrLCD("DATE:");
	while(my_ColScan()==0);
	key=my_ReadData();
		 

	if(key>=0 && key<=31)
	{
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("valid");
		DOM = key;
	}
	else
	{
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("Invalid");
	}
	 delay_ms(1000);
}
void SetRTCMonth(void)
{
	s32 key;
	CmdLCD(CLEAR_LCD);
	StrLCD("MONTH:");
	while(my_ColScan()==0);
	key = my_ReadData();
		 

	if(key>=0 && key<=11)
	{
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("valid");
		MONTH = key;
	}
	else
	{
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("Invalid");
	}
	 delay_ms(1000);
}
void SetRTCYear(void)
{
	s32 key;
	CmdLCD(CLEAR_LCD);
	StrLCD("YEAR:");
	while(my_ColScan()==0);
	key=my_ReadData();
		 
		YEAR = key;
	
	 delay_ms(1000);
}
