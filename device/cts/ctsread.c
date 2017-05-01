/* ctsread.c - ctsread */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  ctsread  -  Read from a cts device
 *------------------------------------------------------------------------
 */
devcall	ctsread(
	  struct dentry	*devptr,	/* Entry in device switch table	*/
	  char	*buff,			/* Buffer of characters		*/
	  int32	count 			/* Count of character to read	*/
	)
{
        kprintf("\nClearing all interrupts on line 0\n");
        int irq_status_clr_val=0xFFFFFFFF;
        *(uint32 *)(GPIO1+GPIO_IRQSTATUS_CLR_0)=irq_status_clr_val;
        kprintf("\nNEW GPIO_IRQSTATUS_0         is %x\n",*(uint32 *)(GPIO1+GPIO_IRQSTATUS_0    ));

        kprintf("Clearing all interrupts on line 1\n");
        int irq_status_clr_1_val = 0xFFFFFFFF;
        *(uint32 *)(GPIO1+GPIO_IRQSTATUS_CLR_1)=irq_status_clr_1_val;
        kprintf("\nNEW GPIO_IRQSTATUS_1         is %x\n",*(uint32 *)(GPIO1+GPIO_IRQSTATUS_1    ));
        // CLEAR DONE


        // SEtting interrupt on for only 28th bit
        kprintf("Setting irq for 28th bit\n");
        int irq_status = 0x10000000;
        *(uint32 *)(GPIO1+GPIO_IRQSTATUS_SET_0)=irq_status;
//      kprintf("\nnew GPIO_IRQSTATUS_0 FINAL   is %x\n",*(uint32 *)(GPIO1+GPIO_IRQSTATUS_0));


//	Setting rising detect for 28th bit only
//      kprintf("Setting irq rising detect for 28th bit \n");
        int irq_rising = 0x10000000;
        *(uint32 *)(GPIO1+GPIO_RISINGDETECT) = irq_rising;
//      kprintf("\nGPIO_RISINGDETECT FINAL   is %x\n",*(uint32 *)(GPIO1+GPIO_RISINGDETECT));

	wait(cts_sem);
        kprintf("Button touched\n");
	return OK;
}
