#include<lpc21xx.h>
#include"types.h"
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define BAUD 9600
#define DIVISOR (PCLK/(16*BAUD))


void Init_UART0()
{
	PINSEL0 |= (1<<0) | (1<<2);
	U0LCR = (1<<7) | 3 ;
	U0DLL = DIVISOR;
	U0DLM = DIVISOR>>8;
	U0LCR &= ~(1<<7);
}
void U0_TxByte(u8 Byte)
{
	U0THR=Byte;
	while((U0LSR&(1<<6))==0);
}
u8 U0_RxByte(void)
{
	while(((U0LSR>>0)&1)==0);
	return U0RBR;
}
void U0_TxStr(s8* Str)
{
	while(*Str)
		U0_TxByte(*Str++);
}
void U0_TxU32(u32 num)
{
	s8 arr[10];
	s32 i=0;
	if(num==0)
	{
		U0_TxByte('0');
	}
	else
	{
		while(num>0)
		{
			arr[i]=(num%10)+48;
			i++;
			num/=10;
		}
		for(--i;i<=0;i--)
		{
			U0_TxByte(arr[i]);
		}
	}
}

void U0_TxS32(s32 num)
{
	if(num<0)
	{
		U0_TxByte('-');
		num=-num;
	}
	U0_TxU32(num);
}

s8* U0_RxStr()
{
	static s8 arr[100];
	s32 i=0;
	while(1)
	{
		arr[i]=U0_RxByte();
		U0_TxByte(arr[i]);
		if(arr[i]=='\n' || arr[i]=='\r')
		{
			arr[i]='\0';
			break;
		}
		i++;
	}
	return arr;
}

void U0_TxF32(f32 fnum,u32 Dp)
{
	u32 temp,i;
	if(fnum<0.0)
	{
		U0_TxByte('-');
		fnum=-fnum;
	}
	temp=fnum;
	U0_TxU32(temp);
	U0_TxByte('.');
	for(i=0;i<Dp;i++)
	{
		fnum=(fnum-temp)*10;
		temp=fnum;
		U0_TxU32(temp);
	}
}


























