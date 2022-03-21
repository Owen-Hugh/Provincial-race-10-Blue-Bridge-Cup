#ifndef _KEY_H
#define _KEY_H

#include "stc15f2k60s2.h"
sbit L1 = P4 ^ 4;
sbit L2 = P4 ^ 2;
sbit H3 = P3 ^ 2;
sbit H4 = P3 ^ 3;
unsigned char keyRead(void);

#endif