/* fsrread.c - fsrread */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  fsrread  -  Read from a fsr device
 *------------------------------------------------------------------------
 */
devcall	fsrread(
	  struct dentry	*devptr,	/* Entry in device switch table	*/
	  char	*buff,			/* Buffer of characters		*/
	  int32	count 			/* Count of character to read	*/
	)
{

	uint32 value_of_sensor = *(uint32 *)(ADC_TSC+FIFO0DATA);
        kprintf("value of sensor is %d\n",value_of_sensor);
	return value_of_sensor;
}
