/* fsrclose.c - fsrclose */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  fsrclose  -  Close a Force Sensitive Resistor (Pressure sensor) device
 *------------------------------------------------------------------------
 */
devcall	fsrclose(
	  struct dentry *devptr		/* Entry in device switch table */
	)
{

	return devptr->dvnum;
}
