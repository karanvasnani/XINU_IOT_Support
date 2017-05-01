/* ctshandler.c - ctshandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  ctshandler  -  Handle an interrupt for a cts device
 *------------------------------------------------------------------------
 */
void ctshandler(uint32 xnum) {

	static int num=0;

	int data_in=*(uint32 *)(GPIO1+GPIO_DATAIN);
	data_in=data_in & 0x10000000;
	if(data_in>0)
	{	
		num++;
		if(num==10)
		{
			uint32 irq_status_clr = 0x10000000;
			*(uint32 *)(GPIO1+GPIO_IRQSTATUS_CLR_0)=irq_status_clr;
			signal(cts_sem);
		}
	}
	else
	{
		num=0;
	}
	
}
