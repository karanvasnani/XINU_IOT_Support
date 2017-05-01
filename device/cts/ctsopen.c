/* ctsopen.c - ctsopen */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  ctsopen  -  Open an Capacitive Touch Sensor device
 *------------------------------------------------------------------------
 */
devcall	ctsopen(
	  struct dentry *devptr,	/* Entry in device switch table */
	  char	*name,			/* Name to open			*/
	  char	*mode			/* Mode argument		*/
	)
{

        kprintf("inside ctsopen:\n");
        int oe_val=*(uint32 *)(GPIO1+GPIO_OE);
        int data_in=*(uint32 *)(GPIO1+GPIO_DATAIN);
        kprintf("initial OE is : %x\n",oe_val);
        kprintf("initial DATAOUT is : %x\n",*(uint32 *)(GPIO1+GPIO_DATAOUT));
        kprintf("initial DATAIN is : %x\n",data_in);

	// set output enable to 1 to configure device for reading(data_in/input)
        int new_oe_val=setbit(oe_val,PIN_VAL);
        *(uint32 *)(GPIO1+GPIO_OE)=new_oe_val;
        kprintf("new OE is : %x\n",*(uint32 *)(GPIO1+GPIO_OE));

	return devptr->dvnum;
}
