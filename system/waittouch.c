/*  waittouch.c  - waittouch */

#include <xinu.h>

process	waittouch(uint32 xnum)
{
	kprintf("inside waittouch");
	while(1)
	{
		read(xnum,NULL,NULL);
		kprintf("read value \n");
                char data[1000]="";
                strncat(data,"setval:BUZ0:off",strlen("setval:BUZ0:off"));
               	strncat(data,";",1);
                strncat(data,"\0",1);
                // Get edge IP
                char str_edge_ip[40];
                uint32 ipaddr_edge = NetData.iprouter;
                sprintf(str_edge_ip, "%d.%d.%d.%d", (ipaddr_edge>>24)&0xff, (ipaddr_edge>>16)&0xff, (ipaddr_edge>>8)&0xff,ipaddr_edge&0xff);
                kprintf("main: sending data \"%s\" to edge at \"%s\":9801\n",data,str_edge_ip);
                sendpkt(str_edge_ip,9801,data,strlen(data));
	}
	return OK;
}
