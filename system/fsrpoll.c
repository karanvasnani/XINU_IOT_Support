/*  fsrpoll.c  - fsrpoll */

#include <xinu.h>

process	fsrpoll(uint32 xnum)
{
	uint32 cur_val;
	kprintf("Starting 5 sec polling for FSR device");
	while(1)
	{
		cur_val=read(xnum,NULL,NULL);
//		kprintf("read value %d\n",cur_val);
		if(cur_val > 500)
		{
			// Convert val to str
			char str_val[40];
			sprintf(str_val,"%d",cur_val);
			// Need to switch on buzzer
			char data[1000]="";
			strncat(data,"setval:BUZ0:on;",strlen("setval:BUZ0:on;"));
			strncat(data,"\0",1);
			char str_edge_ip[40];
			// Get edge IP
        		uint32 ipaddr_edge = NetData.iprouter;
        		sprintf(str_edge_ip, "%d.%d.%d.%d", (ipaddr_edge>>24)&0xff, (ipaddr_edge>>16)&0xff, (ipaddr_edge>>8)&0xff,ipaddr_edge&0xff);
			kprintf("main: sending data \"%s\" to edge at \"%s\":9801\n",data,str_edge_ip);
			sendpkt(str_edge_ip,9801,data,strlen(data));
		}
		sleep(5);
	}
	return OK;
}
