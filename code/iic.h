#ifndef _IIC_H
#define _IIC_H

#include "stc15f2k60s2.h"

void IIC_Start(void);
void IIC_Stop(void);
bit IIC_WaitAck(void);
void IIC_SendAck(bit ackbit);
void IIC_SendByte(unsigned char byt);
unsigned char IIC_RecByte(void);
void AD_Init(unsigned char add);
unsigned char AD_Get(void);
unsigned int Read_AIN3(void);
void writedac(unsigned char dat);
#endif
