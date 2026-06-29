#include<LPC21xx.h>
#include"types.h"
#include"lcd.h"
#include"lcd_defines.h"
#include"delay.h"

#define ROW0 16
#define ROW1 17
#define ROW2 18
#define ROW3 19

#define COL0 20
#define COL1 21
#define COL2 22
#define COL3 23

u8 kpmLUT[4][4]={{'7','8','9','%'},
                  {'4','5','6','x'},
                  {'1','2','3','-'},
                  {'*','0','=','+'}};

									
void my_InitKPM()
{
	IODIR1 |= 15<<ROW0; 
	IODIR1 &= ~(15<<COL0);
}

u32 my_ColScan()
{
	return (((IOPIN1>>COL0)&15)<15)?0:1;
}

u32 my_RowCheck()
{
	int r;
	for(r=0;r<4;r++)
	{
		IOPIN1 = ((IOPIN1&~(15<<ROW0)) | ((~(1<<r))<<ROW0));
		if(my_ColScan()==0)
		{
			break;
		}
	}
	IOCLR1 |= 15<<ROW0;
	return r;
}

u32 my_ColCheck()
{
		u32 c;
	
	for(c=0;c<4;c++)
	{
		if(((IOPIN1>>(COL0+c))&1)==0)
		break;
	}
	return c;
}

u32 my_KeyScan()
{
	u32  r,c,KeyV;
	while(my_ColScan());
	r=my_RowCheck();
	c=my_ColCheck();
	KeyV=kpmLUT[r][c];
	return KeyV;
}


u32 my_ReadData()
{
	u32 key,sum=0;
	s32 pos=0;
	while(1)
	{
	key=my_KeyScan();
	
	if(key==' ')
	{
		pos--;
		if(pos>=0)
		{
			CmdLCD(GOTO_LINE2_POS0+pos);
			CharLCD(' ');
			CmdLCD(GOTO_LINE2_POS0+pos);
			sum/=10;
		}
			else
			{
				pos=0;
			}
			while(my_ColScan()==0);
		}
	else if(key>=48 && key<=57)
	{
		CharLCD(key);
		sum=sum*10+(key-48);
		while(my_ColScan()==0);
		pos++;
	}
	else
	{
		break;
	}
	}
	return sum;	
}

u32 my_ReadNum()
{
	u32 key,sum;
	s32 pos;

while(1)
{
	key=my_KeyScan();
	
	if(key==' ')
	{
		pos--;
		if(pos>=0)
		{
			CmdLCD(GOTO_LINE2_POS0+pos);
			CharLCD(' ');
			CmdLCD(GOTO_LINE2_POS0+pos);
			while(my_ColScan()==0);
			sum/=10;
		}
		else
		{
			pos=0;
		}
	}
		else if(key>=48 && key<=57)
		{
			CmdLCD(GOTO_LINE2_POS0+pos);
			CharLCD(key);
			CmdLCD(GOTO_LINE2_POS0+pos);
			
			delay_ms(100);
			
			CmdLCD(GOTO_LINE2_POS0+pos);
			CharLCD('*');
			CmdLCD(GOTO_LINE2_POS0+pos);
			
			sum=sum*10+(key-48);
			while(my_ColScan()==0);
			pos++;
		}
		else
		{
			break;
		}
	}
return sum;
}	











