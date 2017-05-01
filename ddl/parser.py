import xml.etree.ElementTree as ET
import sys
import os
tree = ET.parse('../ddl/ddl.xml')
root = tree.getroot()
if root.tag != 'DDL':
	sys.exit()
devices = root.findall('Device')
for device in devices:
	device_type = device.find('Device_Type').text
	id = device.find('Description').find('Id').text
	device_logic = device.find('Description').find('Device_Logic').text
	if device_type == 'Actuator':
# Add code for changing the directory
		openact = '../device/%s/%sopen.c'% (id, id)
		close = "../device/%s/%sclose.c"% (id, id)
		write = "../device/%s/%swrite.c"% (id, id)
		os.makedirs(os.path.dirname(openact), exist_ok=True)
		actopen = open(openact,'w')		
		actclose = open(close,'w')		
		actwrite = open(write,'w')
		gpio = device.find('Interface').find('Reading').find('Pin').find('Value').text
		gpio_no = int(int(gpio)/32)
		gpio_bit = int(gpio) % 32
		
#	writing actopen.c
#		writing header
		actopen.write ("/* buzopen.c - buzopen */\n\n#include <xinu.h>\n\n/*------------------------------------------------------------------------\n *  buzopen  -  Open a Buzzer device\n *------------------------------------------------------------------------ */\ndevcall	buzopen(\n\tstruct dentry *devptr,	/* Entry in device switch table */\n\tchar	*name,			/* Name to open			*/\n\tchar	*mode			/* Mode argument		*/\n\t)\n{\n")
#		writing main code
		actopen.write("\tuint32 oe_val=*(uint32 *)(GPIO%d+GPIO_OE);\n" %gpio_no)
		actopen.write ("\tuint32 new_oe_val=unsetbit(oe_val,%d);\n\t*(uint32 *)(GPIO%d+GPIO_OE)=new_oe_val;\n\n\treturn devptr->dvnum;\n" %(gpio_bit, gpio_no));
		actopen.write ("}");
		
#   writing actclose.c
#		writing header
		actclose.write ("/* buzclose.c - buzclose */\n\n#include <xinu.h>\n\n/*------------------------------------------------------------------------\n *  buzclose  -  Close a Buzzer device\n *------------------------------------------------------------------------ */\ndevcall	buzclose(\n\tstruct dentry *devptr	/* Entry in device switch table */\n\t)\n{\n")
#		writing main code
		actclose.write ("\tuint32 oe_val=*(uint32 *)(GPIO%d+GPIO_OE);\n" %gpio_no)
		actclose.write ("\tuint32 data_out=*(uint32*)(GPIO%d+GPIO_DATAOUT);\n" %gpio_no)
		actclose.write ("\t*(uint32*)(GPIO%d+GPIO_DATAOUT)=unsetbit(data_out,%d);\n" %(gpio_no, gpio_bit))
		actclose.write ("\tuint32 new_oe_val=setbit(oe_val,%d);\n\t*(uint32 *)(GPIO%d+GPIO_OE)=new_oe_val;\n\n\treturn devptr->dvnum;\n" %(gpio_bit, gpio_no));
		actclose.write ("}");

#	writing actwrite.c
#		writing header
		actwrite.write ("/* buzwrite.c - buzwrite */\n\n#include <xinu.h>\n\n/*------------------------------------------------------------------------\n *  buzwrite  -  write a Buzzer device\n *------------------------------------------------------------------------ */\ndevcall	buzwrite(\n\tstruct dentry *devptr,	/* Entry in device switch table */\n\tchar	*buff,\t	/* Buffer of characters			*/\n\tuint32	count\n\t)\n{\n")
#		writing main code
		actwrite.write("\tuint32 oe_val=*(uint32 *)(GPIO%d+GPIO_OE);\n\tuint32 data_out=*(uint32 *)(GPIO%d+GPIO_DATAOUT);\n\n" %(gpio_no, gpio_no))
		actwrite.write("\tif((buff[0]=='o' && buff[1]=='n')||((buff[0]=='O' && buff[1]=='N')))\n\t{\n")
		actwrite.write ("\t\tuint32 new_data_out=setbit(data_out,%d);\n" %gpio_bit)
		actwrite.write ("\t\t*(uint32 *)(GPIO%d+GPIO_DATAOUT)=new_data_out;\n" % gpio_no)
		actwrite.write ("\t}\n")
		actwrite.write ("\telse if((buff[0]=='o' && buff[1]=='f' && buff[2]=='f')||(buff[0]=='O' && buff[1]=='F' && buff[2]=='F'))\n\t{\n")
		actwrite.write ("\t\tuint32 new_data_out=unsetbit(data_out,%d);\n" %gpio_bit)
		actwrite.write ("\t\t*(uint32 *)(GPIO%d+GPIO_DATAOUT)=new_data_out;\n\t}\n" %gpio_no)
		actwrite.write ("\telse\n\t{\n\t\treturn SYSERR;\n\t}\n\n\treturn OK;\n}\n")
			
