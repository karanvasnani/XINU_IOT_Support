/* gpio.h - unsetbit, setbit */

#define PIN_VAL			28

/* GPIO base addresses */
#define GPIO0             	0x44E07000
#define GPIO1           	0x4804C000
#define GPIO2   	        0x481AC000
#define GPIO3			0x481AE000

#define GPIO_REVISION 		0x0 	
#define GPIO_SYSCONFIG 		0x10 
#define GPIO_EOI 		0x20 
#define GPIO_IRQSTATUS_RAW_0 	0x24 
#define GPIO_IRQSTATUS_RAW_1 	0x28 
#define GPIO_IRQSTATUS_0 	0x2C 
#define GPIO_IRQSTATUS_1 	0x30 
#define GPIO_IRQSTATUS_SET_0 	0x34 
#define GPIO_IRQSTATUS_SET_1 	0x38 
#define GPIO_IRQSTATUS_CLR_0 	0x3C 
#define GPIO_IRQSTATUS_CLR_1 	0x40 
#define GPIO_SYSSTATUS 		0x114
#define GPIO_CTRL 		0x130
#define GPIO_OE  		0x134
#define GPIO_DATAIN 		0x138
#define GPIO_DATAOUT 		0x13C
#define GPIO_LEVELDETECT0 	0x140
#define GPIO_LEVELDETECT1 	0x144
#define GPIO_RISINGDETECT 	0x148
#define GPIO_FALLINGDETECT 	0x14C
#define GPIO_DEBOUNCENABLE	0x150
#define GPIO_DEBOUNCINGTIME 	0x154
#define GPIO_CLEARDATAOUT 	0x190
#define GPIO_SETDATAOUT 	0x194

#define setbit(val,n)		val | (1<<n)
#define unsetbit(val,n)		val & ~(1<<n)

