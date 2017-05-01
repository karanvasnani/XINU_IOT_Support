/* ctsinit.c - ctsinit */

#include <xinu.h>

/*------------------------------------------------------------------------
 * ctsinit  -  CAp touch sensor initialization function
 *------------------------------------------------------------------------
 */
int32	ctsinit (
		 struct	dentry *devptr
		)
{

	kprintf("Init called for CTS\n");
	set_evec( devptr->dvirq, (uint32)devptr->dvintr );

	return OK;
}