#	closing files
		actwrite.close()
		actclose.close()
		actopen.close()
		
	if device_type=='Sensor' and device_logic=='Analog':
# Add code for changing the directory
		openfsr = '../device/%s/%sopen.c'% (id, id)
		close = "../device/%s/%sclose.c"% (id, id)
		read = "../device/%s/%sread.c"% (id, id)
		init = "../device/%s/%sinit.c"% (id, id)
		os.makedirs(os.path.dirname(openfsr), exist_ok=True)
		fsropen = open(openfsr,'w')		
		fsrclose = open(close,'w')		
		fsrread = open(read,'w')
		fsrinit = open(init,'w')
		ain_pin = device.find('Interface').find('Reading').find('Pin').find('Value').text
		formula = device.find('Interface').find('Computation').find('Expression').text	
	
#	writing fsropen.c
#		writing header
		fsropen.write ("/* fsropen.c - fsropen */\n\n#include <xinu.h>\n\n/*------------------------------------------------------------------------\n *  fsropen  -  Open a Force Sensitive Resistor (Pressure Sensor) device\n *------------------------------------------------------------------------\n */\ndevcall	fsropen(\n\tstruct dentry *devptr,	/* Entry in device switch table */\n\tchar	*name,			/* Name to open			*/\n\tchar	*mode			/* Mode argument		*/\n\t)\n{\n")
#		writing main code
		fsropen.write ("\tuint32 step_enable_orig = *(uint32 *)(ADC_TSC+STEPENABLE);\n")
		fsropen.write ("\tuint32 step_enable_new = setbit(step_enable_orig,1);\n")
		fsropen.write ("\t*(uint32 *)(ADC_TSC+STEPENABLE) = step_enable_new;\n")
		fsropen.write ("\n\treturn devptr->dvnum;\n}")
		
#   writing fsrclose.c
#		writing header
		fsrclose.write ("/* fsrclose.c - fsrclose */\n\n#include <xinu.h>\n\n/*------------------------------------------------------------------------\n *  fsrclose  -  Close a Force Sensitive Resistor (Pressure sensor) device\n *------------------------------------------------------------------------\n */\ndevcall	fsrclose(\n\tstruct dentry *devptr	/* Entry in device switch table */\n\t)\n{\n")
#		writing main code
		fsrclose.write("\treturn devptr->dvnum;\n}")
		
#	writing fsrread.c
#		writing header
		fsrread.write ("/* fsrread.c - fsrread */\n\n#include <xinu.h>\n\n/*------------------------------------------------------------------------\n *  fsrread  -  Read from a fsr device\n *------------------------------------------------------------------------\n */\ndevcall	fsrread(\n\tstruct dentry *devptr,	/* Entry in device switch table */\n\tchar	*buff,\t	/* Buffer of characters			*/\n\tuint32	count 			/* Count of character to read	*/\n\t)\n{\n")
#		writing main code
		fsrread.write ("\tuint32 value_of_sensor = *(uint32 *)(ADC_TSC+FIFO0DATA);\n")
		fsrread.write ("\tuint32 adc_val=value_of_sensor;\n")
		fsrread.write ("\tuint32 output;\n")
		fsrread.write ("\t%s;\n" % formula )
		fsrread.write ("\n\treturn output;\n}")
		
#	writing fsrinit.c
#		writing header
		fsrinit.write ("/* fsrinit.c - fsrinit */\n\n#include <xinu.h>\n\n/*--------------------------------------------------------------------------------\n * fsrinit  -  Force sensitive resistor (Pressure sensor) initialization function\n *--------------------------------------------------------------------------------\n */\ndevcall	fsrinit (\n\tstruct	dentry *devptr\n\t)\n{\n")
