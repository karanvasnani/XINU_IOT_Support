/* buzopen.c - buzopen */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  buzopen  -  Open a Buzzer device
 *------------------------------------------------------------------------
 */
devcall	buzopen(
	  struct dentry *devptr,	/* Entry in device switch table */
	  char	*name,			/* Name to open			*/
	  char	*mode			/* Mode argument		*/
	)
{

        kprintf("inside buzopen:\n");
        int oe_val=*(uint32 *)(GPIO1+GPIO_OE);
        int data_out=*(uint32 *)(GPIO1+GPIO_DATAOUT);
        kprintf("initial OE is : %x\n",oe_val);
        kprintf("initial DATAIN is : %x\n",*(uint32 *)(GPIO1+GPIO_DATAIN));
        kprintf("initial DATAOUT is : %x\n",data_out);

        int new_oe_val=unsetbit(oe_val,PIN_VAL);
        *(uint32 *)(GPIO1+GPIO_OE)=new_oe_val;
        kprintf("new OE is : %x\n",*(uint32 *)(GPIO1+GPIO_OE));

	return devptr->dvnum;
}
