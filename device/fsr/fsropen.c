/* fsropen.c - fsropen */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  fsropen  -  Open a Force Sensitive Resistor (Pressure Sensor) device
 *------------------------------------------------------------------------
 */
devcall	fsropen(
	  struct dentry *devptr,	/* Entry in device switch table */
	  char	*name,			/* Name to open			*/
	  char	*mode			/* Mode argument		*/
	)
{

        kprintf("inside fsropen:\n");

        uint32 step_enable_orig = *(uint32 *)(ADC_TSC+STEPENABLE);
        kprintf("original step enable is %x\n",step_enable_orig);

        uint32 step_enable_new = setbit(step_enable_orig,2-1);
        *(uint32 *)(ADC_TSC+STEPENABLE) = step_enable_new;
        kprintf("new step enable is %x\n",*(uint32 *)(ADC_TSC+STEPENABLE));

        kprintf("FSR OPENED:\n");
	return devptr->dvnum;
}
