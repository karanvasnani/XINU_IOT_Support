/*  serverfsr.c  - serverfsr */

#include <xinu.h>

process	serverfsr(uint32 xnum)
{
	kprintf("serverfsr: Starting serverfsr for FSR device");
	uint32 slot;
	uint16 localport = 9501;
        slot = udp_register(0, 0, localport);
	// todo: cannot bind port - try 5 times record port number and send pkt saying listening at
        if (slot == SYSERR) {
                kprintf("serverfsr: Could not reserve UDP port %d\n",localport);
                return SYSERR;
        }
	// sending a packet which tells the local IP/port at which serverfsr is listening

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
        strncat(data,"serverport:FSR0:",strlen("serverport:FSR0:"));
	strncat(data,str_port,strlen(str_port));
        strncat(data,";",1);
        strncat(data,"\0",1);
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
		uint32 i=0;
		while(buff[i]!=';')
			i++;
		buff[i]='\0';
		char *matchstr="getval:FSR0";
		kprintf("serverfsr: received %s on serverfsr at port %d\n",buff,localport);
		if(strcmp(buff,matchstr)==0)
		{
			kprintf("Known command\n");
			uint32 cur_val=read(xnum,NULL,NULL);
                	kprintf("read value %d\n",cur_val);
                        // Convert val to str
                        char str_val[40];
                        sprintf(str_val,"%d",cur_val);
                        char data[1000]="";
                        strncat(data,"reading:FSR0:",strlen("reading:FSR0:"));
                        strncat(data,str_val,strlen(str_val));
			strncat(data,";",1);
			strncat(data,"\0",1);
                        char str_edge_ip[40];
                        kprintf("main: sending data \"%s\" to edge at \"%s\":9801\n",data,str_edge_ip);
			retval = udp_sendto(slot, remip, remport, data, strlen(data));
			if (retval == SYSERR) 
			{
				kprintf("udp_sendto failed\n");
				return SYSERR;
			}
		}
		else
		{
			kprintf("Unknown command ; see log\n");
			uint32 i=0;
			while(matchstr[i]!='\0')
			{
				if(matchstr[i]==buff[i])
					kprintf("%d matches\n",i);
				else
					break;
				i++;
			}
			kprintf("log ends\n");
		}
	}
	return OK;
    
}