#		writing main code
		fsrinit.write("\t\tuint32 cm_wkup_adc_tsc_clkctrl_orig = *(uint32*)(CM_WKUP+CM_WKUP_ADC_TSC_CLKCTRL);\n\n")
		fsrinit.write("\t\tuint32 cm_wkup_adc_tsc_clkctrl_new = setbit(cm_wkup_adc_tsc_clkctrl_orig,1);\n")
		fsrinit.write("\t\t*(uint32*)(CM_WKUP+CM_WKUP_ADC_TSC_CLKCTRL)=cm_wkup_adc_tsc_clkctrl_new;\n\n")
		fsrinit.write("\t\tuint32 adc_tsc_ctrl_orig = *(uint32 *)(ADC_TSC+CTRL);\n\n")
		fsrinit.write("\t\tuint32 adc_tsc_ctrl_new = setbit(adc_tsc_ctrl_orig,2);\n")
		fsrinit.write("\t\t*(uint32 *)(ADC_TSC+CTRL) = adc_tsc_ctrl_new;\n\n")
		fsrinit.write("\t\tuint32 stepconfig1_orig = *(uint32 *)(ADC_TSC+STEPCONFIG1);\n\n")
		fsrinit.write("\t\t*(uint32 *)(ADC_TSC+STEPCONFIG1) = setbit(stepconfig1_orig,0);\n")
		fsrinit.write("\t\tuint32 stepconfig1_new = *(uint32 *)(ADC_TSC+STEPCONFIG1);\n\n")
		fsrinit.write("\t\tuint32 stepdelay1_orig = *(uint32 *)(ADC_TSC+STEPDELAY1);\n\n")
		fsrinit.write("\t\t*(uint32 *)(ADC_TSC+STEPDELAY1) = (0x0F)<<24;\n")
		fsrinit.write("\t\tuint32 stepdelay1_new = *(uint32 *)(ADC_TSC+STEPDELAY1);\n\n")
		fsrinit.write("\t\tadc_tsc_ctrl_orig = *(uint32 *)(ADC_TSC+CTRL);\n")
		fsrinit.write("\t\tadc_tsc_ctrl_new = setbit(adc_tsc_ctrl_orig,0);\n\n")
		fsrinit.write("\t\t*(uint32 *)(ADC_TSC+CTRL) = adc_tsc_ctrl_new;\n\n")
		fsrinit.write("\treturn OK;\n}")
		
#	closing files
		fsrread.close()
		fsrclose.close()
		fsropen.close()
		fsrinit.close()
		
	if device_type=='Sensor' and device_logic=='Digital':
# Add code for changing the directory
		opencts = '../device/%s/%sopen.c'% (id, id)
		close = "../device/%s/%sclose.c"% (id, id)
		read = "../device/%s/%sread.c"% (id, id)
		init = "../device/%s/%sinit.c"% (id, id)
		handler = "../device/%s/%shandler.c"% (id, id)
		os.makedirs(os.path.dirname(opencts), exist_ok=True)
		ctsopen = open(opencts,'w')		
		ctsclose = open(close,'w')		
		ctsread = open(read,'w')
		ctsinit = open(init,'w')
		ctshand = open(handler,'w')
		gpio = device.find('Interface').find('Reading').find('Pin').find('Value').text
		gpio_no = int(int(gpio)/32)
		gpio_bit = int(gpio) % 32
		
#	writing ctsopen.c
#		writing header
		ctsopen.write ("/* ctsopen.c - ctsopen */\n\n#include <xinu.h>\n\n/*------------------------------------------------------------------------\n *  ctsopen  -  Open a Capacitive Touch Sensor device\n *------------------------------------------------------------------------\n */\ndevcall	ctsopen(\n\tstruct dentry *devptr,	/* Entry in device switch table */\n\tchar	*name,			/* Name to open			*/\n\tchar	*mode			/* Mode argument		*/\n\t)\n{\n")
#		writing main code
		ctsopen.write ("\tuint32 oe_val=*(uint32 *)(GPIO%d+GPIO_OE);\n\tuint32 data_in=*(uint32 *)(GPIO%d+GPIO_DATAIN);\n\n" % (gpio_no, gpio_no))
		ctsopen.write ("\t// set output enable to 1 to configure device for reading(data_in/input)\n\tuint32 new_oe_val=setbit(oe_val,%d);\n\t*(uint32 *)(GPIO%d+GPIO_OE)=new_oe_val;\n\n" %(gpio_bit, gpio_no))
		ctsopen.write ("\treturn devptr->dvnum;\n}")
		
