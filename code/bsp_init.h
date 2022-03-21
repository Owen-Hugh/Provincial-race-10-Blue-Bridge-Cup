#ifndef _BSP_INIT_H
#define _BSP_INIT_H

#include "stc15f2k60s2.h"
void delay(unsigned int i);
void bsp_init(void);
void bsp_smg(unsigned char n, unsigned char m);
void LED_1();
void LED_2();
void LED_3();
void LED_4();
void LED_5();
void LED_1_OFF();
void LED_2_OFF();
void LED_3_OFF();
void LED_4_OFF();
void LED_5_OFF();
#endif /*_BSP_INIT_H*/