#include "key.h"
#include "bsp_init.h"

unsigned char keyRead(void)
{
	unsigned char t;
	t = 16;
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
	return t;
}