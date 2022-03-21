#include "bsp_init.h"
#include "intrins.h"
#include "time.h"
#include "iic.h"
#include "key.h"
#include "stdio.h"

unsigned int AD_val, dac;
unsigned int ne555, NE555_Sec;
unsigned char t;
bit Mode;		// 0: Vrb 1: Fout
bit Mode_2;		// 0: 2V 1:AD
bit Mode_3 = 1; // LED 0:off 1: on
bit Mode_4 = 1; // SMG 0: off 1: on
void Mode_SMG();
unsigned char str[10];
/*按键输入检测

*/
void keyR(void)
{
	L1 = L2 = H3 = 1;
	H4 = 0;
	if (L2 == 0)
	{
		delay(100);
		if (L2 == 0)
			t = 8;
		while (!L2)
			;
	}
	if (L1 == 0)
	{
		delay(100);
		if (L1 == 0)
			t = 4;
		while (!L1)
			;
	}
	L1 = L2 = H4 = 1;
	H3 = 0;
	if (L2 == 0)
	{
		delay(100);
		if (L2 == 0)
			t = 9;
		while (!L2)
			;
	}
	if (L1 == 0)
	{
		delay(100);
		if (L1 == 0)
			t = 5;
		while (!L1)
			;
	}
}
/*
	界面切换函数
*/
void Mode_Key(void)
{
	if (t == 4)
		Mode ^= 1;
	if (t == 5)
		Mode_2 ^= 1;
	if (t == 8)
		Mode_3 ^= 1;
	if (t == 9)
		Mode_4 ^= 1;
	t = 16;
}
/*
	数码管显示界面
*/
void smg_disp()
{
	bsp_smg(6, AD_val / 1000);
	bsp_smg(7, AD_val % 1000 / 100);
	bsp_smg(8, AD_val % 100 / 10);
	bsp_smg(6, 10);
	bsp_smg(1, 11);
}

void smg_disp_555()
{
	bsp_smg(1, 12);
	if (NE555_Sec / 10000)
	{
		bsp_smg(4, NE555_Sec / 10000);
		bsp_smg(5, NE555_Sec % 10000 / 1000);
		bsp_smg(6, NE555_Sec % 1000 / 100);
		bsp_smg(7, NE555_Sec % 100 / 10);
		bsp_smg(8, NE555_Sec % 10);
	}
	else if (NE555_Sec / 1000)
	{
		bsp_smg(5, NE555_Sec % 10000 / 1000);
		bsp_smg(6, NE555_Sec % 1000 / 100);
		bsp_smg(7, NE555_Sec % 100 / 10);
		bsp_smg(8, NE555_Sec % 10);
	}
	else if (NE555_Sec / 100)
	{
		bsp_smg(6, NE555_Sec % 1000 / 100);
		bsp_smg(7, NE555_Sec % 100 / 10);
		bsp_smg(8, NE555_Sec % 10);
	}
	else if (NE555_Sec / 10)
	{
		bsp_smg(7, NE555_Sec % 100 / 10);
		bsp_smg(8, NE555_Sec % 10);
	}
	else
		bsp_smg(8, NE555_Sec % 10);
}
/*
	LED
*/
void LED_disp()
{
	//L1 L2
	if (Mode == 0)
	{
		LED_1();
		LED_2_OFF();
	}
	else
	{
		LED_2();
		LED_1_OFF();
	}
	//L3
	if (AD_val < 1500 || (AD_val >= 2500 && AD_val < 3500))
	{
		LED_3_OFF();
	}
	else
	{
		LED_3();
	}
	//L4
	if (NE555_Sec < 1000 || (NE555_Sec < 10000 && NE555_Sec >= 5000))
	{
		LED_4_OFF();
	}
	else
	{
		LED_4();
	}
	//L5
	if (Mode_2 == 0)
	{
		LED_5_OFF();
	}
	else if (Mode_2 == 1)
	{
		LED_5();
	}
}

/*
	界面切换
*/
void Mode_SMG()
{
	Mode_Key();
	//按键功能1
	if (Mode == 0 && Mode_4 == 1)
		smg_disp();
	else if (Mode == 1 && Mode_4 == 1)
		smg_disp_555();
	//按键功能2
	if (Mode_2 == 0)
	{
		delay(50);
		writedac(0x66);
	}
	else if (Mode_2 == 1)
	{
		dac = AD_Get();
		delay(50);
		writedac(dac);
	}
	//按键功能3
	if (Mode_3 == 0)
	{
		bsp_init();
	}
	else if (Mode_3 == 1)
	{
		LED_disp();
	}
}

// 主程序
int main()
{
	bsp_init();
	Timer0Init();
	Timer1Init();
	AD_Init(0x03);
	//UartInit();
	while (1)
	{
		keyR();
		AD_Init(0x03);
		AD_val = Read_AIN3();
	}
}

void Timer0() interrupt 1
{
	ne555++;
}
void Timer1() interrupt 3
{
	static unsigned char sec;
	sec++;
	Mode_SMG();
	if (sec == 200)
	{
		sec = 0;
		NE555_Sec = ne555;
		ne555 = 0;
		//sprintf(str,"F = %dHZ",NE555_Sec);
	}
}