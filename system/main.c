/*  main.c  - main */

#include <xinu.h>

process	main(void)
{

	char str_own_ip[40];
	// Extracting local IP address in str in dotted decimal notation
        uint32 ipaddr = NetData.ipucast;
        sprintf(str_own_ip, "%d.%d.%d.%d", (ipaddr>>24)&0xff, (ipaddr>>16)&0xff, (ipaddr>>8)&0xff,ipaddr&0xff);

	char str_edge_ip[40];
	// Extracting EDGE IP address in str in dotted decimal notation
        uint32 ipaddr_edge = NetData.iprouter;
        sprintf(str_edge_ip, "%d.%d.%d.%d", (ipaddr_edge>>24)&0xff, (ipaddr_edge>>16)&0xff, (ipaddr_edge>>8)&0xff,ipaddr_edge&0xff);

/*	
	pid32 fsr_poll,serverfsr_proc;
	
	kprintf("Opening FSR0\n");
	open(FSR0,NULL,NULL);
	
	char data[1000]="";
	strncat(data,"register",strlen("register"));
	strncat(data,":FSR0:",6);
	strncat(data,str_own_ip,strlen(str_own_ip));
	strncat(data,";",1);
	strncat(data,"\0",1);
	kprintf("main: sending data \"%s\" to edge at \"%s\":9801\n",data,str_edge_ip);

	// edge runs on port 9801
	sendpkt(str_edge_ip,9801,data,strlen(data));

	fsr_poll=create(fsrpoll,4096,20,"fsr_polling",1,FSR0);
	serverfsr_proc=create(serverfsr,4096,20,"serverfsr_process",1,FSR0);
	resume(fsr_poll);
	resume(serverfsr_proc);
*/
/*	pid32 serverbuz_proc;
	
	kprintf("Opening BUZ0\n");
	open(BUZ0,NULL,NULL);
	
	char data[1000]="";
	strncat(data,"register",strlen("register"));
	strncat(data,":BUZ0:",6);
	strncat(data,str_own_ip,strlen(str_own_ip));
	strncat(data,";",1);
	strncat(data,"\0",1);
	kprintf("main: sending data \"%s\" to edge at \"%s\":9801\n",data,str_edge_ip);

	// edge runs on port 9801
	sendpkt(str_edge_ip,9801,data,strlen(data));

	serverbuz_proc=create(serverbuz,4096,20,"serverbuz_process",1,BUZ0);
	resume(serverbuz_proc);
*/
	
	kprintf("Opening CTS0\n");
	open(CTS0,NULL,NULL);
	char data[1000]="";
	strncat(data,"register",strlen("register"));
	strncat(data,":CTS0:",6);
	strncat(data,str_own_ip,strlen(str_own_ip));
	strncat(data,";",1);
	strncat(data,"\0",1);
	kprintf("main: sending data \"%s\" to edge at \"%s\":9801\n",data,str_edge_ip);

	sendpkt(str_edge_ip,9801,data,strlen(data));
	pid32 waittouch_proc;
	waittouch_proc=create(waittouch,4096,20,"waittouch_process",1,CTS0);
	kprintf("Starting waittouch\n");
	resume(waittouch_proc);
	
	return OK;
    
}
