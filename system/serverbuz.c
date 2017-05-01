/*  serverbuz.c  - serverbuz */

#include <xinu.h>

process	serverbuz(uint32 xnum)
{
	kprintf("serverbuz: Starting serverbuz for BUZ device");
	uint32 slot;
	uint16 localport = 9501;
        slot = udp_register(0, 0, localport);
	// todo: cannot bind port - try 5 times record port number and send pkt saying listening at
        if (slot == SYSERR) {
                kprintf("serverbuz: Could not reserve UDP port %d\n",localport);
                return SYSERR;
        }
	// sending a packet which tells the local IP/port at which serverbuz is listening

        // Extracting local IP address in str in dotted decimal notation
        char str_own_ip[40];
	uint32 ipaddr = NetData.ipucast;
        sprintf(str_own_ip, "%d.%d.%d.%d", (ipaddr>>24)&0xff, (ipaddr>>16)&0xff, (ipaddr>>8)&0xff,ipaddr&0xff);
        // Extracting EDGE IP address in str in dotted decimal notation
        char str_edge_ip[40];
        uint32 ipaddr_edge = NetData.iprouter;
        sprintf(str_edge_ip, "%d.%d.%d.%d", (ipaddr_edge>>24)&0xff, (ipaddr_edge>>16)&0xff, (ipaddr_edge>>8)&0xff,ipaddr_edge&0xff);
	// Converting local port to string 
	char str_port[6];
	sprintf(str_port,"%d",localport);
	// Forming data
        char data[1000]="";
        strncat(data,"serverport:BUZ0:",strlen("serverport:BUZ0:"));
//        strncat(data,str_own_ip,strlen(str_own_ip));
//        strncat(data,":",1);
	strncat(data,str_port,strlen(str_port));
        strncat(data,";",1);
        kprintf("main: sending data \"%s\" to edge at \"%s\":9801\n",data,str_edge_ip);
	sendpkt(str_edge_ip,9801,data,strlen(data));
	
	while(1)
	{
		char buff[1000];
		uint32 remip;
		uint16 remport;
		int32 retval;
		retval = udp_recvaddr(slot, &remip, &remport, buff,sizeof(buff),600000);
		if (retval == TIMEOUT) 
		{
			continue;
		} 
		else if (retval == SYSERR) 
		{
			kprintf("error receiving UDP\n");
			return SYSERR;
		}
		// should receive setval:BUZ0:off;
		uint32 i=0;
		while(buff[i]!=';')
			i++;
		buff[i]='\0';
		char *matchstr1="setval:BUZ0:on";
		char *matchstr2="setval:BUZ0:off";
		kprintf("serverbuz: received %s on serverbuz at port %d\n",buff,localport);
		if(strcmp(buff,matchstr1)==0)
		{
			kprintf("Known command on\n");
			write(xnum,"on",2); //todo: check if write occurred
		}
		else if(strcmp(buff,matchstr2)==0)
		{
			kprintf("Known command off\n");
			write(xnum,"off",3); //todo: check if write occurred
		}
		else
		{
			kprintf("Unknown command ; see log\n");
			uint32 i=0;
			while(buff[i]!='\0' && i<1000)
			{
				kprintf("%d is %c\n",i,buff[i]);
				i++;
			}
			kprintf("log ends\n");
		}
	}
	return OK;
}
