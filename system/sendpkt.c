/* Send and receive UDP Packet */
#include <xinu.h>
syscall sendpkt(char *destipstr, uint16 destport,char *buff, uint32 bufflen)
{
        uint32 destip;
        uint32 retval;
	kprintf("sendpkt: Called sendpkt\n");
	// convert ipstring to dest ip 
	dot2ip(destipstr, &destip);
	uint16 locport = getport();
	kprintf("sendpkt: Using local port %d\n",locport);
        uint32 slot = udp_register(destip, destport, locport);
	// todo: check if slot free - if not getport again to a max of 5 tries if fails return SYSERR
        int32 msglen;
        kprintf("sendpkt: Reserved slot %d, sending packet to destination %d:%d buff is %s, bufflen is %d\n", slot, destip, destport,buff,bufflen);
	retval = udp_send(slot, buff, bufflen);
	kprintf("out of udp_send\n");
        if (retval == SYSERR) {
		kprintf("sendpkt: %d error sending UDP \n",destip);
                return SYSERR;
        }
        udp_release(slot);
        return OK;
}

