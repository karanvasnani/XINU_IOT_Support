/* adc.h */
#define ADC_TSC		0x44E0D000

#define CM_WKUP                   0x44E00400 
#define CM_WKUP_ADC_TSC_CLKCTRL         0xBC 

/* ADC_TSC registers */
#define REVISION		0x0
#define SYSCONFIG		0x10
#define IRQ_EOI			0x20
#define IRQSTATUS		0x28
#define IRQENABLE_SET		0x2C
#define IRQENABLE_CLR		0x30
#define IRQWAKEUP		0x34
#define DMAENABLE_SET		0x38
#define DMAENABLE_CLR		0x3C
#define CTRL			0x40
#define ADCSTAT			0x44
#define ADCRANGE		0x48
#define ADC_CLKDIV		0x4C
#define ADC_MISC		0x50
#define STEPENABLE		0x54
#define IDLECONFIG		0x58
#define TS_CHARGE_STEPCONFIG	0x5C
#define TS_CHARGE_DELAY		0x60
#define STEPCONFIG1		0x64
#define STEPDELAY1		0x68
#define STEPCONFIG2		0x6C
#define STEPDELAY2		0x70
#define STEPCONFIG3		0x74
#define STEPDELAY3		0x78
#define STEPCONFIG4		0x7C
#define STEPDELAY4		0x80
#define STEPCONFIG5		0x84
#define STEPDELAY5		0x88
#define STEPCONFIG6		0x8C
#define STEPDELAY6		0x90
#define STEPCONFIG7		0x94
#define STEPDELAY7		0x98
#define STEPCONFIG8		0x9C
#define STEPDELAY8		0xA0
#define STEPCONFIG9		0xA4
#define STEPDELAY9		0xA8
#define STEPCONFIG10		0xAC
#define STEPDELAY10		0xB0
#define STEPCONFIG11		0xB4
#define STEPDELAY11		0xB8
#define STEPCONFIG12		0xBC
#define STEPDELAY12		0xC0
#define STEPCONFIG13		0xC4
#define STEPDELAY13		0xC8
#define STEPCONFIG14		0xCC
#define STEPDELAY14		0xD0
#define STEPCONFIG15		0xD4
#define STEPDELAY15		0xD8
#define STEPCONFIG16		0xDC
#define STEPDELAY16		0xE0
#define FIFO0COUNT		0xE4
#define FIFO0THRESHOLD		0xE8
#define DMA0REQ			0xEC
#define FIFO1COUNT		0xF0
#define FIFO1THRESHOLD		0xF4
#define DMA1REQ			0xF8
#define FIFO0DATA		0x100
#define FIFO1DATA		0x200

