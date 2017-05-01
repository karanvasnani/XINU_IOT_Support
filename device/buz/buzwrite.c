/* buzwrite.c - buzwrite */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  buzwrite  -  Switch buzzer on/off
 *------------------------------------------------------------------------
 */
devcall	buzwrite(
	  struct dentry	*devptr,	/* Entry in device switch table	*/
	  char	*buff,			/* Buffer of characters		*/
	  int32	count 			/* Count of character to write	*/
	)
{
	kprintf("inside buzwrite:\n");
        int oe_val=*(uint32 *)(GPIO1+GPIO_OE);
        int data_out=*(uint32 *)(GPIO1+GPIO_DATAOUT);
        kprintf("initial OE is : %x\n",oe_val);
        kprintf("initial DATAIN is : %x\n",*(uint32 *)(GPIO1+GPIO_DATAIN));
        kprintf("initial DATAOUT is : %x\n",data_out);

	if((buff[0]=='o' && buff[1]=='n')||((buff[0]=='O' && buff[1]=='N')))
	{
        	int new_data_out=setbit(data_out,PIN_VAL);
       		*(uint32 *)(GPIO1+GPIO_DATAOUT)=new_data_out;
	}
	else if((buff[0]=='o' && buff[1]=='f' && buff[2]=='f')||(buff[0]=='O' && buff[1]=='F' && buff[2]=='F'))
	{
		int new_data_out=unsetbit(data_out,PIN_VAL);
                *(uint32 *)(GPIO1+GPIO_DATAOUT)=new_data_out;
	}
	else
	{
		kprintf("Undefined write operation for buzzer.");
		return SYSERR;	
	}

        kprintf("new DATAOUT is : %x\n",*(uint32 *)(GPIO1+GPIO_DATAOUT));
	return OK;
}
