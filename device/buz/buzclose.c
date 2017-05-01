/* buzclose.c - buzclose */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  buzclose  -  Close a buzzer device
 *------------------------------------------------------------------------
 */
devcall	buzclose(
	  struct dentry *devptr		/* Entry in device switch table */
	)
{

        kprintf("inside buzclsoe:\n");
        int oe_val=*(uint32 *)(GPIO1+GPIO_OE);
        int data_out=*(uint32 *)(GPIO1+GPIO_DATAOUT);
        kprintf("initial OE is : %x\n",oe_val);
        kprintf("initial DATAIN is : %x\n",*(uint32 *)(GPIO1+GPIO_DATAIN));
        kprintf("initial DATAOUT is : %x\n",data_out);

	kprintf("force swithcing off buz first if on");
        *(uint32 *)(GPIO1+GPIO_DATAOUT)=unsetbit(data_out,28);
	kprintf("new DATAOUT is : %x\n",*(uint32 *)(GPIO1+GPIO_DATAOUT));
        int new_oe_val=setbit(oe_val,PIN_VAL);
        *(uint32 *)(GPIO1+GPIO_OE)=new_oe_val;
        kprintf("new OE is : %x\n",*(uint32 *)(GPIO1+GPIO_OE));

	return devptr->dvnum;
}