#	writing ctsclose.c
#		writing header
		ctsclose.write ("/* ctsclose.c - ctsclose */\n\n#include <xinu.h>\n\n/*------------------------------------------------------------------------\n *  ctsclose  -  Close a capacitive touch sensor device\n *------------------------------------------------------------------------\n */\ndevcall	ctsclose(\n\tstruct dentry *devptr	/* Entry in device switch table */\n\t)\n{\n")
#		writing main code
		ctsclose.write ("\treturn devptr->dvnum;\n}")
		
#	writing ctsread.c
#		writing header
		ctsread.write ("/* csrread.c - csrread */\n\n#include <xinu.h>\n\n/*------------------------------------------------------------------------\n *  ctsread  -  Read from a cts device\n *------------------------------------------------------------------------\n */\ndevcall	ctsread(\n\tstruct dentry *devptr,	/* Entry in device switch table */\n\tchar	*buff,\t	/* Buffer of characters			*/\n\tuint32	count 			/* Count of character to read	*/\n\t)\n{\n")
#		writing main code
		ctsread.write ("\tuint32 irq_status_clr_val=0xFFFFFFFF;\n\t*(uint32 *)(GPIO%d+GPIO_IRQSTATUS_CLR_0)=irq_status_clr_val;\n\n" % gpio_no)
		ctsread.write ("\tuint32 irq_status_clr_1_val = 0xFFFFFFFF;\n\t*(uint32 *)(GPIO%d+GPIO_IRQSTATUS_CLR_1)=irq_status_clr_1_val;\n\t// CLEAR DONE\n\n" %gpio_no)
		ctsread.write ("\t//Setting interrupt on for only 28th bit\n\tuint32 irq_status = (1<<%d);\n\t*(uint32 *)(GPIO%d+GPIO_IRQSTATUS_SET_0)=irq_status;\n\n" % (gpio_bit,gpio_no))
		ctsread.write ("\t// Setting rising detect for 28th bit only\n\tuint32 irq_rising = (1<<%d);\n\t*(uint32 *)(GPIO%d+GPIO_RISINGDETECT) = irq_rising;\n\n" % (gpio_bit,gpio_no))
		ctsread.write ("\twait(cts_sem);\n\t\tkprintf(\"Button touched\\n\");\n\n")
		ctsread.write ("\treturn OK;\n}")
		
#	writing ctsinit.c
#		writing header
		ctsinit.write ("/* ctsinit.c - ctsinit */\n\n#include <xinu.h>\n\n/*--------------------------------------------------------------------------------\n * ctsinit  -  Cap touch sensor initialization function\n *--------------------------------------------------------------------------------\n */\ndevcall	ctsinit (\n\tstruct	dentry *devptr\n\t)\n{\n")
#		writing main code
		ctsinit.write ("\tset_evec( devptr->dvirq, (uint32)devptr->dvintr );\n\treturn OK;\n}")
		
#	writing ctshandler.c
#		writing header
		ctshand.write ("/* ctshandler.c - ctshandler */\n\n#include <xinu.h>\n\n/*------------------------------------------------------------------------\n *  ctshandler  -  Handle an interrupt for a cts device\n *------------------------------------------------------------------------\n */\n\nvoid ctshandler(uint32 xnum) {\n")
#		writing main code
		ctshand.write ("\n\n\tstatic uint32 num=0;\n\n")
		ctshand.write ("\tuint32 data_in=*(uint32 *)(GPIO%d+GPIO_DATAIN);\n\tdata_in=data_in & (1<<%d);\n\n" % (gpio_no,gpio_bit))
		ctshand.write ("\tif(data_in>0)\n\t{\n\t\tnum++;\n\t\tif(num==10)\n\t\t{\n")
		ctshand.write ("\t\t\t\n\t\t\tuint32 irq_status_clr = (1<<%d);\n\t\t\t*(uint32 *)(GPIO%d+GPIO_IRQSTATUS_CLR_0)=irq_status_clr;\n\t\t\tsignal(cts_sem);\n\t\t}\n\t}\n" % (gpio_bit,gpio_no))
		ctshand.write ("\telse\n\t{\n\t\tnum=0;\n\t}\n\n")
		ctshand.write ("}")
