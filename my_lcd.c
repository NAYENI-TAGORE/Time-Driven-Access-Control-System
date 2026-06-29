#include<lpc21xx.h>
#include"delay.h"
#include"types.h"
#include"lcd_defines.h"

void Write_LCD(u8 Data)
{
	IOPIN0 = ((IOPIN0&~(0xFF<<8)) | ( Data<<8));
	IOCLR0 |= 1<<17;
	
	IOSET0 |= 1<<18;
	delay_us(1);
	IOCLR0 |= 1<<18;
	delay_ms(2);
}

void CmdLCD(u8 Cmd)
{
	
	IOCLR0 |= 1<<16;
	Write_LCD(Cmd);
}

void InitLCD()
{
	IODIR0 |= (0xFF<<8) | (1<<16) | (1<<17) | (1<<18);
	delay_ms(15);
	CmdLCD(0x30);
	delay_ms(2);
	CmdLCD(0x30);
	delay_us(100);
	CmdLCD(0x30);
	delay_us(100);
	CmdLCD(0x38);
	CmdLCD(0x0C);
	CmdLCD(0x01);
}

void CharLCD(u8 ascii)
{
	IOSET0 |= 1<<16;
	Write_LCD(ascii);
}

void StrLCD(s8 *Str)
{
	while(*Str)
	CharLCD(*Str++);
}

void U32LCD(u32 num)
{
	s8 a[8];
	s32 i=0;
	
	if(num==0)
	{
		CharLCD('0');
	}
	else
	{
		while(num>0)
		{
			a[i]=(num%10)+48;
			i++;
			num/=10;
		}
		for(--i;i>=0;i--)
		{
			CharLCD(a[i]);
		}
	}
}

void S32LCD(s32 num)
{

	if(num<0)
	{
		CharLCD('-');
		num=-num;
	}
	U32LCD(num);
}

void HEXLCD(u32 num)
{
	s8 a[8];
	s32 i=0;
	if(num==0)
	{
		CharLCD('0');
	}
	else
	{
		while(num)
		{
			if((num%16)<10)
			{
				a[i]=(num%16) + 48;
				i++;
			}
			else
			{
				a[i]=(num%16) -10 + 'A';
				i++;
			}
			num/=16;
		}
		for(--i;i>=0;i--)
		CharLCD(a[i]);
	}
}

void OctLCD(u32 num)
{
	s8 a[11];
	s32 i=0;
	
	if(num==0)
	{
		CharLCD('0');
	}
	else
	{
		while(num)
		{
			a[i]=num%8 + 48;
		i++;
			num/=8;
		}
			for(--i;i>=0;i--)
			CharLCD(a[i]);
	}
}

void BinLCD(u32 num,u32 nBD)
{
	s32 i;
	for(i=nBD-1;i>=0;i--)
	CharLCD(((num>>i)&1)+48);
}

void F32LCD(f32 fnum,u32 Dp)
{
	int temp,i;
	if(fnum<0.0)
	{
		CharLCD('-');
		fnum=-fnum;
	}
	temp=fnum;
	U32LCD(temp);
	CharLCD('.');
	for(i=0;i<Dp;i++)
	{
		fnum=(fnum-temp)*10;
		temp=fnum;
		U32LCD(temp);
	}
}
