#include <lpc21xx.h>
#include "delay.h"
#include "kpm.h"
#include "kpm_defines.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "types.h"
#include "uart_defines.h"
#include "interrupts.h"
unsigned int PASS = 2468;
int hours,minutes,seconds;
u32 h, m, s,year,month,date,day;
unsigned int digit = 0;
int key = 0,i,temp=0;
volatile int flag = 0;
void displayRTC()
{
				if(h<10)
				CharLCD('0');
			  U32LCD(h);
				CharLCD(':');
				if(m<10)
				CharLCD('0');
				U32LCD(m);
				CharLCD(':');
				if(s<10)
				CharLCD('0');
				U32LCD(s);
}




void SetRTCTime(u32 H, u32 M, u32 S)
{
    HOUR = H;
    MIN  = M;
    SEC  = S;
}



void getRTC(u32 *h, u32 *m, u32 *s)
{
    *h = HOUR;
    *m = MIN;
    *s = SEC;
}



void SetDate(u32 date,u32 month,u32 year)
{
	
	DOM = date;
	MONTH = month;
	YEAR = year;
}



void RTC_Init(void) 
{
  
	CCR = RTC_RESET;
  
#ifdef _LPC2148
 
	CCR = RTC_ENABLE | RTC_CLKSRC;  
#else
 
	PREINT = PREINT_VAL;
	PREFRAC= PREFRAC_VAL;
  
  
	CCR = RTC_ENABLE;  
	
#endif
}



void getDate(u32 *day,u32 *date,u32 *month,u32 *year)
{
	*date = DOM;
	*month = MONTH;
	*year = YEAR;
	*day = DOW;
}


char week[][10] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};



void SetRTCDay(u32 day)
{
	DOW = day;
}



void  SetTime(s32 h,s32 m,s32 s)
{
	hours = h;
	minutes = m;
	seconds = s;
}



int gethr(u32 *h)
{
	*h = HOUR;
	return *h;
}



int getmin(u32 *m)
{
	*m = MIN;
	return *m;
}



void check()
{

			  if(digit != PASS)
				{
					delay_ms(100);
					CmdLCD(CLEAR_LCD);
					CmdLCD(GOTO_LINE1_POS0);
					S32LCD(digit);
					CmdLCD(GOTO_LINE2_POS0);
					StrLCD("WRONG PASSWORD!");
					delay_s(2);
					digit = 0;
				}
				else if(gethr(&h)!=hours || getmin(&m)!=minutes)
				{
					CmdLCD(CLEAR_LCD);
					CmdLCD(GOTO_LINE1_POS0);
					StrLCD("OUT OF TIME");
					delay_s(2);
					digit = 0;
				}
				else if(digit == PASS && gethr(&h)==hours && getmin(&m)==minutes)
				{
					delay_ms(100);
					CmdLCD(CLEAR_LCD);
					CmdLCD(GOTO_LINE1_POS0);
					StrLCD("SECURITY");
					CmdLCD(GOTO_LINE2_POS0);
					StrLCD("ACCESS GRANTED");
					delay_s(2);
					digit = 0;
				}
}
void RTC_HOUR()
{
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("ENTER HOUR(0-24)");
	CmdLCD(GOTO_LINE2_POS0);
	for(i=0;i<2;i++)
	{
		key = my_KeyScan();
		while(my_ColScan()==0);
		key = key - '0';
		S32LCD(key);
		temp = temp*10 + key;
	}
	HOUR = temp;
	temp = 0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("HOURS UPDATED");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("SUCCESSFULLY!");
	delay_s(1);
}
void RTC_MIN()
{
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("ENTER MIN(0-59)");
	CmdLCD(GOTO_LINE2_POS0);
	for(i=0;i<2;i++)
	{
		key = my_KeyScan();
		while(my_ColScan()==0);
		key = key - '0';
		S32LCD(key);
		temp = temp*10 + key;
	}
	MIN = temp;
	temp = 0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("MINUTES UPDATED");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("SUCCESSFULLY!");
	delay_s(1);
}

void RTC_SEC()
{
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("ENTER SEC(0-59)");
	CmdLCD(GOTO_LINE2_POS0);
	for(i=0;i<2;i++)
	{
		key = my_KeyScan();
		while(my_ColScan()==0);
		key = key - '0';
		S32LCD(key);
		temp = temp*10 + key;
	}
	SEC = temp;
	temp = 0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("SECONDS UPDATED");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("SUCCESSFULLY!");
	delay_s(1);
}
void RTC_YEAR()
{
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("ENTER YEAR");
	CmdLCD(GOTO_LINE2_POS0);
	for(i=0;i<4;i++)
	{
		key = my_KeyScan();
		while(my_ColScan()==0);
		key = key - '0';
		S32LCD(key);
		temp = temp*10 + key;
	}
	YEAR = temp;
	temp = 0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("YEAR UPDATED");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("SUCCESSFULLY!");
	delay_s(1);
}

void RTC_MONTH()
{
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("ENTER MONTH 0-12");
	CmdLCD(GOTO_LINE2_POS0);
	for(i=0;i<2;i++)
	{
		key = my_KeyScan();
		while(my_ColScan()==0);
		key = key - '0';
		S32LCD(key);
		temp = temp*10 + key;
	}
	MONTH = temp;
	temp = 0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("MONTH UPDATED");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("SUCCESSFULLY!");
	delay_s(1);
}
void RTC_DATE()
{
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("ENTER DATE 0-31");
	CmdLCD(GOTO_LINE2_POS0);
	for(i=0;i<2;i++)
	{
		key = my_KeyScan();
		while(my_ColScan()==0);
		key = key - '0';
		S32LCD(key);
		temp = temp*10 + key;
	}
	DOM = temp;
	temp = 0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("DATE UPDATED");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("SUCCESSFULLY!");
	delay_s(1);
}
void RTC_DAY()
{
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("ENTER DAY(0-6)");
	CmdLCD(GOTO_LINE2_POS0);
	key = my_KeyScan();
	while(my_ColScan()==0);
	key = key - '0';
	S32LCD(key);
	DOW = key;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("DAY UPDATED");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("SUCCESSFULLY!");
	delay_s(1);
}

