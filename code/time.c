#include "time.h"

void Timer0Init(void) //1毫秒@12.000MHz
{
	TH0 = 0xFF;
	TL0 = 0xFF;
	TMOD = 0x04;
	ET0 = 1;
	TR0 = 1;
	EA = 1;
}
void Timer1Init(void) //1毫秒@12.000MHz
{
	AUXR &= 0xBF; //定时器时钟12T模式
	TMOD &= 0x0F; //设置定时器模式
	TL1 = 0x78;	  //设置定时初值
	TH1 = 0xEC;	  //设置定时初值
	TF1 = 0;	  //清除TF1标志
	TR1 = 1;	  //定时器1开始计时
	ET1 = 1;
}
