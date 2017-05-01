/* Receive UDP Packet */

#include<xinu.h>

syscall recvpkt(uint32 slot,char *buff, uint32 len)
{
	kprintf("recvpkt: Inside recvpkt\n");
	int32 retval;
	uint16 remport;
	uint32 remip;
	kprintf("recvpkt: Listening for packet on slot %d\n",slot);
	while (TRUE) 
	{
                retval = udp_recvaddr(slot, &remip, &remport, buff,len, 600000);
                if (retval == TIMEOUT) {
                        continue;
                } else if (retval == SYSERR) {
                        kprintf("recvpkt: Error receiving UDP\n");
                        return 1;
                }
		printf("recvpkt: Packet received from %d:%d, message is: %s\n", remip, remport, buff);
	}
	return OK;
}