void EXIT()
{
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("EXITING...");
	delay_s(1);
}


void EDIT_RTC()
{
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1:H 2:M 3:S 4:D");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("5:DT 6:M 7:Y 8:E");
	
	key = my_KeyScan();
	while(my_ColScan()==0);
	key = key - '0';
	
	
	switch(key)
	{
		case 1: RTC_HOUR();
						EXIT();
						break;
		case 2: RTC_MIN();
						EXIT();				
						break;
		case 3: RTC_SEC();
						EXIT();
						break;
		case 4: RTC_DAY();
						EXIT();
						break;
		case 5: RTC_DATE();
						EXIT();
						break;
		case 6: RTC_MONTH();
						EXIT();
						break;
		case 7: RTC_YEAR();
						EXIT();
						break;
		case 8: EXIT();
						break;
	}
}

void EDIT_HOUR()
{
	hours = 0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("ENTER HOUR(0-24)");
	CmdLCD(GOTO_LINE2_POS0);
	for(i=0;i<2;i++)
	{
		key = my_KeyScan();
		while(my_ColScan()==0);
		key = key - '0';
		S32LCD(key);
		hours = hours*10 + key;
	}
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("HOURS UPDATED");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("SUCCESSFULLY!");
	delay_s(1);
}


void EDIT_MINUTES()
{
	minutes = 0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("ENTER MIN(0-59)");
	CmdLCD(GOTO_LINE2_POS0);
	for(i=0;i<2;i++)
	{
		key = my_KeyScan();
		while(my_ColScan()==0);
		key = key - '0';
		S32LCD(key);
		minutes = minutes*10 + key;
	}
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("MINTES UPDATED");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("SUCCESSFULLY!");
	delay_s(1);
}

void EDIT_SECONDS()
{
	seconds = 0;
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("ENTER SEC(0-59)");
	CmdLCD(GOTO_LINE2_POS0);
	for(i=0;i<2;i++)
	{
		key = my_KeyScan();
		while(my_ColScan()==0);
		key = key - '0';
		S32LCD(key);
		seconds = seconds*10 + key;
	}
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("SECONDS UPDATED");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("SUCCESSFULLY!");
	delay_s(1);
}



void EDIT_SCHEDULE()
{
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1:HOUR 2:MINUTE");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("3:SECOND 4:EXIT");
	
	key = my_KeyScan();
	while(my_ColScan()==0);
	key = key - '0';
	switch(key)
	{
		case 1: EDIT_HOUR();
						EXIT();
						break;
		case 2: EDIT_MINUTES();
						EXIT();
						break;
		case 3: EDIT_SECONDS();
						EXIT();
						break;
		case 4: EXIT();
						break;
	}
}

int main()
{		IODIR0 &= ~(1<<25);
		IODIR0 |= 1<<24;
	  IODIR0 &= ~(1<<3);
		RTC_Init();
    InitLCD();
		my_InitKPM();
		Init_Interrupt();
    SetRTCTime(18, 50, 00);
		SetRTCDay(0);
		SetTime(18,51,00);
		SetDate(28,06,2026);
while(1)
{
				CmdLCD(CLEAR_LCD);
				StrLCD("TIME:");
        getRTC(&h, &m, &s);
				displayRTC();
				getDate(&day,&date,&month,&year);
				CmdLCD(GOTO_LINE2_POS0);
				U32LCD(date);
				CharLCD('/');
				U32LCD(month);
				CharLCD('/');
				U32LCD(year);
				CharLCD(' ');
				StrLCD(week[day]);
				delay_s(1);


	if(((IOPIN0>>25)&1)==0)
	{
		//delay_us(20);
		while(((IOPIN0>>25)&1)==0)
		CmdLCD(CLEAR_LCD);
		CmdLCD(GOTO_LINE1_POS0);
		StrLCD("ENTER PASSWORD");
		CmdLCD(GOTO_LINE2_POS0);
		while(1)
		{
			key = my_KeyScan();
			while(my_ColScan()==0);
			if(key == '-')
				{
					CmdLCD(SHIFT_CUR_LEFT);
					CharLCD(' ');
					CmdLCD(SHIFT_CUR_LEFT);
					digit/=10;
				}
				else if(key >='0' && key<='9')
				{
						key = key - '0';
						digit = digit*10 + key;
						CharLCD('*');
						//S32LCD(key);
				}
			else if(key == '=')
			{
				CmdLCD(CLEAR_LCD);
				CmdLCD(GOTO_LINE1_POS0);
				U32LCD(digit);
				check();
				break;				
			}
		}
   }
	
	 if(flag)
	 {
		 delay_s(1);
		 flag = 0;
		 CmdLCD(CLEAR_LCD);
		 CmdLCD(GOTO_LINE1_POS0);
		 StrLCD("1.EDIT RTC 3.EXIT");
		 CmdLCD(GOTO_LINE2_POS0);
		 StrLCD("2.EDIT SCHEDULE");
		 key = my_KeyScan();
		 while(my_ColScan()==0);
		 key = key - '0';
		 switch(key)
		 {
			 case 1: EDIT_RTC();
								break;
			 case 2: EDIT_SCHEDULE();
			 
			 case 3: break; 
		 }
	 }
}
}

